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
int distans_ot_robota_do_borta=30;
const int v_max=1000;
//int gyro_real;

//include
#include "lib/init_lib.c"
#include "lib/move_lib.c"
//voids
/*

void moveProporcional( int GiroscopTarget, int koef_usilenia  , int v_max )

{
	const int k_gyro_rul = 1;
	int dynamic_speed = v_max;

	int ugol_error = GiroscopTarget -  SensorValue(port_gyro);
	dynamic_speed -= koef_usilenia * ( abs( ugol_error ) );
	if ( dynamic_speed > v_max ) 	    dynamic_speed=v_max;
	else if (dynamic_speed < -v_max )	dynamic_speed=-v_max;
	else if ( dynamic_speed>0 && dynamic_speed<=15 )  dynamic_speed=0;
	else if ( dynamic_speed<0 && dynamic_speed>=-15 ) dynamic_speed=0;
	if ( ugol_error <=0 ){
		motor[mot_left]=dynamic_speed;
		motor[mot_right]=v_max;
	}
	else {
		motor[mot_left]=v_max;
		motor[mot_right]=dynamic_speed;
	}

	set_ugol_rul ( k_gyro_rul * ugol_error);

}
*/


void moveKyrs(int giroTagetXZ, int stoop)
{
	setLEDColor(ledOrange);
	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	while(1)
	{
		if(stoop<SensorValue(port_nose))
		{
			int delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_right);
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-15, 1 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+15, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(70<filtr_itog_nose)
		else//if(70>filtr_itog_nose)
		{ break; }
	}// while(1)
}//void moveKyrs()


/*
void povorot_na_1_motore(int ugol_povorota, int v_max)
{
	setLEDColor(ledGreen);
	if(ugol_povorota<0)
	{
		while( ugol_povorota+5 < SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=v_max;
			set_ugol_rul(-40);
		}//while( ugol_povorota+5 != SensorValue(port_gyro))
	}//if(ugol_povorota<0)
	else
	{
		while( ugol_povorota-5 > SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=v_max;
			motor[mot_right]=Error_ygol;
			set_ugol_rul(40);
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
	set_ugol_rul(0);
}//void povopot_na_1_motore()
/*
void EnMoveGir(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	datalogClear();
	while(1){
		int delta_distans_right;
		int ff;
		int SrArifmetikEnkoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right))/2;
		if(SrArifmetikEnkoder<EnkoderTarget)
		{
			ff = SensorValue(port_right);
			delta_distans_right =  distans_ot_robota_do_borta - ff;
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-30, 3.5 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+30, 3.5 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(SrArifmetikEnkoder<EnkoderTarget)
		else//if(SrArifmetikEnkoder<EnkoderTarget)
		{ break; }
	}// while(1)
}//EnMoveGir(int EnkoderTarget, int giroTagetXZ)
*/


task main()
{
	start_init_main();

  distans_ot_robota_do_borta=30;

	mvGyroRightToEncoder(6000, 0);

  distans_ot_robota_do_borta=30;

	playTone(600,10);

	moveKyrs(0,70);

	playTone(600,10);

	turn(-80, 100);

	playTone(600,10);

	mvGyroRightToEncoder(500, -90);

	playTone(600,10);

	moveKyrs(-90,70);

	playTone(600,10);

	turn(-170, 100);

	playTone(600,10);






	mvGyroRightToEncoder(5000, -180);

	playTone(600,70);

	moveKyrs(-180,40);

	////////////////   END
	dispEndTimer();

	}