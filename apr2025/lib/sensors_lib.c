int  prog = 0;

//    const int len_gyro_real = 9;
//    int arr_gyro[len_gyro_real];
//    int ih_gyro = 0;  // indek poslednego izmerenia v massive

    ///////////////////////////////////////////////////////////
    const int len_left_real = 11;
    int arr_left[len_left_real];
    int ih_left = 0;  // indek poslednego izmerenia v massive

    //////////////////////////////////////////////////////////////////////////
    const int len_right_real = 13;
    int arr_right[len_right_real];
    int ih_right = 0;

    //////////////////////////////////////////////////////////////////////////
    const int len_nose_real = 15;
    int arr_nose[len_nose_real];
    int ih_nose = 0;

//int gyro()
// {
//    return arr_gyro[ih_gyro];
// }
int us_left()
{
    return arr_left[ih_left];
}
int us_right()
{
    return arr_right[ih_right];
}
int us_nose()
{
    return arr_nose[ih_nose];
}

task sensors()
{ // oprashivaem datchiki i po krugu zapisivaem v massivi
    // originalnih poslednih znachenij datchika
datalogClear();
time1[0]=0;
int tm_sleep=35;

    while (1)
    {
        {
        int ihl = ih_left + 1;
        if (ihl >= len_left_real)	{ihl = 0;}
        arr_left[ ihl ] = SensorValue(port_left);
        ih_left = ihl;
        sleep(tm_sleep);
        }

        {
        int ihr = ih_right + 1;
        if (ihr >= len_right_real)		{ihr = 0;}
        arr_right[ihr] = SensorValue(port_right);
        ih_right = ihr;
        sleep(tm_sleep);
        }

        {
        int ihn = ih_nose + 1;
        if (ihn >= len_nose_real)	{ihn = 0;}
        arr_nose[ih_nose] = SensorValue(port_nose);
        ih_nose = ihn;
        sleep(tm_sleep);
        }
  /*
        {
        int ih = ih_gyro + 1;
        if (ih >= len_gyro_real)	{ih = 0;}
        arr_nose[ih] = SensorValue(port_gyro);
        ih_gyro = ih;
        sleep(tm_sleep);
        }
*/

	datalogDataGroupStart();

			datalogAddValue(0,time1[0]);
			datalogAddValue(1,time1[3]);

			datalogAddValue(2,us_left());
			datalogAddValue(3,us_right());
			datalogAddValue(4,us_nose());
//			datalogAddValue(4,gyro());
           datalogAddValue(5,getMotorEncoder(mot_left));
           datalogAddValue(6,getMotorEncoder(mot_right));
            datalogAddValue(7,prog);
	datalogDataGroupEnd();



    } // while(1)
} // task sensors()
