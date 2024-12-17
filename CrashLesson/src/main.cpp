/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      12/15/2024, 2:08:36 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Controller1;
motor LeftFront=motor(PORT1,ratio18_1,true);
motor LeftBack=motor(PORT2,ratio18_1,true);
motor LeftMid=motor(PORT3,ratio18_1,true);
motor RightFront(PORT4,ratio18_1,false);
motor RightBack(PORT5,ratio18_1,false);
motor RightMid(PORT6,ratio18_1,false);
// define your global instances of motors and other devices here
void drive(int lspeed, int rspeed, int wt){
LeftFront.spin(forward,lspeed,percent);
LeftBack.spin(forward,lspeed,percent);
LeftMid.spin(forward,lspeed,percent);
RightFront.spin(forward,rspeed,percent);
RightBack.spin(forward,rspeed,percent);
RightMid.spin(forward,rspeed,percent);
wait(wt,msec);
}

void driveBrake(){
LeftFront.stop(brake);
LeftBack.stop(brake);
LeftMid.stop(brake);
RightFront.stop(brake);
RightBack.stop(brake);
RightMid.stop(brake);
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

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  //auto to drive by time and speed
  drive(50,50,1000);
  driveBrake();
  drive(50,-50,500);
  driveBrake();
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
 int lstick=0;
 int rstick=0;
  while (true) {
    lstick=Controller1.Axis3.position(percent);
    rstick=Controller1.Axis2.position(percent);
    drive(lstick,rstick,20);
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
