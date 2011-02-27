// Defined quad encoder values
int Step1 = 101;
int Step2 = 330;
int Step3 = 162;
int Step4A = 391;
int Step4B = 191;
int Step5 = 182;
int Step6 = 245;
int Step7 = 120;

#include "Alpha.c"
#include "Beta.c"
#include "Gamma.c"
#include "Delta.c"

void pre_auton()
{
    QCenter = 0;
    QLeft = 0;
    QRight = 0;

    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;
}

task autonomous()
{
    StartTask(velocitycalculator);

    if(SensorValue[J1]) // blue
    {
        if(SensorValue[J2]) //normal
        {
            Alpha();
        }
        else // oppo
        {
            Gamma();
        }
    }
    else // red
    {
        if(SensorValue[J2]) // normal
        {
            Beta();
        }
        else // oppo
        {
            Delta();
        }
    }

    StopTask(velocitycalculator);
}
