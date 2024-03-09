#pragma config(Sensor, S1, port_nose, sensorEV3_Ultrasonic)
#pragma config(Sensor, S2, port_left, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3, port_right, sensorEV3_Ultrasonic)
#pragma config(Sensor, S4, port_gyro, sensorEV3_Gyro)
#pragma config(Motor, motorA, mot_left, tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor, motorB, port_radar, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, port_rul, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorD, mot_right, tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//global variable
	int rul;  // tekuschij ugol rulua   global
	const int SPEED_RUL=30

	int distans_ot_robota_do_borta=30;
	int v_max=80;
	int gyro_real;

	int my_timer;
	int my_delta;

	int filtr_itog_left;
	int filtr_itog_nose;
	int filtr_itog_right;

//massives
	const int len_left_real = 17;
	int arr_left[len_left_real];
	int ih_left = 0;

	const int len_left_frozen = 11;
	const int middle_left = len_left_frozen/2;
	int arr_left_frozen[len_left_frozen];

	//////////////////////////////////////////////////////////////////////////
	const int len_right_real = 19;
	int arr_right[len_right_real];
	int ih_right = 0;

	const int len_right_frozen = 11;
	const int middle_right = len_right_frozen/2;
	int arr_right_frozen[len_right_frozen];

	//////////////////////////////////////////////////////////////////////////
	const int len_nose_real = 20;
	int arr_nose[len_nose_real];
	int ih_nose = 0;

	const int len_nose_frozen = 11;
	const int middle_nose = len_nose_frozen/2;
	int arr_nose_frozen[len_nose_frozen];

//voids
	void buble_sort( int *arr, int lenn )
	{ // sortirovka puzirkom
		int tmp;
		int last = lenn - 1;
		do{
			tmp = 0;
			for( int n = last ;   n > 0 ;   n-- )
			{
				if (arr[ n-1 ] > arr[ n ])
				{
					int imp = arr[ n ];
					arr[ n ] = arr[ n-1 ];
					arr[ n-1 ] = imp;
					tmp++;
				}//if (arr[ n-1 ] > arr[ n ])
			}//for( int n = last ;   n > 0 ;   n-- )
		}while ( tmp > 0 );
	}//void buble_sort( int *arr, int lenn )

	void frozen( int* raw, int len_raw, int raw_pointer, int* frozen, int len_frozen   )
	{ // ficsaruem - zamorajivae  massiv dlya sortirovki
		int ih = raw_pointer-1 ;
		if ( ih < 0 ) {ih = len_raw - 1;}

		for( int ii = len_frozen - 1; ii >= 0; ii-- )
		{
			frozen[ii] = raw[ih];
			ih--;
			if ( ih < 0 ) {ih = len_raw - 1;}
		}//for( int ii = len_frozen - 1; ii >= 0; ii-- )
	}//void frozen( int* raw, int len_raw, int raw_pointer, int* frozen, int len_frozen   )

	void set_ugol_rul(int ff)
	{
		int f=ff;
		if(f > 60){ f=60;}
		if(f < -60){ f=-60;}

		setMotorTarget(port_rul, f, SPEED_RUL);
		waitUntilMotorStop(port_rul);

		rul=getMotorEncoder(port_rul);
	}

    void moveProporcional(int GiroscopTarget, int koef_usilenia)
    {
        int GiroscopYgolOnline = SensorValue(port_gyro)
        int Error_ygol = GiroscopTarget - GiroscopYgolOnline
        if(Error_ygol>GiroscopTarget)
        {
            motor[mot_left]=80-Error_ygol*koef_usilenia
            motor[mot_right]=80+Error_ygol*koef_usilenia
        }//if(Error_ygol>GiroscopTarget)
        else
        {
            motor[mot_left]=80+Error_ygol*koef_usilenia
            motor[mot_right]=80-Error_ygol*koef_usilenia
        }//else
    }//void moveProporcional(int GiroscopTarget, int koef_usilenia)

