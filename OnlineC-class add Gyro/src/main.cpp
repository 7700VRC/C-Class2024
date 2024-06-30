/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       georgekirkman                                             */
/*    Created:      6/5/2024, 6:08:47 PM                                      */
/*    Description:  V5 project    June 30, 2024 add gyro                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// define your global instances of motors and other devices here
brain  Brain;
controller Controller1 = controller(primary);
motor LF = motor(PORT2, ratio6_1, true);
motor RF = motor(PORT20, ratio6_1, false);
motor LB = motor(PORT1, ratio6_1, true);
motor RB = motor(PORT11, ratio6_1, false);

inertial Gyro = inertial(PORT12);


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

float kp=0.7;
float accuracy=2.0;
int stop=20;

void gyroTurnP(float target){
float heading = 0.0;
float error= target - heading;
int speed=0;

int count =0;
Gyro.setRotation(0.0, degrees);
while(count<stop){
speed= kp*error;
  drive(speed, -speed, 10);
  heading = Gyro.rotation(degrees);
  error=target - heading;
 if (fabs(error)<accuracy){
  count++;
 }
 else{
  count=0;
 }

}

driveBrake();
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
void TurnR(int lspeed, int rspeed,int wt){
    LF.spin(fwd, lspeed, pct);
    LB.spin(fwd, lspeed, pct);
    RF.spin(reverse, rspeed, pct);
    RB.spin(reverse, rspeed, pct);
    wait(wt,msec);
}
void GyrocurveP(float target, float curve,float accuracy,int count,float kp){
    float heading= 0.0;
    float error= target- heading;
    int speed=0;

    Gyro.setRotation(0.0,degrees);
    while(count<20){
        TurnR(speed, -speed/curve, 10);
        heading=Gyro.rotation(degrees);
        error= target- heading;
        speed= kp*error;
        if(fabs (error)<accuracy){
            count++;
        }
        else{
            count=0;
        }
    };
driveBrake();
}
void dk(){
  Brain.Screen.printAt(1,20,"running dk");
  kp=5.0;
  accuracy= 2.0;
  stop=20;

  gyroTurnP(135);

  wait(500, msec);

  gyroTurnP(-45);

  
}


  void gyroCode(float target, float curve, float accuracy, int count, float kp){
    float heading=0.0;
    float error=target-heading;
    float speed=100.0;
  Gyro.setRotation(0.0,deg);
  while(count<20){
    speed=kp*(error);
   if (target>0){
    drive(speed*curve,speed,10);
   }
   else{
    
      drive(speed,speed*curve,10);
   }
    heading=Gyro.rotation(degrees);
    error=target-heading;
if(fabs(error)< accuracy){
  count++;
}
else{
  count=0;
}
  }
  driveBrake();
}

void aaron(){
  Brain.Screen.printAt(1,20,"running aaron");
  gyroCode(90, 2, 1.0, 0, 1.0);

  
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

//dk();
  
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

aaron();
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
