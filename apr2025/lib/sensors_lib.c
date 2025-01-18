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

    while (1)
    {
        {
        int ih = ih_left + 1;
        if (ih >= len_left_real)	{ih = 0;}
        arr_left[ ih ] = SensorValue(port_left);
        ih_left = ih;
        sleep(10);
        }

        {
        int ih = ih_right + 1;
        if (ih >= len_right_real)		{ih = 0;}
        arr_right[ih] = SensorValue(port_right);
        ih_right = ih;
        sleep(10);
        }

        {
        int ih = ih_nose + 1;
        if (ih >= len_nose_real)	{ih = 0;}
        arr_nose[ih_nose] = SensorValue(port_nose);
        ih_nose = ih;
        sleep(10);
        }

	datalogDataGroupStart();

			datalogAddValue(0,time1[0]);

			datalogAddValue(1,us_left());
			datalogAddValue(2,us_right());
			datalogAddValue(3,us_nose());
//			datalogAddValue(4,dt5);
	datalogDataGroupEnd();



    } // while(1)
} // task sensors()







