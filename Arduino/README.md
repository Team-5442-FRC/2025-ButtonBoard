# Button Box 2025

Four buttons, plus a 12-position switch. Two TBD slots, likely to be switches at some point? Maybe? Designed for selecting what we want the robot to do next. Critically, not for saying _how_ the robot does something, that's an XBOX controller.

# BOM

* [Screw Terminal Headers](https://www.amazon.com/gp/product/B08B3P8BF3/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)
* [Smaller screw terminal headers](https://www.amazon.com/dp/B09F6TC7RP?ref=ppx_yo2ov_dt_b_fed_asin_title)
* [buttons with prewired leads](https://www.amazon.com/dp/B083JWJPW5?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* [12-position switch](https://www.amazon.com/dp/B07CG9RPKY?ref=ppx_yo2ov_dt_b_fed_asin_title)
* [Arduino Micro](https://www.amazon.com/dp/B0D83FBYPD?ref=ppx_yo2ov_dt_b_fed_asin_title)
* [USB C panel connector](https://www.amazon.com/gp/product/B09HWSFRP1/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
* [Chicken head knobs, in red.](https://www.amazon.com/dp/B0CTK8KTCY?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
* Various lengths of wire and solder from chris's house.

# Case

3d printed. [Onshape model here.](https://cad.onshape.com/documents/869acc283b4ba9cf722a7f24/w/f1bf797406fabe92c85b2bc6/e/4f9baf0fe7687c51c3f60388)

Designed to bolt to a driver station or something like that. 

# In Robot Code

See `GenericHID` - https://docs.wpilib.org/en/stable/docs/software/basic-programming/joystick.html#button-usage

Use `getRawButton()` to get each state. 

18 buttons are enumerated. 

The chickenhead knob may be thought of as 12 buttons, only one of which is pressed at a time (generally)

Each pushbutton is either pressed or not pressed.

Each switch (future) is either on or off.

# Arduino Inputs

![image](https://github.com/user-attachments/assets/e75b9636-1b75-4f60-b4c9-d91ded63cf92)

Which of the 12 digital inputs goes with each physical position depends on how you put the knob on.

Wired so pin numbers increase _counterclockwise_.

Chris suspects this will be a problem at some point.

# HID Inputs

Buttons are index'ed like this:

![image](https://github.com/user-attachments/assets/5716d01d-1a83-4388-a505-5729c6c4e905)

Again, which button goes with which position on the chickenhead knob depends on how you mount the chickenhead knob.

Indices increase _counterclockwise_.

# Fancy Pictures

![PXL_20250124_204141088](https://github.com/user-attachments/assets/ca581af8-fa5e-4dc7-b58a-ad8763fb0f3f)



![PXL_20250124_204133635](https://github.com/user-attachments/assets/2d9d623d-3628-4adf-9ec3-3a46be1b5fe3)
