/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      6/5/2024, 6:08:47 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// define your global instances of motors and other devices here
brain  Brain;
controller Controller1 = controller(primary);
motor LF = motor(PORT1, ratio18_1, false);
motor RF = motor(PORT9, ratio18_1, true);
motor LB = motor(PORT3, ratio18_1, false);
motor RB = motor(PORT6, ratio18_1, true);




bool RemoteControlCodeEnabled = true;

// A global instance of competition
competition Competition;

// define your global variables
float D=4.0;  //wheel diameter
float G=1.0;  //Gear ratio external
float PI= 3.14;  //math constant of circles

//custom functions

void drive(int lspeed, int rspeed, int wt){
  LF.spin(fwd,lspeed,percent);
  LB.spin(fwd,lspeed,percent);
  RF.spin(fwd,rspeed,percent);
  RB.spin(fwd,rspeed,percent);
  wait(wt,msec);
}

void driveBrake(){
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}

void inchDriveBangBang(float target){
  float x=0;
  float speed =50;
LF.setPosition(0.0, rev);
while(x<target){
drive(speed,speed,10);
x=LF.position(rev)*PI*D*G;
}
driveBrake();
}

void inchDriveP(float target){
  float x=0;
  float error=target;
  float kp=1.0;
  float speed =kp*error;
  float accuracy=1.0;
LF.setPosition(0.0, rev);
while(error>accuracy){
drive(speed,speed,10);
x=LF.position(rev)*PI*D*G;
error=target-x;
speed=kp*error;
}
driveBrake();
}

void inchDrivePfabs(float target){
  float x=0;
  float error=target;
  float kp=1.0;
  float speed =kp*error;
  float accuracy=1.0;
LF.setPosition(0.0, rev);
while(fabs(error)>accuracy){
drive(speed,speed,10);
x=LF.position(rev)*PI*D*G;
error=target-x;
speed=kp*error;
}
driveBrake();
}

void connor(void) {
  int x = 0 ; 
float y=0.0 ;
int z = 10;
bool flag = true;
Brain.Screen.printAt(1,20,"variables");
Brain.Screen.printAt(1,40," x = %d   ", x);
Brain.Screen.printAt(1,60, "y = %.2f", y);
  while (true) {
   x+=5;
   y+=2;
   z=0;
   Brain.Screen.printAt(1,20,"variables");
Brain.Screen.printAt(1,40," x = %d   ", x);
Brain.Screen.printAt(1,60, "y = %.2f", y);
  Brain.Screen.clearScreen();
 // wait(75, msec); 
Brain.Screen.setFillColor(orange);
Brain.Screen.drawRectangle(25,150,50,75);
Brain.Screen.setFillColor(purple);
Brain.Screen.drawCircle(170, 150, 50);
Brain.Screen.drawRectangle(50, 100, 60, 45, 60);
Brain.Screen.setFillColor(blue);
Brain.Screen.drawCircle(x,y,10);
   wait(50, msec); 
    if (x>400) {
      x=0;
      y=0;
    }
    }
}
void william(void) {
  int x = 0 ; 
float y=0.0 ;
int z = 10;
bool flag = true;
Brain.Screen.printAt(1,20,"variables");
Brain.Screen.printAt(1,40," x = %d   ", x);
Brain.Screen.printAt(1,60, "y = %.2f", y);
  while (true) {
   x+=10;
   y+=5;
   z=0;
   Brain.Screen.printAt(1,20,"variables");
Brain.Screen.printAt(1,40," x = %d   ", x);
Brain.Screen.printAt(1,60, "y = %.2f", y);
  Brain.Screen.clearScreen();
Brain.Screen.setFillColor(blue);
Brain.Screen.drawCircle(x,y,5);
    wait(75, msec);
    if (x>300) {
      x=0;
      y=0;
    }
}
}

void dk(){
  Brain.Screen.printAt(1,20,"running dk");
  int x = 0;
  int y = 0;
  bool down=true;
  while(true){
  x++;
  if (y<256 && down){
    down=true;
    y+=10;
  }
  else {
    down=false;
    y=y-10;
    if (y<=1){
      down=true;
    }
  }
  Brain.Screen.setFillColor(blue);
Brain.Screen.drawCircle(x,y,5);
  }
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

//connor();

//william();

dk();
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {

   Brain.Screen.printAt(1,40,"running auton");

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
 int x = 2 ; 
 float y=2 ;
 int z = 10;
 bool flag = true;

 Brain.Screen.printAt(1,20,"variables");
 Brain.Screen.printAt(1,40, " x =  %d  ", x);
 Brain.Screen.printAt(1,60, "Y = %.2f ", y );

  while (true) {
   x=x+1;
   y=x*x;
   z=0;

Brain.Screen.printAt(1,20,"variables");
 Brain.Screen.printAt(1,40, " x =  %d  ", x);
 Brain.Screen.printAt(1,60, "Y = %.2f ", y );
 Brain.Screen.setFillColor(blue);
Brain.Screen.drawCircle(x,y,10);
 Brain.Screen.setFillColor(transparent);
    wait(100, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
Brain.Screen.clearScreen();

if(y>250){
  x=0;
  y=0;
}

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
