void Alpha()
{

    ArmBase();

    Forward(30, 74); // 70

    PickUp4();

    ArmBase();

    /*
    TurnRight(40, 60);

    Forward(30, 250);
    */

    // NOTE: Modify speed and distance if needed
    // 300 original
    Right(127, 300); //check

    // NOTE: Modify distance if needed
    Forward(30, 300, false);//check this

    //Drop(5);
    Drop(3);

    // NOTE: ArmWall has not been tested(?)
    ArmWall();

    Backward(30, -55, false); // 205 need to check this value.

    // INFO: Turning to wall
    TurnLeft(40, 174); // 200

    Forward(30, 233); //check
    //Drop(GetDonutCount());
    Down();

    /*
    ArmBase();

    Forward(30, 80); // 70

    PickUp4();

    ArmBase();

    //TurnRight(40, 60);

    //Forward(30, 250);

    // NOTE: Modify speed and distance if needed
    // 300 original
    Right(127, 350);

    // NOTE: Modify distance if needed
    Forward(30, 200, false);

    //Drop(5);
    Drop(3);

    // NOTE: ArmWall has not been tested
    ArmWall();

    Backward(30, 750, false); // 205

    // INFO: Turning to wall
    TurnLeft(40, 200); // 170

    Forward(30, 230);

    Drop(GetDonutCount());
    */
}
