/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      6/12/2024, 6:10:17 PM                                     */
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
motor LF=motor(PORT2, ratio6_1, true);
motor LB=motor(PORT1, ratio6_1, true);
motor RF=motor(PORT20, ratio6_1, false);
motor RB=motor(PORT11, ratio6_1, false);
inertial Gyro = inertial(PORT12);


// global variables
float PI = 3.14;
float D = 4.0;
float G= 3.0 / 7.0;

void gyroPrint()
{
float heading = Gyro.rotation(deg);
Brain.Screen.printAt(1, 60, "heading  =  %.2f. degrees", heading);
}

void drive(int lspeed, int rspeed, int wt){
  LF.spin(fwd,lspeed,pct);
  LB.spin(fwd,lspeed,pct);
  RF.spin(fwd,rspeed,pct);
  RB.spin(fwd,rspeed,pct);
  wait(wt,msec);
}

void driveBrake(){
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}

void inchDrive(float target){
  float x = 0.0;
  LF.setPosition(0.0, rev);
  while(x < target){
    drive(50,50,10);
    x= LF.position(rev)*G*PI*D;
  }

  driveBrake();
  
}

void gyroTurnRight(float target){
  float heading=0.0;
  Gyro.setRotation(0.0,deg);
  while(heading < target){
    drive(20,-20,10);
    heading=Gyro.rotation(deg);
  }
  driveBrake();
  Brain.Screen.printAt(1, 60, "heading  =  %.2f. degrees", heading);
}

void gyroTurnP(float target){
    float accuracy=0.5;
    float heading=0.0;
    float error=target-heading;
    float kp=0.7;
    float speed=100.0;
  Gyro.setRotation(0.0,deg);
  while(accuracy < fabs(error)){
    speed=kp*(error)+5.0*fabs(error)/error;
    drive(speed,-speed,10);
    heading=Gyro.rotation(deg);
    error=target-heading;

  }
  driveBrake();
}


void gyroTurnP2(float target){
  int count=0;
    float accuracy=1.0;
    float heading=0.0;
    float error=target-heading;
    float kp=0.7;
    float speed=100.0;
  Gyro.setRotation(0.0,deg);
  while(count<10){
    speed=kp*(error);
    drive(speed,-speed,10);
    heading=Gyro.rotation(deg);
    error=target-heading;
if(accuracy > fabs(error)){
  count++;
}
else{
  count=0;
}
  }
  driveBrake();
}

void gyroCurve(float target, float curve){
    float accuracy=0.5;
    float heading=0.0;
    float error=target-heading;
    float kp=0.7;
    float speed=100.0;
  Gyro.setRotation(0.0,deg);
  if (curve<0) curve=fabs(curve);
  if (curve>100) curve = 100;
  while(accuracy < fabs(error)){
    speed=kp*(error)+5.0*fabs(error)/error;
    drive(speed+curve,speed-curve,10);
    heading=Gyro.rotation(deg);
    error=target-heading;

  }
  driveBrake();
}

void dkDrive(){
  int count=1;
  while(count <=4){
  inchDrive(48);
  wait(500,msec);
  gyroTurnP(90);
  count=count+1;
  }
}

void Williamdrive(){
   for (int i = 0; i < 4; i++) {
   inchDrive(90);
  wait(250,msec);
  gyroTurnP2(90);
   }
  driveBrake();
}

void LucasDrive(){
 inchDrive(95);  
  wait(250,msec);
  gyroTurnP2(90);  
  driveBrake();
}

void connorDrive(){
   inchDrive(100); 
  wait(250,msec);
  gyroTurnP(90);
  driveBrake();
  inchDrive(100);
  wait(250, msec);
  gyroTurnP(90);
  driveBrake();
  inchDrive(100);
  wait(250, msec);
  gyroTurnP(90);
  driveBrake();
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
//dkDrive();
Williamdrive();
//LucasDrive();
//inchDrive(72.0);
//connorDrive();



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
  while (true) {
 gyroPrint();

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
