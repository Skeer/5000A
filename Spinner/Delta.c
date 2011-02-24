void Delta()
{
    // red opp
    // This is how I want autonomous to look.
    // I do not want values in 5s or 10s, make sure your values are checked multiple times and tweaked to shit.

    Up();

    ArmBase();

    Forward(101, 101);

    PickUp4();

    ArmBase();

    //Left(330);
    while(SensorValue[QuadCenter] < 330);

    Forward(180, 180);

    Drop(3);

    ArmWall();

    Backward(-201, -201);

    TurnRight(192, -192);

    Forward(260, 260);

    Down();

    while(GetDonutCount() > 0);

    wait1Msec(1000);

    Backward(-120, -120);


    /*
    ArmBase();



    Forward(95, 95);



    PickUp4();


    // 125 125

    ArmBase();



    TurnLeft(40, 210);


    //Left(350);

    Forward(200, 400);


    //Forward(300, 300);

    Drop(3);



    ArmWall();



    TurnRight(420, 20);


    //Backward(180, 180);

    //TurnRight(450, -70);

    Forward(460, 150);
    //Forward(600, 80);

    Down();
    */
}
