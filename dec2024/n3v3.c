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
int distans_ot_robota_do_borta=25;
const int v_max=100;



//include
#include "lib/init_lib.c";
#include "lib/move_lib.c";
#include "lib/lib_turn.c";
#include "lib/lib_mvGyroRightToLeftBui.c"
#include "lib/lib_mvGyroToEncoder.c";
#include "lib/lib_TurnAnRadius.c"


task main()
{
	start_init_main();
	//--------------------------------------------


	mvGyroRightToEncoder(500, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(0, 30); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);
	mvGyroRightToEncoder(1250, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(0, 30); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);

	TurnAnRadius(-80, 100, -150);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

	mvGyroRightToEncoder(3500, -180);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);

	TurnAnRadius(-90, 100, -325);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

	mvGyroRightToEncoder(500, -360);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(-360, 35); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);
	mvGyroRightToEncoder(750, -360);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(-360, 40); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);

	TurnAnRadius(-90, 100, -530);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

	mvGyroRightToNose(-540,30);		  /*(int giroTagetXZ, int stoop)*/			 playTone(600,10);

	////////////////   END
	dispEndTimer();

	}
