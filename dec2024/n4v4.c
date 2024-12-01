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
#include "lib/lib_mvGyroRightToLeftBui.c";
#include "lib/lib_mvGyroLeftToRightBui.c";
#include "lib/lib_mvGyroLeftToEncoder.c";
#include "lib/lib_mvGyroToEncoder.c";
#include "lib/lib_TurnAnRadius.c";


task main()
{
	start_init_main();
	//--------------------------------------------


//mvGyroleftToEncoder(7000, 0);/*(int EnkoderTarget, int giroTagetXZ)*/playTone(600,10);

mvGyroRightToEncoder(1000, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/playTone(600,10);
mvGyroRightToLeftBui(0, 30); 	/*(int giroTagetXZ, int LeftBui)*/playTone(600,10);
mvGyroRightToEncoder(1250, 0);	  /*(int EnkoderTarget, int giroTagetXZ)*/playTone(600,10);
mvGyroRightToLeftBui(0, 33); 	/*(int giroTagetXZ, int LeftBui)*/playTone(600,10);
TurnAnRadius(-90, 100, -160);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

/ pervaya diagonal
vGyroRightToEncoder(500, -180);	/*(int EnkoderTarget, int giroTagetXZ)*/playTone(600,10);
TurnAnRadius(-90, 100, -220);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);
vGyroToEncoder(800, -220);	/*(int EnkoderTarget, int gyroTaget)*/playTone(600,10);
TurnAnRadius(100, -100, -190);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

// vtoroi bui   ( blignij k staetu )
mvGyroLeftToRightBui(-180, 40); 	/*(int giroTagetXZ, int LeftBui)*/playTone(600,10);
TurnAnRadius(100, -100, -20);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

// obratnaya diagonal
mvGyroLeftToEncoder(1000, 0);	/*(int EnkoderTarget, int giroTagetXZ)*/playTone(600,10);
TurnAnRadius(100, -100, 45);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);
mvGyroToEncoder(800, 45);	/*(int EnkoderTarget, int gyroTaget)*/playTone(600,10);
TurnAnRadius(-90, 100, 15);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

// vtoroi raz vokrug pervogo buya
mvGyroRightToLeftBui(0, 40); 	/*(int giroTagetXZ, int LeftBui)*/playTone(600,10);
TurnAnRadius(-100, 90, -160);	/*(int v_left, int v_right, int giroTagetXZ)*/playTone(600,10);

// domoi
mvGyroRightToNose(-180,30);		/*(int giroTagetXZ, int stoop)*/playTone(600,10);








  ////////////////   END
	dispEndTimer();

	}
