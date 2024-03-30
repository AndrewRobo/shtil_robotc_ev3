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
const int distans_ot_robota_do_borta=40;
const int v_max=100;
//int gyro_real;

//include
#include "filter_lib.c"
#include "init_lib.c"
//voids

void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)
{
	int GiroscopYgolOnline = SensorValue(port_gyro);
	int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
	motor[mot_left]=v_max+Error_ygol*koef_usilenia;
	motor[mot_right]=v_max-Error_ygol*koef_usilenia;
}//void moveProporcional(int GiroscopTarget, int koef_usilenia)

void EnMoveGirRight(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int et = EnkoderTarget * 2;
	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	int delta_distans_right;
	int SrArifmetikEnkoder;

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);

	do{
		SrArifmetikEnkoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
		delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_right);
		GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
		if(abs(delta_distans_right)<10)
		{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	moveProporcional( GiroscopTargetFrozen-15, 4 , v_max);	}
			else
			{	moveProporcional( GiroscopTargetFrozen+15, 4 , v_max);	}
		}//if(abs(delta_distans_right)<10)
	}while(SrArifmetikEnkoder<et);
}//void EnMoveGirRight(int EnkoderTarget, int giroTagetXZ)


void povorot(int ugol_povorota, int v_max)
{
	setLEDColor(ledGreen);
	if(ugol_povorota<0)
	{
		while( ugol_povorota+5 > SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=-Error_ygol;
		}//while( ugol_povorota+5 != SensorValue(port_gyro))
	}//if(ugol_povorota<0)
	else
	{
		while( ugol_povorota-5 < SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=-Error_ygol;
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
}//povorot(new_kurs)

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
			{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	moveProporcional( GiroscopTargetFrozen-15, 1 , v_max);	}
				else
				{	moveProporcional( GiroscopTargetFrozen+15, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(70<filtr_itog_nose)
		else//if(70>filtr_itog_nose)
		{ break; }
	}// while(1)
}//void moveKyrs()

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
			set_ugol_rul(-40)
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

void EnMoveGir(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	datalogClear();
	while(1)
	{
		int delta_distans_right;
		int ff;
		int SrArifmetikEnkoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right))/2;
		if(SrArifmetikEnkoder<EnkoderTarget)
		{
			ff = SensorValue(port_right);
			delta_distans_right =  distans_ot_robota_do_borta - ff;
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	moveProporcional( GiroscopTargetFrozen-15, 4 , v_max);	}
				else
				{	moveProporcional( GiroscopTargetFrozen+15, 4 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(SrArifmetikEnkoder<EnkoderTarget)
		else//if(SrArifmetikEnkoder<EnkoderTarget)
		{ break; }
	}// while(1)
}//EnMoveGir(int EnkoderTarget, int giroTagetXZ)

void moveKyrsRight_doBuy(int giroTagetXZ, int stoop)
{
	setLEDColor(ledOrangePulse);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	int delta_distans_right;

	do{
		delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_right);
		GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
		if(abs(delta_distans_right)<10)
		{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	moveProporcional( GiroscopTargetFrozen-15, 1 , v_max);	}
			else
			{	moveProporcional( GiroscopTargetFrozen+15, 1 , v_max);	}
		}//if(abs(delta_distans_right)<10)
	}while(stoop<SensorValue(port_left));
}//void moveKyrsRight(int giroTagetXZ, int stoop)

void EnMoveGirLol(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRedPulse);

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);

	int et = EnkoderTarget * 2;
	int SrArifmetikEnkoder;

	do{
		SrArifmetikEnkoder= (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
		moveProporcional( giroTagetXZ, 1 , 100);
	}while(SrArifmetikEnkoder<et);
}//void EnMoveGir(int EnkoderTarget, int giroTagetXZ)

task bui()
{
	sleep(3000)
	while(1)
	{
		if(SensorValue(port_left)<50)
		{
			stopAllTasks()
			playtone(600 , 1000)
			sleep(1000)
		}
	}
}

task main()
{
	start_init_main();

	stopTask(filtr);
	stopTask(sensors);
	startTask(Bui)

	EnMoveGir(40000, 0);

	////////////////   END
	dispEndTimer();

}
