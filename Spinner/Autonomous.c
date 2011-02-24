#pragma config(Sensor, in1,    p1,                  sensorPotentiometer)
#pragma config(Sensor, in2,    p2,                  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  QuadCenter,          sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  QuadLeft,            sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  QuadRight,           sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  DonutSonar,          sensorSONAR_mm)
#pragma config(Sensor, dgtl9,  j1,                  sensorTouch)
#pragma config(Sensor, dgtl10, j2,                  sensorTouch)
#pragma config(Sensor, dgtl11, j3,                  sensorTouch)
#pragma config(Sensor, dgtl12, j4,                  sensorTouch)
#pragma config(Motor,  port1,           DriveCenter,   tmotorNormal, openLoop)
#pragma config(Motor,  port2,           DriveLeftFront, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           DriveLeftRear, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           DriveRightFront, tmotorNormal, openLoop)
#pragma config(Motor,  port5,           DriveRightRear, tmotorNormal, openLoop)
#pragma config(Motor,  port6,           Arm1,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port7,           Spinner,       tmotorNormal, openLoop)
#pragma config(Motor,  port8,           Arm3,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           Arm4,          tmotorNormal, openLoop)
#pragma config(Motor,  port10,          Arm2,          tmotorNormal, openLoop, reversed)

int QLeft;
int QRight;
int QCenter;
int Velocity;
int VelocityLeft;
int VelocityRight;

#include "Functions.c"

void pre_auton()
{
    QLeft = 0;
    QRight = 0;
    QCenter = 0;
    Velocity = 0;

    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;
}

task main()
{
    pre_auton();

    Up();

    ArmBase();

    Forward(101, 101);

    PickUp4();

    ArmBase();

    Left(330);

    Forward(180, 180);

    Drop(3);

    ArmWall();

    Backward(-201, -201);

    TurnRight(192, -192);

    Forward(260, 260);

    DropAll();

    Up();

    Backward(-120, -120);
}
