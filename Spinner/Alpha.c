void Alpha()
{
    Up();

    ArmBase();

    Forward(step1, step1);

    PickUp4();

    ArmBase();

    Right(-step2);

    Forward(step3, step3);

    //Drop(3);
    Drop(3);

    ArmWall();

    Backward(-step4b, -step4b);

    TurnLeft(step5, -step5);

    Forward(step6, step6);

    DropAll();

    Up();

    Backward(-step7, -step7);
}
