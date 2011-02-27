#include "Config.c"
#include "Functions.c"
#include "Autonomous.c"


task usercontrol()
{
    // Autonomous trigger in drive control
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

    bool macro = false;
    int id = 0;
    int step = 0;

    while(true)
    {
        Drive(multiplier);


        if(vexRT[Btn7U])
        {
            wall = true;
            base = false;
            down = false;
            macro = false;
        }
        else if(vexRT[Btn7D])
        {
            wall = false;
            base = true;
            down = false;
            macro = false;
        }
        else if(vexRT[Btn7L])
        {
            wall = false;
            base = false;
            down = true;
            macro = false;
        }

        if(vexRT[Ch2] > 20 || vexRT[Ch2] < -20)
        {
            Arm();
            wall = false;
            base = false;
            down = false;
            macro = false;
        }
        else if(wall)
        {
            if(SensorValue[P1] + SensorValue[P2] != 2891)
            {
                Arm(520 - (SensorValue[P1] + SensorValue[P2]) / 6);
            }
            else
            {
                wall = false;
            }
        }
        else if(base)
        {
            if(SensorValue[P1] + SensorValue[P2] != 2212)
            {
                Arm(271 - (SensorValue[P1] + SensorValue[P2]) / 10);
            }
            else
            {
                base = false;
            }
        }
        else if(down)
        {
            if(SensorValue[P1] + SensorValue[P2] > 12)
            {
                Arm(-127);
            }
            else
            {
                down = false;
            }
        }
        else if(!macro)
        {
            Trim();
        }

        if(vexRT[Btn5U])
        {
            macro = false;
            Down();
        }
        else if(!macro)
        {
            Up();
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

        if(macro)
        {
            // macro id's
            // 1 = pick up 4
            switch (id)
            {
            case 1:
                switch(step)
                {
                case 0:
                    if(SensorValue[P1] + SensorValue[P2] > 400)
                    {
                        Arm(-127);
                    }
                    else
                    {
                        Trim();
                        ++step;
                    }
                    break;
                case 1:
                    if(SensorValue[QuadLeft] < 40 || SensorValue[QuadRight] < 40)
                    {
                        if(SensorValue[QuadLeft] < 40)
                        {
                            DriveLeft(30);
                        }
                        else
                        {
                            LeftBrake();
                        }

                        if(SensorValue[QuadRight] < 40)
                        {
                            DriveRight(30);
                        }
                        else
                        {
                            RightBrake();
                        }
                    }
                    else
                    {
                        Stop();
                        ClearTimer(T1);
                        ++step;
                    }
                    break;
                case 3:
                    if(time1[T1] < 500)
                    {
                        Arm(-127);
                    }
                    else
                    {
                        ClearTimer(T1);
                        ++step;
                    }
                    break;
                case 4:
                    if(SensorValue[P1] + SensorValue[P2] < 2212 || time1(T1) < 1000) //2060 -> 2212
                    {
                        Arm(271 - (SensorValue[P1] + SensorValue[P2]) / 10);
                    }
                    else
                    {
                        Trim();
                        macro = false;
                        id = 0;
                    }
                    break;
                }
                break;
            case 2:
                switch(step)
                {
                case 0:
                    if(GetRingCount() > 0)
                    {
                        Down();
                    }
                    else
                    {
                        ++step;
                        ClearTimer(T1);
                    }
                    break;
                case 1:
                    if(time1[T1] < 1000)
                    {
                        Down();
                    }
                    else
                    {
                        Up();
                        macro = false;
                        id = 0;
                    }
                    break;
                }
                break;
            }
        }

        if(vexRT[Btn6U])
        {
            wall = false;
            base = false;
            down = false;
            macro = true;

            SensorValue[QuadCenter] = 0;
            SensorValue[QuadLeft] = 0;
            SensorValue[QuadRight] = 0;

            if(GetRingCount() < 3 && SensorValue[P1] + SensorValue[P2] > 1500 && SensorValue[P1] + SensorValue[P2] < 2212)
            {
                id = 1;
            }
            else if(GetRingCount() > 0 && SensorValue[P1] + SensorValue[P2] >= 2212)
            {
                // NOTE: No point of this.............
                id = 2;
            }

            step = 0;
        }
    }
}