//init
	void init_gyro()
	{
	sleep(500);
	resetGyro(port_gyro);
	sleep(500);
	}//init_gyro()

	void init_radar()
	{// inicializacia naoravlenia radararadara
		// vraschaem motor radara do ogranichitela
		// i vistavlyaen nulevim kurs vpered

		int en_radar = 1;
		int en_radar2 = 2;

		motor[port_radar] = -30;

		while (en_radar != en_radar2)
		{
			en_radar2 = en_radar;
			sleep(50);
			en_radar = getMotorEncoder(port_radar);
		}//while (en_radar != en_radar2)

		//	resetMotorEncoder(port_radar);
		motor[port_radar] = 0;
		sleep(300);

		moveMotorTarget(port_radar, 110, 30); // 100 grad - 90 grad
		//                 plus experimentalnaya korrektirovka
		waitUntilMotorStop(port_radar);

		resetMotorEncoder(port_radar); // nulevim oschetom graduvov napravlinia radara delaem kurs vpered
	}//init_radar()

	void init_rul()
	{
		// povopot rulya do fiksatora  vdol zadnego borta
		int ryl = 1;
		int ryl2 = 2;

		motor[port_rul] = 40;

		while (ryl != ryl2)
		{
			ryl2 = ryl;
			sleep(50);
			ryl = getMotorEncoder(port_rul);
		}//while (ryl != ryl2)
		motor[port_rul] = 0;
		//	resetMotorEncoder(port_rul);
		sleep(300);

		// ustanavlivaem nulevim centralnoe pologenie rula
		moveMotorTarget(port_rul, -100, -30); // 100 grad - 90 grad
		//                 plus experimentalnaya korrektirovka
		waitUntilMotorStop(port_rul);
		resetMotorEncoder(port_rul);
	}//init_rul()




//tasks
	task sensors()
	{ // oprashivaem datchiki i po krugu zapisivaem v massivi
		// originalnih poslednih znachenij datchika
		while (1)
		{

			arr_left[ ih_left ] = SensorValue(port_left);
			ih_left++;
			if (ih_left >= len_left_real)	{ih_left = 0;}
			sleep(10);

			arr_right[ih_right] = SensorValue(port_right);
			ih_right++;
			if (ih_right >= len_right_real)		{ih_right = 0;}
			sleep(10);

			arr_nose[ih_nose] = SensorValue(port_nose);
			ih_nose++;
			if (ih_nose >= len_nose_real)	{ih_nose = 0;}
			sleep(10);

		} // while(1)
	} // task sensors()

	task monnitor()
	{
		while(1)
		{
		displayBigTextLine(3, "%d", filtr_itog_nose);
		displayBigTextLine(5, "%d", filtr_itog_right);
		displayBigTextLine(7, "%d", filtr_itog_left);
		displayBigTextLine(11, "%d", gyro_real);
		}// while(1)
	}//task monnitor()

	task filtr()
	{
		time1[0]=0;
		while(1)
		{
			my_timer=time1[0];

			frozen( arr_right, len_right_real, ih_right, arr_right_frozen, len_right_frozen);
			buble_sort( arr_right, len_right_real );
			filtr_itog_right = arr_right_frozen[middle_right];

			frozen( arr_nose, len_nose_real, ih_nose, arr_nose_frozen, len_nose_frozen);
			buble_sort( arr_nose, len_nose_real );
			filtr_itog_nose = arr_nose_frozen[middle_nose];

			my_delta=time1[0]- my_timer ;

			displayBigTextLine(10, "%d", my_delta);
		}// while(1)
	}//task filtr()
 
task main()
{
	init_radar();
	sleep(300);

	init_rul();
	sleep(300);

	init_gyro();
	sleep(300);

	startTask(sensors);
	sleep(1000);

	startTask(filtr);
	sleep(1000);
	//startTask(monnitor);

	playTone(600,100);

	while(1)
	{
         moveProporcional(0 , 1)
	}// while(1)
}// task_main
