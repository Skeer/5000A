bool Out = false;

task descore()
{
    if(Out)
    {
        motor[Descore] = -127;
    }
    else
    {
        motor[Descore] = 127;
    }
    wait1Msec(1250);
    motor[Descore] = 0;
    Out = !Out;
}

// Velocity values
int Velocity;
int LeftVelocity;
int RightVelocity;

// Realtime velocity calculator
task velocitycalculator()
{
    int leftInitial;
    int rightInitial;
    int leftFinal;
    int rightFinal;

    while(true)
    {
        leftInitial = SensorValue[QuadLeft];
        rightInitial = SensorValue[QuadRight];
        wait1Msec(100);
        leftFinal = SensorValue[QuadLeft];
        rightFinal = SensorValue[QuadRight];

        Velocity = (leftFinal + rightFinal - leftInitial - rightInitial) * 5;
        LeftVelocity = (leftFinal - leftInitial) * 10;
        RightVelocity = (rightFinal - rightInitial) * 10;
    }
}

// Actual encoder values
int QCenter;
int QLeft;
int QRight;

// Sets the left drive motors to value
void DriveLeft(int value)
{
    motor[DriveLeftFront] = value;
    motor[DriveLeftRear] = value;
}

// Sets the right drive motors to value
void DriveRight(int value)
{
    motor[DriveRightFront] = value;
    motor[DriveRightRear] = value;
}

// User control drive
// using arcade and multiplied by multiplier.
// Center drive does not get affected my multiplier
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

// Arm control for both user and autonomous
void Arm(int y = vexRT[Ch2])
{
    motor[Arm1] = y;
    motor[Arm2] = y;
    if(y > 0)
    {
        SensorValue[dgtl11] = 0;
        SensorValue[dgtl12] = 0;
    }
    else
    {
        SensorValue[dgtl11] = 1;
        SensorValue[dgtl12] = 1;
    }
}

// Continuously powering arm motors when idle
void Trim()
{
    // Possiby no need of this function anymore because of tension
    motor[Arm1] = 15;
    motor[Arm2] = 15;
}

// Spinning upwards
void Up()
{
    motor[Spinner1] = 127;
    motor[Spinner2] = 127;
}

// Spinning downwards
void Down()
{
    motor[Spinner1] = -127;
    motor[Spinner2] = -127;
}

// Stopping all drive motors
void Stop()
{
    motor[DriveCenter] = 0;
    DriveLeft(0);
    DriveRight(0);
}

// Applying brake to the left side
void LeftBrake()
{
    motor[DriveLeftFront] = 30;
    motor[DriveLeftRear] = -30;
}

// Applying brake to the right side
void RightBrake()
{
    motor[DriveRightFront] = 30;
    motor[DriveRightRear] = -30;
}

// Safety brake feature makes sure the robot has been braking for at least 100 milliseconds before continuing
void SafetyBrake()
{
    LeftBrake();
    RightBrake();
    wait1Msec(100);
    Stop();
}

// Moves robot forward for left and right distance
void Forward(int left, int right, int time = 20000)
{
    // Formatting user input values
    if(left < 0)
    {
        left = -left;
    }
    if(right < 0)
    {
        right = -right;
    }

    ClearTimer(T1);

    // Hidden cumulative left and right values...
    QLeft += left;
    QRight += right;

    // Calibrating left and right drives
    // The larger it is, the earlier the drive stops
    // The smaller it is, the later the drive stops
    int leftConstant = 5;
    int rightConstant = 5;

    // Loop until both conditions have been satisfied
    while(time1(T1) < time && (SensorValue[QuadLeft] < QLeft - leftConstant || SensorValue[QuadRight] < QRight - rightConstant))
    {
        // If left needs to move
        if(SensorValue[QuadLeft] < QLeft - leftConstant)
        {
            // Driving left side
            DriveLeft(40);
        }
        else
        {
            // Stopping left side
            DriveLeft(0);
        }

        if(SensorValue[QuadRight] < QRight - rightConstant)
        {
            // Driving right side
            DriveRight(40);
        }
        else
        {
            // Stopping right side
            DriveLeft(0);
        }
    }
    // Applying safety brake for safety measures
    SafetyBrake();
}

