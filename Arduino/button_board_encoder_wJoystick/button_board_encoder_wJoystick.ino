#include <Adafruit_NeoPixel.h>
#include <Joystick.h>
#define NUM_PINS 7
bool buttonStates[NUM_PINS] = {0};
 
 #define outputA 2
 #define outputB 3
 const int swPin0 = 0;
 const int swPin1 = 1;
 const int swPin5 = 5;
 const int swPin6 = 6;
 const int swPin7 = 7;
 const int swPin8 = 8;
 const int swPin10 = 10;
 const int swPin11 = 11;
 const int swPin12 = 12;
 const int swPin13 = 13;
 
 int startupVersion = 4; //IMPORTANT! (/j)
 bool singleBranch = 0; //EXTREMELY IMPORTANT!!!!!!!

 int counter = 15000; 
 int aState;
 int aLastState;

 int startupState = 0;

 bool buttonDown = 0;
 bool algaeMode = 0;
 bool bothAlgae = 0;
 int currentTarget = 49;

 
int markpin = 0;
int placepin = 0;
int mark[12][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int place[12][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

uint32_t Lred = 0x220000;
uint32_t Lorange = 0x221100;
uint32_t Lyellow = 0x222200;
uint32_t Lgreen = 0x002200;
uint32_t Lblue = 0x000022;
uint32_t Lpurple = 0x220022;

uint32_t Lwhite = 0x222222;

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
                   false, false, false, false, false, false, false);
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
pinMode(swPin10, INPUT);
pinMode(swPin11, INPUT);
pinMode(swPin12, INPUT);
pinMode(swPin13, INPUT);
pinMode(swPin0, INPUT);
pinMode(swPin1, INPUT);
}

/*  ###  these are the subfunctions that are available to run ###  */
int button(){ //verified
  // input:  low voltage on individual pins when buttons are pressed
  // process:  read the pins.  determine which is pressed, if any
  // output:  0 for no pins being pressed, otherwise output [markpin, placepin]
  // example [1,0] if markpin=1 and placepin=0
  // later figure out to add debounce, reference "singleswitch"
  if (singleBranch){
    buttonDown = 1;
    if (digitalRead(swPin10) == HIGH or digitalRead(swPin5) == HIGH){algaeMode=0;  return 1;}
    if (digitalRead(swPin11) == HIGH or digitalRead(swPin6) == HIGH){algaeMode=0;  return 2;}
    if (digitalRead(swPin12) == HIGH or digitalRead(swPin7) == HIGH){algaeMode=0;  return 3;}
    if (digitalRead(swPin13) == HIGH or digitalRead(swPin8) == HIGH){algaeMode=0;  return 4;}
    
    if (digitalRead(swPin0) == HIGH and digitalRead(swPin1) == HIGH) {algaeMode=1; bothAlgae=1; return 4;}
    if ((bothAlgae) and (digitalRead(swPin0) == HIGH or digitalRead(swPin1) == HIGH)) {
      delay(100);
    }
    if (digitalRead(swPin0) == HIGH){algaeMode=1; bothAlgae=0; return 2;}
    if (digitalRead(swPin1) == HIGH){algaeMode=1; bothAlgae=0; return 3;}
    buttonDown = 0;
  } else {
    buttonDown=1;
    if (digitalRead(swPin5) == HIGH){algaeMode=0;  return 5;} //return the level associated with the button
    if (digitalRead(swPin6) == HIGH){algaeMode=0;  return 6;}
    if (digitalRead(swPin7) == HIGH){algaeMode=0;  return 7;}
    if (digitalRead(swPin8) == HIGH){algaeMode=0;  return 8;}
    if (digitalRead(swPin10) == HIGH){algaeMode=0;  return 1;}
    if (digitalRead(swPin11) == HIGH){algaeMode=0;  return 2;}
    if (digitalRead(swPin12) == HIGH){algaeMode=0;  return 3;}
    if (digitalRead(swPin13) == HIGH){algaeMode=0;  return 4;}

    if (digitalRead(swPin0) == HIGH and digitalRead(swPin1) == HIGH) {algaeMode=1; bothAlgae=1; return 4;}
    if ((bothAlgae) and (digitalRead(swPin0) == HIGH or digitalRead(swPin1) == HIGH)) {
      delay(100);
    }
    if (digitalRead(swPin0) == HIGH){algaeMode=1; bothAlgae=0; return 2;}
    if (digitalRead(swPin1) == HIGH){algaeMode=1; bothAlgae=0; return 3;}
    buttonDown = 0;
  }
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
int SwitchPos = (abs(counter%12)/2)+1;
// Serial.println(SwitchPos);
    
//read the button, interpret the level
int level = button();

//here we need to determine if the button has changed or the encoder has changed
if(buttonDown==1){
  if (singleBranch) {
    currentTarget = reefLookupFcn(7,level);
  }
  else {
    if (level<=4) {
      currentTarget = reefLookupFcn(SwitchPos*2-1,level);
    } else {
      currentTarget = reefLookupFcn(SwitchPos*2,level-4);
    }
  }
}

//light the switchlight row 1
int poleLED = reefLookupFcn(SwitchPos,1);
poleLED *= 2;
if (singleBranch) {
  poleLED = 24;
}

/*   STARTUP START   */

if(startupVersion==1){ //TRAFFIC LIGHT
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
      delay(125);
    }
    startupState++;
    delay(150);
  } else {
    startupVersion=0;
  }
}

