void DriveLeft(int value)
{
    motor[DriveLeftFront] = value;
    motor[DriveLeftRear] = value;
}

void DriveRight(int value)
{
    motor[DriveRightFront] = value;
    motor[DriveRightRear] = value;
}

void Drive(float multiplier)
{
    int x = vexRT[Ch4];
    int y = vexRT[Ch3];
    DriveLeft((y + x) * multiplier);
    DriveRight((y - x) * multiplier);

    if(vexRT[Btn5D])
    {
        // left
        motor[DriveCenter] = 127;
    }
    else if(vexRT[Btn6D])
    {
        // right
        motor[DriveCenter] = -127;
    }
    else
    {
        motor[DriveCenter] = 0;
    }
}

void Arm(int y = vexRT[Ch2])
{
    motor[Arm1] = y;
    motor[Arm2] = y;
    motor[Arm3] = y;
    motor[Arm4] = y;
}

void Trim()
{
    motor[Arm1] = 20;
    motor[Arm2] = 20;
    motor[Arm3] = 20;
    motor[Arm4] = 20;
}

void Open()
{
    motor[Claw] = 127;
}

void Close()
{
    motor[Claw] = -127;
}

void Stop()
{
    motor[DriveCenter] = 0;
    DriveLeft(0);
    DriveRight(0);
}

void LeftBrake()
{
    motor[DriveLeftFront] = 30;
    motor[DriveLeftRear] = -30;
}

void RightBrake()
{
    motor[DriveRightFront] = 30;
    motor[DriveRightRear] = -30;
}

void SafetyBrake()
{
    LeftBrake();
    RightBrake();
    wait1Msec(100);
    Stop();
}
/*
void Move(int center, int left, int right)
{
    while(true)
    {
        if(SensorValue[QuadCenter] > center + 5)
        {
            motor[DriveCenter] = -127;
        }
        else if(SensorValue[QuadCenter] < center - 5)
        {
            motor[DriveCenter] = 127;
        }
        else if(SensorValue[QuadCenter] > center)
        {
            motor[DriveCenter] = -20;
        }
        else if(SensorValue[QuadCenter] < center)
        {
            motor[DriveCenter] = 20;
        }
        else
        {
            motor[DriveCenter] = 0;
        }

        if(SensorValue[QuadLeft] > left + 20)
        {
            motor[DriveLeftFront] = 0.6 * (left - SensorValue[QuadLeft]) - 20;
            motor[DriveLeftRear] = 0.6 * (left - SensorValue[QuadLeft]) - 20;
        }
        else if(SensorValue[QuadLeft] < left - 20)
        {
            motor[DriveLeftFront] = 0.6 * (left - SensorValue[QuadLeft]) + 20;
            motor[DriveLeftRear] = 0.6 * (left - SensorValue[QuadLeft]) + 20;
        }
        else if(SensorValue[QuadLeft] > left + 5)
        {
            motor[DriveLeftFront] = -25;
            motor[DriveLeftRear] = -25;
        }
        else if(SensorValue[QuadLeft] < left - 5)
        {
            motor[DriveLeftFront] = 25;
            motor[DriveLeftRear] = 25;
        }
        else
        {
            motor[DriveLeftFront] = -20;
            motor[DriveLeftRear] = 20;
        }

        if(SensorValue[QuadRight] > right + 20)
        {
            motor[DriveRightFront] = 0.6 * (right - SensorValue[QuadRight]) - 20;
            motor[DriveRightRear] = 0.6 * (right - SensorValue[QuadRight]) - 20;
        }
        else if(SensorValue[QuadRight] < right - 20)
        {
            motor[DriveRightFront] = 0.6 * (right - SensorValue[QuadRight]) + 20;
            motor[DriveRightRear] = 0.6 * (right - SensorValue[QuadRight]) + 20;
        }
        else if(SensorValue[QuadRight] > right + 5)
        {
            motor[DriveRightFront] = -25;
            motor[DriveRightRear] = -25;
        }
        else if(SensorValue[QuadRight] < right - 5)
        {
            motor[DriveRightFront] = 25;
            motor[DriveRightRear] = 25;
        }
        else
        {
            motor[DriveRightFront] = -20;
            motor[DriveRightRear] = 20;
        }

        if(SensorValue[QuadCenter] >= center - 5 && SensorValue[QuadCenter] <= center + 5 && SensorValue[QuadLeft] >= left - 5 && SensorValue[QuadLeft] <= left + 5 && SensorValue[QuadRight] >= right - 5 && SensorValue[QuadRight] <= right + 5)
        {
            wait1Msec(100);

            if(SensorValue[QuadCenter] >= center - 5 && SensorValue[QuadCenter] <= center + 5 && SensorValue[QuadLeft] >= left - 5 && SensorValue[QuadLeft] <= left + 5 && SensorValue[QuadRight] >= right - 5 && SensorValue[QuadRight] <= right + 5)
            {

                Stop();
                break;
            }
        }
    }
}

void Move(int quadCenter, int quadLeft, int quadRight)
{
// Tolerance of 3
// Working to replace all movement functions with this.
while(true)
{
if(SensorValue[QuadCenter] < quadCenter - 3 || SensorValue[QuadCenter] > quadCenter + 3 || SensorValue[QuadLeft] < quadLeft - 3 || SensorValue[QuadLeft] > quadLeft + 3 || SensorValue[QuadRight] < quadRight - 3 || SensorValue[QuadRight] > quadRight + 3)
{
// needs to go right
if(SensorValue[QuadCenter] > quadCenter + 3)
{
// see if this needs deceleration...
motor[DriveCenter] = quadCenter - SensorValue[QuadCenter] - 97;
}
// needs to go left
else if(SensorValue[QuadCenter] < quadCenter - 3)
{
motor[DriveCenter] = quadCenter - SensorValue[QuadCenter] + 97;
}
else
{
motor[DriveCenter] = 0;
}

// needs to go backward
if(SensorValue[QuadLeft] > quadLeft + 3)
{
motor[DriveLeftFront] = 0.6 * (quadLeft - SensorValue[QuadLeft]) - 22;
motor[DriveLeftRear] = 0.6 * (quadLeft - SensorValue[QuadLeft]) - 22;
}
// needs to go forward
else if(SensorValue[QuadLeft] < quadLeft - 3)
{
motor[DriveLeftFront] = 0.6 * (quadLeft - SensorValue[QuadLeft]) + 22;
motor[DriveLeftRear] = 0.6 * (quadLeft - SensorValue[QuadLeft]) + 22;
}
else
{
motor[DriveLeftFront] = 0;
motor[DriveLeftRear] = 0;
}

// needs to go backward
if(SensorValue[QuadRight] > quadRight + 3)
{
motor[DriveRightFront] = 0.6 * (quadRight - SensorValue[QuadRight]) - 22;
motor[DriveRightRear] = 0.6 * (quadRight - SensorValue[QuadRight]) - 22;
}
// needs to go forward
else if(SensorValue[QuadRight] < quadRight - 3)
{
motor[DriveRightFront] = 0.6 * (quadRight - SensorValue[QuadRight]) + 22;
motor[DriveRightRear] = 0.6 * (quadRight - SensorValue[QuadRight]) + 22;
}
else
{
motor[DriveRightFront] = 0;
motor[DriveRightRear] = 0;
}
}
else
{
wait1Msec(250);

if(SensorValue[QuadCenter] >= quadCenter - 3 && SensorValue[QuadCenter] <= quadCenter + 3 && SensorValue[QuadLeft] >= quadLeft - 3 && SensorValue[QuadLeft] <= quadLeft + 3 && SensorValue[QuadRight] >= quadRight - 3 && SensorValue[QuadRight] <= quadRight + 3)
{
Stop();
break;
}

}
}
}
*/

