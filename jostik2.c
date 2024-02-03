#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     port_left,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     port_roght,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_gyro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          port_radar,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#pragma DebuggerWindows("JoystickSimple")


const int len_left_real=20 ;
int arr_left[len_left_real];
int ih_left = 0;

const int len_left_frizen=11  ;
int arr_left_frozen[len_left_frizen];

void massive_left_sensor()
{
	while(1)
	{
   arr_left[ih_left]=SensorValue(port_left);
   ih_left++;
   if( ih_left >= len_left_real){ ih_left = 0; }
	}
}
task sensors()
{
	massive_left_sensor();
}
void init_radar()////////////////////////////////////////////
{ // inicializacia naoravlenia radararadara
	// vraschaem motor radara do ogranichitela
	// i vistavlyaen nulevim kurs vpered

	int en_radar = 1;
	int en_radar2 = 2;

	motor[port_radar] = -30;

	while(en_radar!=en_radar2)
	{
		en_radar2 = en_radar;
		sleep(50);
		en_radar = getMotorEncoder(port_radar);
	}

	//	resetMotorEncoder(port_radar);
	motor[port_radar] = 0;
	sleep(300);


	moveMotorTarget(port_radar,110,30); // 100 grad - 90 grad
	//                 plus experimentalnaya korrektirovka
	waitUntilMotorStop(port_radar);

	resetMotorEncoder(port_radar); // nulevim oschetom graduvov napravlinia radara delaem kurs vpered
}


void init_rul()/////////////////////////////////////////////////////////////////////////////////////////////

{
	// povopot rulya do fiksatora  vdol zadnego borta
	int ryl=1;
	int ryl2=2;

	motor[port_rul] = 40;

	while( ryl !=  ryl2)
	{
		ryl2 = ryl;
		sleep(50);
		ryl = getMotorEncoder(port_rul);
	}
	motor[port_rul] = 0;
	//	resetMotorEncoder(port_rul);
	sleep(300);

	// ustanavlivaem nulevim centralnoe pologenie rula
	moveMotorTarget(port_rul,-100,-30); // 100 grad - 90 grad
	//                 plus experimentalnaya korrektirovka
	waitUntilMotorStop(port_rul);
	resetMotorEncoder(port_rul);
}



task main()////////////////////////////////////////////////////////////////////////////////////////
{
	init_radar();
	sleep(300);
	init_rul();
  startTask(sensors);

	while(1)
	{ // y - otklonenia joistikov s pulta otpravliaem v motori
		getJoystickSettings(joystick);
		motor[mot_left]  = joystick.joy1_y1;
		motor[mot_right] = joystick.joy1_y2;

		if( joy1Btn(Btn5) ) // umenshaen ugol rulya  do -60 gradusov
		{
			if( nMotorEncoder(port_rul) > -60 )
			{
				moveMotorTarget(port_rul,-10,-10);
				waitUntilMotorStop(port_rul);
			}
		}
		if( joy1Btn(Btn6) ) // uvelichivaem ugol rulya do +60 gradusov
		{
			if( nMotorEncoder(port_rul) < 60 )
			{
				moveMotorTarget(port_rul,10,10);
				waitUntilMotorStop(port_rul);
			}
		}
		if( joy1Btn(Btn7) ) // umenshaen ugol rulya  do -60 gradusov   //  povorot k pravomu bortu
		{
			if( nMotorEncoder(port_radar) > -80 )
			{
				moveMotorTarget(port_radar,-10,-10);
				waitUntilMotorStop(port_radar);
			}
		}
		if( joy1Btn(Btn8) ) // uvelichivaem ugol rulya do +60 gradusov   	// povotachivaem radar na pravij bort
		{
			if( nMotorEncoder(port_radar) < 80 )
			{
				moveMotorTarget(port_radar,10,10);
				waitUntilMotorStop(port_radar);
			}
		}
	}//while(1)
} //task_main