if(startupVersion==2){ //ALL ON THEN OFF
  //New startup sequence just dropped
  if(startupState==0){
    for(int k=0;k<=48;k++){
      strip.setPixelColor(k,0,0,0);
    }
  }
  strip.show();
  delay(50);
  for(int i=0;i<=48;i++){
    strip.setPixelColor(i, Lwhite);
    strip.show();
    delay(30);
  }
  for(int i=0;i<=48;i++){
    strip.setPixelColor(i,0,0,0);
    strip.show();
    delay(30);
  }
  startupVersion=0;
  delay(100);
}

if(startupVersion==3){ //RAINBOW
  //Actual shark
  if(startupState==0){
    for(int k=0;k<=48;k++){
      strip.setPixelColor(k,0,0,0);
    }
  }
  strip.show();
  delay(50);
  for(int i=0;i<8;i++){
    strip.setPixelColor(i, Lred);
    strip.show();
    delay(20);
  }
  for(int i=8;i<16;i++){
    strip.setPixelColor(i, Lorange);
    strip.show();
    delay(20);
  }
  for(int i=16;i<24;i++){
    strip.setPixelColor(i, Lyellow);
    strip.show();
    delay(20);
  }
  for(int i=24;i<32;i++){
    strip.setPixelColor(i, Lgreen);
    strip.show();
    delay(20);
  }
  for(int i=32;i<40;i++){
    strip.setPixelColor(i, Lblue);
    strip.show();
    delay(20);
  }
  for(int i=40;i<48;i++){
    strip.setPixelColor(i, Lpurple);
    strip.show();
    delay(20);
  }
  startupVersion=0;
  delay(500);
}

if(startupVersion==4){ //LE FISH AU CHOCOLAT
  //Call the fish!
  if(startupState==0){
    for(int k=0;k<=48;k++){
      strip.setPixelColor(k,Lblue);
    }
  }
  for(int i=0;i<6;i++){
    for(int i=44;i<48;i++){strip.setPixelColor(i, Lblue);}
    for(int i=32;i<44;i++){strip.setPixelColor(i, Lorange);}
    for(int i=1;i<=12;i++){strip.setPixelColor(reefLookupFcn(i,1), Lorange);}
    strip.show();
    delay(250);
    for(int i=32;i<36;i++){strip.setPixelColor(i, Lblue);}
    for(int i=44;i<48;i++){strip.setPixelColor(i, Lorange);}
    for(int i=1;i<=12;i++){strip.setPixelColor(reefLookupFcn(i,1), Lorange);}
    strip.show();
    delay(250);
  }
  startupVersion=0;
}

/*   STARTUP END   */

if(startupVersion==0) { //NO STARTUP
  for(int i=0;i<=48;i++){
    strip.setPixelColor(i,0,0,0);
  }
  strip.setPixelColor(poleLED+0, Lwhite);  //show the current rotary position as a white LED
  strip.setPixelColor(poleLED+1, Lwhite);
  strip.setPixelColor(poleLED+2, Lwhite);
  strip.setPixelColor(poleLED+3, Lwhite);
  strip.setPixelColor(poleLED+4, Lwhite);
  strip.setPixelColor(poleLED+5, Lwhite);
  strip.setPixelColor(poleLED+6, Lwhite);
  strip.setPixelColor(poleLED+7, Lwhite);
  if(algaeMode) {
    strip.setPixelColor(currentTarget, Lgreen);  //show the current target as GREEN
    strip.setPixelColor(currentTarget+4, Lgreen);
  }
  else {
    if (singleBranch) {
      strip.setPixelColor(currentTarget, Lred);
      strip.setPixelColor(currentTarget+4, Lred);
    }
    else {
      strip.setPixelColor(currentTarget, Lred);  //show the current target as RED
    }
  }
  if(algaeMode and bothAlgae) {
    strip.setPixelColor(currentTarget-1,Lyellow);
    strip.setPixelColor(currentTarget+3,Lyellow);
    strip.setPixelColor(currentTarget,Lyellow);
    strip.setPixelColor(currentTarget+4,Lyellow);
  }
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

// Serial.println(currentTarget);
Joystick.setButton(6, algaeMode);
Joystick.setButton(5, bin6);
Joystick.setButton(4, bin5);
Joystick.setButton(3, bin4);  
Joystick.setButton(2, bin3);
Joystick.setButton(1, bin2);
Joystick.setButton(0, bin1);
}