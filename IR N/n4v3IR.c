#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     port_left,      sensorEV3_IRSensor)
#pragma config(Sensor, S3,     port_right,     sensorEV3_IRSensor)
#pragma config(Sensor, S4,     port_gyro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          port_radar,    tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//#define dlog 1;
//global variabl
//int rul;  // tekuschij ugol rulua   global
int distans_ot_robota_do_borta=30;
const int v_max=15;
//include
#include "lib/sensor3_lib.c";
#include "lib/init_lib.c";
#include "lib/move_lib.c";
#include "lib/lib_turn.c";
#include "lib/lib_mvGyroRightToLeftBui.c";
#include "lib/lib_mvGyroLeftToRightBui.c";
#include "lib/lib_mvGyroLeftToEncoder.c";
#include "lib/lib_mvGyroToEncoder.c";
#include "lib/lib_mvGyroToNose.c";
#include "lib/lib_TurnAnRadius.c";
task main()
{
	start_init_main();
	//--------------------------------------------
	mvGyroRightToEncoder(700, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(0, 90); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);
	mvGyroRightToEncoder(720, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	mvGyroRightToLeftBui(0, 90); 	/*(int giroTagetXZ, int LeftBui)*/		 playTone(600,10);
	turn(-45, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-45)
		turn(-90, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-90)
		turn(-135, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-135)
		turn(-175, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	mvGyroRightToEncoder(500, -180);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
//	mvGyroToEncoder(50,-135)
		turn(-225, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	set_ugol_radar(-35);
  mvGyroToNose(-230, 80);
//	mvGyroToEncoder(50,-135)
		turn(-185, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	mvGyroLeftToEncoder(500, -180);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	turn(-135, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-45)
		turn(-90, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-90)
		turn(-45, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-135)
		turn(-10, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	mvGyroLeftToEncoder(600, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	set_ugol_radar(45);
//	mvGyroToEncoder(50,-135)
		turn(45, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	mvGyroToNose(45, 75);
//	mvGyroToEncoder(50,-135)
		turn(10, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	set_ugol_radar(5);
	mvGyroRightToEncoder(150, 0);   /*(int EnkoderTarget, int giroTagetXZ)*/	 playTone(600,10);
	turn(-45, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-45)
		turn(-90, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-90)
		turn(-135, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
//	mvGyroToEncoder(50,-135)
		turn(-160, 100);					  /*(int new_kurs, int v_max)*/				 playTone(600,10);
	distans_ot_robota_do_borta=50;
	mvGyroRightToNose(-180,25);		  /*(int giroTagetXZ, int stoop)*/			 playTone(600,10);
  ////////////////   END
	dispEndTimer();

	}
