#pragma config(Sensor, in1,    ArmPotentiometer1,   sensorPotentiometer)
#pragma config(Sensor, in2,    ArmPotentiometer2,   sensorPotentiometer)
#pragma config(Sensor, in3,    ClawPotentiometer,   sensorPotentiometer)
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
#pragma config(Motor,  port7,           Claw,          tmotorNormal, openLoop)
#pragma config(Motor,  port8,           Arm3,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port9,           Arm4,          tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,          Arm2,          tmotorNormal, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
#include "Functions.c"
//#include "Alpha.c"
//#include "Beta.c"
//#include "Gamma.c"
#include "Delta.c"

void pre_auton()
{
    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;
}

task autonomous()
{
    // TODO: Inverse poten

    // Delta for reference
    //Up();
    Trim();

    if(SensorValue[j1]) // blue
    {
        if(SensorValue[j2]) //normal
        {
            //Gamma();
        }
        else // oppo
        {
            //Alpha();
        }
    }
    else // red
    {
        if(SensorValue[j2]) // normal
        {
            //Beta();
        }
        else // oppo
        {
            Delta();
        }
    }
}

task usercontrol()
{
    if(vexRT[Btn5D] && vexRT[Btn5U] && vexRT[Btn6D] && vexRT[Btn6U])
    {
        StartTask(autonomous);
        wait1Msec(20000);
        StopTask(autonomous);
    }

    float multiplier = 1;
    bool wall = false;
    bool base = false;
    bool down = false;

    while (true)
    {
        Drive(multiplier);

        if(vexRT[Btn7U])
        {
            wall = true;
            base = false;
            down = false;
        }
        else if(vexRT[Btn7D])
        {
            wall = false;
            base = true;
            down = false;
        }
        else if(vexRT[Btn7L])
        {
            wall = false;
            base = false;
            down = true;
        }

        if(vexRT[Ch2] > 20 || vexRT[Ch2] < -20)
        {
            Arm();
            wall = false;
            base = false;
            down = false;
        }
        else if(wall)
        {
            if(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] != 2891) //2502 -> 2891
            {
                Arm(520 - (SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2]) / 6);
            }
            else
            {
                wall = false;
            }
        }
        else if(base)
        {
            if(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] != 2212) //2060 -> 2212
            {
                Arm(271 - (SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2]) / 10);
            }
            else
            {
                base = false;
            }
        }
        else if(down)
        {
            if(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] > 12)
            {
                Arm(-127);
            }
            else
            {
                down = false;
            }
        }
        else
        {
            Trim();
        }

        // 139 for open max

        if(vexRT[Btn6U])
        {
            motor[Claw] = 127;
        }
        else if(vexRT[Btn5U])
        {
            motor[Claw] = -127;
        }
        else
        {
            motor[Claw] = 0;
        }

        if(vexRT[Btn8D])
        {
            multiplier = 0.25;
        }
        else if(vexRT[Btn8L])
        {
            multiplier = 0.5;
        }
        else if(vexRT[Btn8U])
        {
            multiplier = 0.75;
        }
        else if(vexRT[Btn8R])
        {
            multiplier = 1;
        }
    }
}
