void Delta()
{
    Up();

    ArmBase();

    Forward(Step1, Step1);

    PickUp4();

    ArmBase();

    Left(Step2);

    Forward(Step3, Step3, 5000);

    Drop(3);

    ArmWall();

    Backward(-Step4B, -Step4B);

    TurnRight(Step5, -Step5);

    //Forward(Step6, Step6);
    ForwardTillStop();

    DropAll();

    Up();

    Backward(-Step7, -Step7);
}
