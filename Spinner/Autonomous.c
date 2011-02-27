// Defined quad encoder values
int step1 = 101;
int step2 = 330;
int step3 = 162;
int step4a = 191;
int step4b = 391;
int step5 = 182;
int step6 = 245;
int step7 = 120;

#include "Alpha.c"
#include "Beta.c"
#include "Gamma.c"
#include "Delta.c"

void pre_auton()
{
    QCenter = 0;
    QLeft = 0;
    QRight = 0;
}

task autonomous()
{
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
}
