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

//int rul;  // tekuschij ugol rulua   global
int distans_ot_robota_do_borta=20;
const int v_max=100;


//include
#include "lib/init_lib.c";
#include "lib/move_lib.c";
#include "lib/lib_turn.c";
#include "lib/lib_mvGyroRightToLeftBui.c";

task main()
{
	start_init_main();
	//--------------------------------------------


	mvGyroRightToLeftBui(0, 50); 	/*(int giroTagetXZ, int LeftBui)*/			playTone(600,10);
	mvGyroRightToEncoder(360, 0);   /*(int EnkoderTarget, int giroTagetXZ)*/	playTone(600,10);
	turn(-80, 100);					/*(int new_kurs, int v_max)*/				 playTone(600,10);

	mvGyroRightToEncoder(500, -90); /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToNose(-90,70);		/*(int giroTagetXZ, int stoop)*/			 playTone(600,10);
	turn(-170, 100);				/*(int new_kurs, int v_max)*/				 playTone(600,10);


	distans_ot_robota_do_borta=30;

	mvGyroRightToNose(-180,50);	/*(int giroTagetXZ, int stoop)*/			playTone(600,10);


	////////////////   END
	dispEndTimer();

	}
