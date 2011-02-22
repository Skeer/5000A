void Delta()
{
    //red opp
    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;

    Close();
    while(SensorValue[ClawPotentiometer] > 240);

    ArmBase();

    Right(320);

    Forward(150, 150);

    while(SensorValue[ArmPotentiometer1] + SensorValue[ArmPotentiometer2] > 400)
    {
        Arm(400 - SensorValue[ArmPotentiometer1] - SensorValue[ArmPotentiometer2]);
    }

    while(SensorValue[ClawPotentiometer] < 500)
    {
        Open();
    }

    Backward(0, 0);
}
