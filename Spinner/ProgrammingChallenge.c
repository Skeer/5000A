#include "Config.c"
#include "Functions.c"

void pre_auton()
{
    QCenter = 0;
    QLeft = 0;
    QRight = 0;

    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;
}

task main()
{
    int step1 = 100;
    int step2 = 182;
    int step3 = 101;
    int step4 = 330;
    int step5 = 162;
    int step6 = 200;
    int step7 = 364;
    int step8 = 200;
    int step9 = 300;
    int step10 = 330;
    int step11 = 243;
    int step12 = 400;
    int step13 = 400;
    int step14 = 30;
    int step15 = 182;
    int step16 = 380;
    int step17 = 100;
    int step18 = 300;
    int step19 = 500;
    int step20 = 162;
    int step21 = 100;
    int step22 = 250;



    StartTask(velocitycalculator);

    pre_auton();


    ArmWall();
    ForwardTillStop();
    DropAll();
    Backward(-step1, -step1);
    TurnLeft(-step2, step2);
    Forward(step3, step3);
    PickUp4();
    ArmBase();
    Left(step4);
    Forward(step5, step5);
    DropAll();
    Backward(-step6, -step6);
    TurnLeft(-step7, step7);
    Forward(step8, step8);
    PickUp4();
    ArmBase();
    Forward(step9, step9);
    DropAll();
    // Should take advantage of line sensor here
    Backward(-step10, -step10);
    // Same here
    TurnRight(step11, -step11);
    // Also here
    Forward(step12, step12);
    // Here too
    Forward(step13, step13);
    PickUp4();
    ArmBase();
    Forward(step14, step14);
    TurnLeft(-step15, step15)
    Forward(step16, step16);
    DropAll();
    Backward(-step17, -step17);
    Right(-step18);
    // Line sensor
    Forward(step19, step19);
    // Here
    TurnLeft(-step20, step20);
    // Also here
    Forward(step21, step21);
    PickUp4();
    ArmBase();
    // Same here
    Forward(step22, step22);
    DropAll();

    StopTask(velocitycalculator);
}