void Forward(int left, int right)
{
    while(SensorValue[QuadLeft] < left - 10 || SensorValue[QuadRight] < right - 10)
    {
        if(SensorValue[QuadLeft] < left - 10)
        {
            DriveLeft(0.6 * (left - SensorValue[QuadLeft]) + 20);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < right - 10)
        {
            DriveRight(0.6 * (right - SensorValue[QuadRight]) + 20);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

void Backward(int left, int right)
{
    while(SensorValue[QuadLeft] > left + 10 || SensorValue[QuadRight] > right + 10)
    {
        if(SensorValue[QuadLeft] > left + 10)
        {
            DriveLeft(0.6 * (left - SensorValue[QuadLeft]) - 20);
        }
        else
        {
            DriveLeft(-20);
        }

        if(SensorValue[QuadRight] > right + 10)
        {
            DriveRight(0.6 * (right - SensorValue[QuadRight]) - 20);
        }
        else
        {
            DriveRight(-20);
        }
    }
    SafetyBrake();
}

void TurnLeft(int left, int right)
{
    while(SensorValue[QuadLeft] > left + 34 || SensorValue[QuadRight] < right - 3)
    {
        if(SensorValue[QuadLeft] > left + 34)
        {
            DriveLeft(0.6 * (left - SensorValue[QuadLeft]) - 20);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < right - 3)
        {
            DriveRight(0.6 * (right - SensorValue[QuadRight]) + 20);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

void TurnRight(int left, int right)
{
    while(SensorValue[QuadLeft] < left - 8 || SensorValue[QuadRight] > right + 19)
    {
        if(SensorValue[QuadLeft] < left - 8)
        {
            DriveLeft(0.6 * (left - SensorValue[QuadLeft]) + 20);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] > right + 19)
        {
            DriveRight(0.6 * (right - SensorValue[QuadRight]) - 20);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

void Left(int center)
{
    LeftBrake();
    RightBrake();
    motor[DriveCenter] = 127;
    while(SensorValue[QuadCenter] < center - 3);
    motor[DriveCenter] = -20;
    SafetyBrake();
}

void Right(int center)
{
    LeftBrake();
    RightBrake();
    motor[DriveCenter] = -127;
    while(SensorValue[QuadCenter] > center + 3);
    motor[DriveCenter] = 20;
    SafetyBrake();
}

int GetDonutCount()
{
    return (352 - SensorValue[DonutSonar]) / 51;
}

void ArmBase()
{
    // INFO: Moves arm to base position
    while(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] < 2212)
    {
        Arm(275 - (SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2]) / 10);
    }
    Trim();
}

void ArmWall()
{
    // INFO: Moves arm to wall position
    while(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] < 2885)
    {
        Arm(540 - (SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2]) / 6);
    }
    Trim();
}
