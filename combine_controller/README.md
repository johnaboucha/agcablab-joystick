# AgCabLab - Combine Controller

Release Version: 2014.08.11

File:  Combine_Controller.ino

About:  This version of the Combine Controller turns the Arduino Leonardo into a joystick with a custom build of the Arduino IDE.  Two files were updated, the HID.cpp and USPAPI.h found here: http://www.imaginaryindustries.com/blog/?p=80.  Additional documentation for this Joystick feature was found on the forums: http://www.jayconsystems.com/forum/viewtopic.php?f=10&t=2127.

**Button Layout:**\
Button Number | Bit | Description

Button 0 | 0x1 | Raise Header 
Button 1 | 0x2 | Lower Header
Button 2 | 0x4 | Swing Arm Out (Also Swings Target Out)
Button 3 | 0x8 | Swing Arm In (Also Swings Target In)
Button 4 | 0x10 | Dump Grain
Button 5 | 0x20 | Start