/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      6/16/2024, 10:19:14 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
brain  Brain;
controller Controller1 = controller(primary);
//7899C

// motor LF = motor(PORT2, ratio6_1, false);
// motor LM = motor(PORT15, ratio6_1, true);
// motor LB = motor(PORT14, ratio6_1, false);
// motor RF = motor(PORT9, ratio6_1, true);
// motor RM = motor(PORT16, ratio6_1, false);
// motor RB = motor(PORT17, ratio6_1, true);
// // define your global variables
// float D=2.75;  //wheel diameter
// float G=1.0;  //Gear ratio external
// float PI= 3.14;  //math constant of circles

//
//7899B 
/*
motor LF = motor(PORT5, ratio6_1, true);
motor LM = motor(PORT6, ratio6_1, true);
motor LB = motor(PORT10, ratio6_1, true);
motor RF = motor(PORT16, ratio6_1, false);
motor RM = motor(PORT2, ratio6_1, false);
motor RB = motor(PORT1, ratio6_1, false);
// define your global variables
float D=2.75;  //wheel diameter
float G=3.0/4.0;  //Gear ratio external
float PI= 3.14;  //math constant of circles
*/
//7899B 4inch 

motor LF = motor(PORT11, ratio6_1, true);
motor LB = motor(PORT1, ratio6_1, true);
motor RF = motor(PORT20, ratio6_1,false);
motor RB = motor(PORT10, ratio6_1,false);
motor RM = motor(PORT2, ratio6_1, true);
motor LM = motor(PORT3, ratio6_1,true);
// define your global variables
float D=4.0;  //wheel diameter
float G=3.0/6.0;  //Gear ratio external
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
   LM.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
   RM.stop(brake);
  RB.stop(brake);
}

void driveCoast(){
  LF.stop(coast);
  LM.stop(coast);
  LB.stop(coast);
  RF.stop(coast);
  RM.stop(coast);
  RB.stop(coast);
}

void drawAxis(){
  int x=0;
  int y=0;
  while(x<480){
Brain.Screen.printAt(x,20,"%d",x/50);
x=x+50;
}
 while(y<272){
Brain.Screen.printAt(0,y,"%d",y);
y=y+50;
}
}

void drawPoints(float x, int y, int r=2){
  Brain.Screen.drawCircle(x,y,r);
}

void drawMyLine(float m, float b){
  float x=0;
  float y = 0;
  while (x<480){
    y= m*x+b;
    drawPoints(x,y);
    x= x + 10;
  }
}

void speedGraph(){
  int count=0;
  int speed= 0;
  int flag=0;
  float x=0.0;
  LF.setPosition(0,rev);
  float t=0.0;
     Brain.Screen.setFillColor(green);
  Brain.Screen.setPenColor(green);

  while(t<10&&flag<2){
  drive(100,100,10);
  t=t+.01;
  count++;
  speed=LF.velocity(pct);
  if(speed>=100){
    flag++;
  }
  else flag=0;
  if(count>=5){
    count=0;
    drawPoints(t*50+100,speed);
  }

  }
  speed=LF.velocity(rpm)*PI*D*G/60;
x= LF.position(rev)*PI*D*G;
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(white);
  Brain.Screen.printAt(200, 170, "time = %.3f sec", t);
    Brain.Screen.printAt(200, 200, "distance = %.3f inch", x);
        Brain.Screen.printAt(200, 240, "speed = %.3f inch/sec", speed);

  
  
 Brain.Screen.setFillColor(red);
  Brain.Screen.setPenColor(red);
  while(t<20){
    drive(0,0,10);
  //driveCoast();
  t=t+.01;
  count++;
  speed=LF.velocity(pct);
  if(count>=5){
    count=0;
    drawPoints(t*50+100,speed);
  }

  }
  driveBrake();
    Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(white);
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
drawAxis();
  //wait(1000,msec);


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
  speedGraph();
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
  // User control code here, inside the loop
  while (1) {
    
    drive(Controller1.Axis3.position(pct),Controller1.Axis2.position(pct),10);
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
