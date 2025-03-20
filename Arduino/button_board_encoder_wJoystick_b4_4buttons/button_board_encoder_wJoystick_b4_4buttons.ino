#include <Adafruit_NeoPixel.h>
#include <Joystick.h>
#define NUM_PINS 6
bool buttonStates[NUM_PINS] = {0};
 
 #define outputA 2
 #define outputB 3
 const int swPin5 = 5;
 const int swPin6 = 6;
 const int swPin7 = 7;
 const int swPin8 = 8;
 
 int counter = 15000; 
 int aState;
 int aLastState;

 int startupState = 0;

 bool buttonDown = 0;
 int currentTarget = 49;

 
int markpin = 0;
int placepin = 0;
int mark[12][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int place[12][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

uint32_t Lred = 0x330000;
uint32_t Lyellow = 0x333300;
uint32_t Lgreen = 0x003300;
uint32_t Lwhite = 0x333333;

//neopixel variables
#define PIN 9
int LEDnum = 0;
int numLED = 49;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLED, PIN, NEO_RGB + NEO_KHZ800);


// reefpole corresponds to switchPos; 
// lights 1-4 correspond to reefpole 1, lights 5-8:  reefpole 2; 9-12:3 ...
int reefLookup[48][3] = {{1,1,0},{1,2,1},{1,3,2},{1,4,3},
                         {2,1,4},{2,2,5},{2,3,6},{2,4,7},
                         {3,1,8},{3,2,9},{3,3,10},{3,4,11},
                         {4,1,12},{4,2,13},{4,3,14},{4,4,15},
                         {5,1,16},{5,2,17},{5,3,18},{5,4,19},
                         {6,1,20},{6,2,21},{6,3,22},{6,4,23},
                         {7,1,24},{7,2,25},{7,3,26},{7,4,27},
                         {8,1,28},{8,2,29},{8,3,30},{8,4,31},
                         {9,1,32},{9,2,33},{9,3,34},{9,4,35},
                         {10,1,36},{10,2,37},{10,3,38},{10,4,39},
                         {11,1,40},{11,2,41},{11,3,42},{11,4,43},
                         {12,1,44},{12,2,45},{12,3,46},{12,4,47}};
// for a given reefpole and level, what is the corresponding LED? {pole,level,LED}
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, NUM_PINS, 0, 
                   false, false, false, false, false, false);
/*  ###  this part of the code runs at startup ###  */
void setup() {
  Joystick.begin();
  
  //encoder setup
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   

  Serial.begin(9600);
  
  strip.begin();
// set all LEDs to Green
//for(int i=1;i<=49; i++){
//strip.setPixelColor(i, Lblue); 
//}
//strip.show();

// initialize the buttons
pinMode(swPin5, INPUT);
pinMode(swPin6, INPUT);
pinMode(swPin7, INPUT);
pinMode(swPin8, INPUT);
}

/*  ###  these are the subfunctions that are available to run ###  */
int button(){ //verified
  // input:  low voltage on individual pins when buttons are pressed
  // process:  read the pins.  determine which is pressed, if any
  // output:  0 for no pins being pressed, otherwise output [markpin, placepin]
  // example [1,0] if markpin=1 and placepin=0
  // later figure out to add debounce, reference "singleswitch"
  if (digitalRead(swPin5) == HIGH){buttonDown=1;  return 1;} //return the level associated with the button
  if (digitalRead(swPin6) == HIGH){buttonDown=1;  return 2;}
  if (digitalRead(swPin7) == HIGH){buttonDown=1;  return 3;}
  if (digitalRead(swPin8) == HIGH){buttonDown=1;  return 4;}
  buttonDown = 0;
}

int reefLookupFcn(int reef, int lvl){
  for(int i=0;i<=47;i++){
      if(reefLookup[i][0]==reef){
        if(reefLookup[i][1]==lvl){
          return reefLookup[i][2];
        }
      }
    }
  }

int update_encoder(){
  aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter --;
     } else {
       counter ++;
     }
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

 
/*  ###  this part of the code runs continuously and is used to call subfunctions ###  */
void loop() {
//this portion reads the encoder and outputs to a position.  
update_encoder();
//int SwitchPos = abs(counter%12)+1; //Original
int SwitchPos = (abs(counter%24)/2)+1;
    
//read the button, interpret the level
int level = button();  

//here we need to determine if the button has changed or the encoder has changed
if(buttonDown==1){currentTarget = reefLookupFcn(SwitchPos,level);}

//light the switchlight row 1
int poleLED = reefLookupFcn(SwitchPos,1);

if(startupState<4){ 
  //An attempt at a startup sequence
  if(startupState==0){
    for(int k=0;k<=48;k++){
      strip.setPixelColor(k,0,0,0);
    }
  }
  for(int i=0;i<=3;i++){
    if(startupState==1){
      for(int j=0;j<=12;j++){
        strip.setPixelColor(j*4+i, Lred);
      }
    } if(startupState==2){
      for(int j=0;j<=12;j++){
        strip.setPixelColor(j*4+i, Lyellow);
      }
    } if(startupState==3){
      for(int j=0;j<=12;j++){
        strip.setPixelColor(j*4+i, Lgreen);
      }
    }
    strip.show();
    delay(150);
  }
  startupState++;
  delay(200);
} else {
  for(int i=0;i<=48;i++){
    strip.setPixelColor(i,0,0,0);
  }
  strip.setPixelColor(poleLED+0, Lwhite);  //show the current rotary position as a white LED
  strip.setPixelColor(poleLED+1, Lwhite);
  strip.setPixelColor(poleLED+2, Lwhite);
  strip.setPixelColor(poleLED+3, Lwhite);
  strip.setPixelColor(currentTarget, Lred);  //show the current target as RED
}

strip.show();

//Serial.println(currentTarget);

int val = currentTarget;
  int bin6 = val/32;
  val = val%32;
  int bin5 = val/16;
  val = val%16;
  int bin4 = val/8;
  val = val%8;
  int bin3 = val/4;
  val = val%4;
  int bin2 = val/2;
  val = val%2;
  int bin1 = val/1;

/*Serial.println(bin6);
Serial.println(bin5);
Serial.println(bin4);
Serial.println(bin3);
Serial.println(bin2);
Serial.println(bin1);
Serial.println(" ");
*/

Serial.println(currentTarget);
Joystick.setButton(5, bin6);
Joystick.setButton(4, bin5);
Joystick.setButton(3, bin4);  
Joystick.setButton(2, bin3);
Joystick.setButton(1, bin2);
Joystick.setButton(0, bin1);
}
