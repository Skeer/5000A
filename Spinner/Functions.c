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

void Up()
{
    motor[Spinner] = 127;
}

void Down()
{
    motor[Spinner] = -127;
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

void Forward(int left, int right)
{
    // Hidden cumulative left and right values... Don't worry about them.
    QLeft += left;
    QRight += right;

    // Change these values, read below. Constants are always positive.
    int leftConstant = 5;
    int rightConstant = 5;

    // Run Forward(85, 85) and see what values are the result.
    // Ex: If Forward(85, 85) grants you 96, 96 quad encoder values,
    // change the constant to -11
    // Retest the functions for consistancy.
    // Backwards should be the same, but you should test all main movement functions too.
    // Forwards, Backwards, TurnLeft, TurnRight
    // And if you want to test Left and Right, you can.
    while(SensorValue[QuadLeft] < QLeft - leftConstant || SensorValue[QuadRight] < QRight - rightConstant)
    {
        if(SensorValue[QuadLeft] < QLeft - leftConstant)
        {
            DriveLeft(30);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < QRight - rightConstant)
        {
            DriveRight(30);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// Arguemnts to this function should be negative.
void Backward(int left, int right)
{
    QLeft += left;
    QRight += right;

    int leftConstant = 18;
    int rightConstant = 18;

    while(SensorValue[QuadLeft] > QLeft + leftConstant || SensorValue[QuadRight] > QRight + rightConstant)
    {
        if(SensorValue[QuadLeft] > QLeft + leftConstant)
        {
            DriveLeft(-30);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] > QRight + rightConstant)
        {
            DriveRight(-30);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// left should be negative, right should be positive.
void TurnLeft(int left, int right)
{
    QLeft += left;
    QRight += right;

    int leftConstant = 10;
    int rightConstant = -9;

    while(SensorValue[QuadLeft] > QLeft + leftConstant || SensorValue[QuadRight] < QRight - rightConstant)
    {
        if(SensorValue[QuadLeft] > QLeft + leftConstant)
        {
            DriveLeft(-30);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < QRight - rightConstant)
        {
            DriveRight(30);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// left should be positive, right should be negative
void TurnRight(int left, int right)
{
    QLeft += left;
    QRight += right;

    int leftConstant = -2;
    int rightConstant = 2;

    while(SensorValue[QuadLeft] < QLeft - leftConstant || SensorValue[QuadRight] > QRight + rightConstant)
    {
        if(SensorValue[QuadLeft] < QLeft - leftConstant)
        {
            DriveLeft(30);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] > QRight + rightConstant)
        {
            DriveRight(-30);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// center should be positive.
void Left(int center)
{
    QCenter += center;

    int centerConstant = 0;

    LeftBrake();
    RightBrake();
    motor[DriveCenter] = 127;
    while(SensorValue[QuadCenter] < QCenter - centerConstant);
    motor[DriveCenter] = 0;
    SafetyBrake();
}

// center should be negative
void Right(int center)
{
    QCenter += center;

    int centerConstant = 0;

    LeftBrake();
    RightBrake();
    motor[DriveCenter] = -127;
    while(SensorValue[QuadCenter] > center + centerConstant);
    motor[DriveCenter] = 0;
    SafetyBrake();
}
/*
void Forward(int left, int right)
{
//    left += left;
//    right += right;

    while(SensorValue[QuadLeft] < left - 25 || SensorValue[QuadRight] < right - 25)
    {
        if(SensorValue[QuadLeft] < left - 25)
        {
            DriveLeft(0.6 * (left - SensorValue[QuadLeft]) + 20);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < right - 25)
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
//    left += left;
//    right += right;

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
    while(SensorValue[QuadLeft] > left + 34 || SensorValue[QuadRight] < Right - 3)
    {

        if(SensorValue[QuadLeft] > Left + 34)
        {
            DriveLeft(0.6 * (Left - SensorValue[QuadLeft]) - 20);
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
*/

int GetDonutCount()
{
    return (352 - SensorValue[DonutSonar]) / 51;
}

void ArmBase()
{
    // INFO: Moves arm to base position
    while(SensorValue[p1] + SensorValue[p2] < 2212)
    {
        Arm(275 - (SensorValue[p1] + SensorValue[p2]) / 10);
    }
    Trim();
}

void ArmWall()
{
    // INFO: Moves arm to wall position
    while(SensorValue[p1] + SensorValue[p2] < 2885)
    {
        Arm(540 - (SensorValue[p1] + SensorValue[p2]) / 6);
    }
    Trim();
}

void PickUp4()
{
    int count = GetDonutCount();

    count += 4;

    if(count > 6)
    {
        count = 6;
    }

    Arm(-127);
    while(SensorValue[p1] + SensorValue[p2] > 400);
    Trim();

    Forward(40, 40);

    Arm(-127);
    // Modify this value (40) if it isn't picking up enough,
    // if that still doesn't work, consider moving the Trim() function to after the last while loop.
    while(SensorValue[p1] + SensorValue[p2] > 40);
    Trim();

    while(GetDonutCount() < count);
}

void Drop(int count)
{
    count = GetDonutCount() - count;

    if(count < 0)
    {
        count = 0;
    }

    Down();
    while(GetDonutCount() > count);
    Up();
}
