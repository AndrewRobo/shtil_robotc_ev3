#pragma config(Sensor, S1, port_nose, sensorEV3_Ultrasonic)
#pragma config(Sensor, S2, port_left, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3, port_right, sensorEV3_Ultrasonic)
#pragma config(Sensor, S4, port_gyro, sensorEV3_Gyro)
#pragma config(Motor, motorA, mot_left, tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor, motorB, port_radar, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, port_rul, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorD, mot_right, tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#pragma DebuggerWindows("JoystickSimple")

int filtr_itog_left;
int filtr_itog_nose;
int filtr_itog_right;


const int len_left_real = 17;
int arr_left[len_left_real];
int ih_left = 0;

const int len_left_frozen = 11;
int arr_left_frozen[len_left_frozen];

//////////////////////////////////////////////////////////////////////////
const int len_right_real = 19;
int arr_right[len_right_real];
int ih_right = 0;

const int len_right_frozen = 11;
int arr_right_frozen[len_right_frozen];

//////////////////////////////////////////////////////////////////////////
const int len_nose_real = 20;
int arr_nose[len_nose_real];
int ih_nose = 0;

const int len_nose_frozen = 11;
int arr_nose_frozen[len_nose_frozen];



void sortirovka_left()
{				 // sortirovka puzirkom Andreya
	int tmp = 1; // flag poscheta nalichiya swapov
	while (tmp > 0)
	{
		tmp = 0;
		int n = len_left_frozen - 1;
		while (n > 0)
		{
			if (arr_left_frozen[n - 1] > arr_left_frozen[n])
			{
			int imp = arr_left_frozen[n];
			arr_left_frozen[n] = arr_left_frozen[n - 1];
			arr_left_frozen[n - 1] = imp;
			tmp++;
			}
			n--;
		}
	}
}
void buble_sort( int *arr, int lenn )
{
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
			}
		}
	}while (tmp > 0);
}

void sortirovka_buble_left()
{ //  sortirovka puzirkom Sergej
	int size = len_left_frozen;
	while (1)
	{
		int wasSort = 0;
		for (int i = 0; i < size - 1; i++)
		{
			if (arr_left_frozen[i] > arr_left_frozen[i + 1])
			{
				int temp_value = arr_left_frozen[i];
				arr_left_frozen[i] = arr_left_frozen[i + 1];
				arr_left_frozen[i + 1] = temp_value;
				wasSort++;
			}
		}
		if (wasSort == 0)
			break;
	}
}

task sensors()
{ // oprashivaem datchiki i po krugu zapisivaem v massivi
	// originalnih poslednih znachenij datchika
	while (1)
	{
		arr_left[ih_left] = SensorValue(port_left);
		ih_left++;
		if (ih_left >= len_left_real)
		{
			ih_left = 0;
		}
		sleep(10);

		arr_right[ih_right] = SensorValue(port_right);
		ih_right++;
		if (ih_right >= len_right_real)
		{
			ih_right = 0;
		}
		sleep(10);

		arr_nose[ih_nose] = SensorValue(port_nose);
		ih_nose++;
		if (ih_nose >= len_nose_real)
		{
			ih_nose = 0;
		}
		sleep(10);

	} // while(1)
} // task sensors()

void left_frozen()
{
	int ih = ih_left;
	int ii = len_left_frozen - 1;
	while (1)
	{
		arr_left_frozen[ii] = arr_left[ih];

		ii--;
		if (ii < 0)
		{
			break;
		}
		ih--;
		if (ih < 0)
		{
			ih = len_left_real - 1;
		}
	}
}

void right_frozen()
{
	int ih = ih_right;
	int ii = len_right_frozen - 1;
	while (1)
	{
		arr_right_frozen[ii] = arr_right[ih];

		ii--;
		if (ii < 0)
		{
			break;
		}
		ih--;
		if (ih < 0)
		{
			ih = len_right_real - 1;
		}
	}
}

void nose_frozen()
{
	int ih = ih_nose;
	int ii = len_nose_frozen - 1;
	while (1)
	{
		arr_nose_frozen[ii] = arr_nose[ih];
		ii--;
		if (ii < 0)
		{
			break;
		}
		ih--;
		if (ih < 0)
		{
			ih = len_nose_real - 1;
		}
	}
}

void init_radar() ////////////////////////////////////////////
{				  // inicializacia naoravlenia radararadara
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
	}

	//	resetMotorEncoder(port_radar);
	motor[port_radar] = 0;
	sleep(300);

	moveMotorTarget(port_radar, 110, 30); // 100 grad - 90 grad
	//                 plus experimentalnaya korrektirovka
	waitUntilMotorStop(port_radar);

	resetMotorEncoder(port_radar); // nulevim oschetom graduvov napravlinia radara delaem kurs vpered
}

void init_rul() /////////////////////////////////////////////////////////////////////////////////////////////

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
	}
	motor[port_rul] = 0;
	//	resetMotorEncoder(port_rul);
	sleep(300);

	// ustanavlivaem nulevim centralnoe pologenie rula
	moveMotorTarget(port_rul, -100, -30); // 100 grad - 90 grad
	//                 plus experimentalnaya korrektirovka
	waitUntilMotorStop(port_rul);
	resetMotorEncoder(port_rul);
}

task main() ////////////////////////////////////////////////////////////////////////////////////////
{
	init_radar();
	sleep(300);
	init_rul();
	startTask(sensors);

	while (1)
	{ // y - otklonenia joistikov s pulta otpravliaem v motori
		getJoystickSettings(joystick);
		motor[mot_left] = joystick.joy1_y1;
		motor[mot_right] = joystick.joy1_y2;

		if (joy1Btn(Btn5)) // umenshaen ugol rulya  do -60 gradusov
		{
			if (nMotorEncoder(port_rul) > -60)
			{
				moveMotorTarget(port_rul, -10, -10);
				waitUntilMotorStop(port_rul);
			}
		}
		if (joy1Btn(Btn6)) // uvelichivaem ugol rulya do +60 gradusov
		{
			if (nMotorEncoder(port_rul) < 60)
			{
				moveMotorTarget(port_rul, 10, 10);
				waitUntilMotorStop(port_rul);
			}
		}
		if (joy1Btn(Btn7)) // umenshaen ugol radara  do -90 gradusov   //  povorot k pravomu bortu
		{
			if (nMotorEncoder(port_radar) > -80)
			{
				moveMotorTarget(port_radar, -10, -10);
				waitUntilMotorStop(port_radar);
			}
		}
		if (joy1Btn(Btn8)) // uvelichivaem ugol radara do +90 gradusov   	// povotachivaem radar na pravij bort
		{
			if (nMotorEncoder(port_radar) < 80)
			{
				moveMotorTarget(port_radar, 10, 10);
				waitUntilMotorStop(port_radar);
			}
		}

		if (joy1Btn(Btn1)) // zapolnenie froze po knopke
		{
			left_frozen();
			buble_sort(arr_left_frozen,len_left_frozen);
			//sortirovka_left();
			//sortirovka_buble_left();

		}

		if (joy1Btn(Btn3))
		{
			right_frozen();
				buble_sort(arr_right_frozen,len_right_frozen);
		}

		if (joy1Btn(Btn4))
		{
			nose_frozen();
				buble_sort(arr_nose_frozen,len_nose_frozen);
		}
 filtr_itog_left = arr_left_frozen[5];
 filtr_itog_nose = arr_nose_frozen[5];
 filtr_itog_right = arr_right_frozen[5];

	} // while(1)
} // task_main
