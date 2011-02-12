void Delta()
{
    //red oppo


    SensorValue[QuadCenter] = 0;
    SensorValue[QuadLeft] = 0;
    SensorValue[QuadRight] = 0;
    /*
    ArmBase();
    //Forward
    Move(0, 98, 105);
    wait1Msec(4000);
    PickUp4();
    ArmBase();
    //Left
    Move(350, 128, 127);
    //Forward
    Move(350, 300, 300);
    Drop(3);
    ArmWall();
    //Backward
    Move(310, 95, 95);
    //TurnRight d
    Move(310, 265, -75);
    //Forward
    Move(310, 495, 155);
    Drop(GetDonutCount());

    */
    ArmBase();

    Forward(80, 80); // 70

    PickUp4();

    ArmBase();

    // TurnRight(40, 60);

    // Forward(30, 250);

    // NOTE: Modify speed and distance if needed
    // 300 original
    Left(260);

    // NOTE: Modify distance if needed
    Forward(320, 320);

    //Drop(5);
    Drop(3);

    // NOTE: ArmWall has not been tested
    ArmWall();

    Backward(180, 180); // 205

    // INFO: Turning to wall
    TurnRight(450, -70); // 170

    Forward(600, 80);

    //Drop(GetDonutCount());
    Down();
}
