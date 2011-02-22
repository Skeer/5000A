void Delta()
{
    // red opp
    // This is how I want autonomous to look.
    // I do not want values in 5s or 10s, make sure your values are checked multiple times and tweaked to shit.

    Up();

    ArmBase();

    Forward(91, 91);

    PickUp4();

    Left(312);

    Forward(99, 99);

    Drop(3);

    Backward(-201, -201);

    TurnRight(85, -85);

    Forward(84, 84);

    Down();


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
