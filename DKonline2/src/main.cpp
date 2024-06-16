/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      6/16/2024, 12:09:29 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain Brain;
controller Controller1=controller(primary);

void drawAxis(){
  int x=0;
  int y=0;
  while(x<480){
Brain.Screen.printAt(x,20,"%d",x);
x=x+50;
}
 while(y<272){
Brain.Screen.printAt(0,y,"%d",y);
y=y+50;
}
}

void drawPoints(int x, int y, int r=2){
  Brain.Screen.drawCircle(x,y,r);
}

void drawMyLine(float m, float b){
  float x=0;
  float y = 0;
  while (x<480){
    y= m*x+b;
    drawPoints(x,y);
    x= x + 10;
    wait(50,msec);
  }
}
void dkNumbers(){
  int x =0;
  float y = 3.141519;
  Brain.Screen.printAt(0,20,"Variables");
  while(x<400){
  Brain.Screen.printAt(0,40,"x =  %d  value",x);
  Brain.Screen.printAt(0,60, " y = %.2f  float", y);
  x=x+1;
  y=y+1.5;
  wait(50, msec);
  }
Brain.Screen.printAt(90,100,"done counting");
}

void drawSomething(){
  Brain.Screen.drawRectangle(50,50,100,50);
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawCircle(75,150,50);
  Brain.Screen.setFillColor(transparent);
}

void drawBall(){
  float x=0.0;
  float y=0.0;
  Brain.Screen.setFillColor(red);
  while(x<400){
    Brain.Screen.clearScreen();
    Brain.Screen.drawCircle(x,y,5);
    x=x+1;
    y=y+.5;
    wait(10,msec);
    
  }
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.printAt(90,100,"done ");
}

void drawDK(){
  drawAxis();
  Brain.Screen.setFillColor(blue);
  drawMyLine(-1.0,250);
  Brain.Screen.setFillColor(red);
  drawMyLine(1,-250);
  Brain.Screen.setFillColor(transparent);

}

void drawAaron(){
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(25,50,100,50);
Brain.Screen.setFillColor(yellow);
Brain.Screen.drawRectangle(50,100,200,100);
Brain.Screen.setFillColor(green);
 Brain.Screen.drawRectangle(75,150,300,150);
Brain.Screen.setFillColor(red);
Brain.Screen.drawRectangle(50,100,200,100);
Brain.Screen.setFillColor(orange);
Brain.Screen.drawRectangle(100,200,400,200);
Brain.Screen.setFillColor(transparent);
}
void drawCube() {
  float x = 0.0;
  float y = 0.0;
   Brain.Screen.setFillColor(green);
   while(x < 400) {
    Brain.Screen.drawRectangle(x, y, 50, 50);
    x = x + 1;
    y = y + 0.4;
    wait(10, msec);
   
   }
    Brain.Screen.setFillColor(transparent);
}
void draw100(){
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawLine(50,50,50,150);
  Brain.Screen.drawCircle(125,100,20);
  Brain.Screen.drawCircle(200,100,20);
  wait(3, sec);
  Brain.Screen.clearScreen();
}
void drawPercentSign(){
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawCircle(100,100,20);
  Brain.Screen.drawCircle(150,150,20);
  Brain.Screen.drawLine(150,100,100,150);
  wait(3, sec);
  Brain.Screen.clearScreen();
}
void drawFace(){
  int a = 10;
  int w = 25;
  int x = 50; 
  int y = 200;
  int z = 150;
  while(x<150){
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(yellow);
    Brain.Screen.drawCircle(100,75,a);
    Brain.Screen.drawCircle(350,75,a);
    Brain.Screen.drawRectangle(y,z,x,w);
    a++;
    y--;
    z--;
    x=x+2;
    w=w+2;
    wait(20,msec);
  }
}
void drawRectangles(){
Brain.Screen.setFillColor(orange);
Brain.Screen.drawRectangle(40,50,100,40);
Brain.Screen.setFillColor(blue);
Brain.Screen.drawRectangle(70,100,200,100);
Brain.Screen.setFillColor(red);
Brain.Screen.drawRectangle(70,60,300,60);
Brain.Screen.setFillColor(green);
Brain.Screen.drawRectangle(50,100,200,100);
Brain.Screen.setFillColor(transparent);
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
Brain.Screen.printAt(0,20,"Pre Auton Running");
  drawSomething();
  
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
   Brain.Screen.clearScreen();
  Brain.Screen.printAt(200,50,"DK code");
  drawDK();
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(200,50,"Aaron code");
  drawAaron();
  wait(1500,msec);
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(200,50,"Lucas code");
  drawCube();
   wait(1500,msec);
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(200,50,"Zachary code");
    drawRectangles();
      wait(1500,msec);
    Brain.Screen.clearScreen();
  drawAxis();
  Brain.Screen.printAt(200,50,"Daniel code");
   draw100();
    Brain.Screen.setFillColor(transparent);
    Brain.Screen.printAt(200,50,"Daniel code");
  drawPercentSign();
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.printAt(200,50,"Daniel code");
  drawFace();
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.printAt(200,50,"Daniel code");
  wait(1500,msec);
 
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
   Brain.Screen.printAt(0,60,"Driver is Running");
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
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