// Moves robot backward for left and right distance
void Backward(int left, int right)
{
    if(left > 0)
    {
        left = -left;
    }
    if(right > 0)
    {
        right = -right;
    }

    QLeft += left;
    QRight += right;

    int leftConstant = 18;
    int rightConstant = 18;

    while(SensorValue[QuadLeft] > QLeft + leftConstant || SensorValue[QuadRight] > QRight + rightConstant)
    {
        if(SensorValue[QuadLeft] > QLeft + leftConstant)
        {
            DriveLeft(-40);
        }
        else
        {
            DriveLeft(0);
        }

        if(SensorValue[QuadRight] > QRight + rightConstant)
        {
            DriveRight(-40);
        }
        else
        {
            DriveLeft(0);
        }
    }
    SafetyBrake();
}

// Turns the robot left for left and right distance
void TurnLeft(int left, int right)
{
    if(left > 0)
    {
        left = -left;
    }
    if(right < 0)
    {
        right = -right;
    }

    QLeft += left;
    QRight += right;

    int leftConstant = 10;
    int rightConstant = -9;

    while(SensorValue[QuadLeft] > QLeft + leftConstant || SensorValue[QuadRight] < QRight - rightConstant)
    {
        if(SensorValue[QuadLeft] > QLeft + leftConstant)
        {
            DriveLeft(-40);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] < QRight - rightConstant)
        {
            DriveRight(40);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// Turns the robot right for left and right distance
void TurnRight(int left, int right)
{
    if(left < 0)
    {
        left = -left;
    }
    if(right > 0)
    {
        right = -right;
    }

    QLeft += left;
    QRight += right;

    int leftConstant = -2;
    int rightConstant = 2;

    while(SensorValue[QuadLeft] < QLeft - leftConstant || SensorValue[QuadRight] > QRight + rightConstant)
    {
        if(SensorValue[QuadLeft] < QLeft - leftConstant)
        {
            DriveLeft(40);
        }
        else
        {
            LeftBrake();
        }

        if(SensorValue[QuadRight] > QRight + rightConstant)
        {
            DriveRight(-40);
        }
        else
        {
            RightBrake();
        }
    }
    SafetyBrake();
}

// Moves the robot left for left distance
void Left(int center)
{
    if(center < 0)
    {
        center = -center;
    }

    QCenter += center;

    int centerConstant = 0;

    LeftBrake();
    RightBrake();
    motor[DriveCenter] = 127;
    while(SensorValue[QuadCenter] < QCenter - centerConstant);
    motor[DriveCenter] = 0;
    SafetyBrake();
}

// Moves the robot right for right distance
void Right(int center)
{
    if(center > 0)
    {
        center = -center;
    }

    QCenter += center;

    int centerConstant = 0;

    LeftBrake();
    RightBrake();
    motor[DriveCenter] = -127;
    while(SensorValue[QuadCenter] > center + centerConstant);
    motor[DriveCenter] = 0;
    SafetyBrake();
}

// Retrieves the count of rings currently in possession of
int GetRingCount()
{
    return (352 - SensorValue[DonutSonar]) / 51;
}

// Moves the arm to base height
void ArmBase()
{
    ClearTimer(T1);
    while(SensorValue[P1] + SensorValue[P2] < 2212 && time1[T1] < 3000)
    {
        Arm(127);
    }
    Trim();
}

// Moves the arm to wall height
void ArmWall()
{
    ClearTimer(T1);
    while(SensorValue[P1] + SensorValue[P2] < 2700 && time1[T1] < 4500)
    {
        Arm(127);
    }
    Trim();
}

// Picks up 4 rings
void PickUp4()
{
    Arm(-127);
    while(SensorValue[P1] + SensorValue[P2] > 400);
    Trim();

    Forward(30, 30);

    Arm(-127);
    while(SensorValue[P1] + SensorValue[P2] > 30);
    wait1Msec(500);
    Trim();
}

// Drops count number of rings
void Drop(int count)
{
    // Remaining count
    count = GetRingCount() - count;

    if(count < 0)
    {
        count = 0;
    }

    Down();
    while(GetRingCount() > count);
    Up();
}

// Drops all rings with additional 1 second wait time
void DropAll()
{
    Down();
    while(GetRingCount() > 0);
    wait1Msec(1000);
    Up();
}

void ForwardTillStop(int speed = 40)
{
    DriveLeft(speed);
    DriveRight(speed);
    wait1Msec(750);
    while(LeftVelocity != 0 || RightVelocity != 0)
    {
        if(LeftVelocity <= 0)
        {
            DriveLeft(0);
        }

        if(RightVelocity <= 0)
        {
            DriveRight(0);
        }
    }
    Stop();
}
