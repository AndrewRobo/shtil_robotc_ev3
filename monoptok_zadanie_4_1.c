#pragma config(Sensor, S1, port_nose, sensorEV3_Ultrasonic)
#pragma config(Sensor, S2, port_left, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3, port_right, sensorEV3_Ultrasonic)
#pragma config(Sensor, S4, port_gyro, sensorEV3_Gyro)
#pragma config(Motor, motorA, mot_left, tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor, motorB, port_radar, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, port_rul, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorD, mot_right, tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "init_lib.c"
//global variable

const int distans_ot_robota_do_borta=20;
const int v_max=100;

void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)
{
	int GiroscopYgolOnline = SensorValue(port_gyro);
	int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
	motor[mot_left]=v_max+Error_ygol*koef_usilenia;
	motor[mot_right]=v_max-Error_ygol*koef_usilenia;
}//void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)

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
}//void povorot(int ugol_povorota, int v_max)

void moveKyrsRight(int giroTagetXZ, int stoop)
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
}//void moveKyrsRight(int giroTagetXZ, int stoop)

void moveKyrsLeft(int giroTagetXZ, int stoop)
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
}//void moveKyrsLeft(int giroTagetXZ, int stoop)

void povorot_na_1_motore(int prohlii_ygol ,int ugol_povorota, int v_max)
{
	setLEDColor(ledGreen);
	if(ugol_povorota<prohlii_ygol)
	{
		while( ugol_povorota+5 < SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=v_max;
			set_ugol_rul(-40) ;
		}//while( ugol_povorota+5 != SensorValue(port_gyro))
	}//if(ugol_povorota<0)
	else
	{
		while( ugol_povorota-5 > SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=v_max;
			motor[mot_right]=Error_ygol;
			set_ugol_rul(40) ;
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
	set_ugol_rul(0) ;
}//void povopot_na_1_motore(int ugol_povorota, int v_max)

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

void EnMoveGirLeft(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int et = EnkoderTarget * 2;
	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	int SrArifmetikEnkoder;
	int delta_distans_left;

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);

	do{
		SrArifmetikEnkoder= (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
		delta_distans_left =  distans_ot_robota_do_borta - SensorValue(port_left);
		GiroscopTargetDinamik = GiroscopTargetFrozen + delta_distans_left;
		if(abs(delta_distans_left)<10)
		{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	moveProporcional( GiroscopTargetFrozen - 15, 4 , v_max);	}
			else
			{	moveProporcional( GiroscopTargetFrozen + 15, 4 , v_max);  }
		}//if(abs(delta_distans_left)<10)
	}while( SrArifmetikEnkoder < et );
}//void EnMoveGirRight(int EnkoderTarget, int giroTagetXZ)

void EnMoveGir(int EnkoderTarget, int giroTagetXZ)
{
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);

	int et = EnkoderTarget * 2;
	int SrArifmetikEnkoder;

	do{
		SrArifmetikEnkoder= (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
		moveProporcional( giroTagetXZ, 1 , 100);
	}while(SrArifmetikEnkoder<et);
}//void EnMoveGir(int EnkoderTarget, int giroTagetXZ)

task main()
{
	start_init_main();

	EnMoveGirRight( 6000 , 0 );

	moveKyrsRight( 0 , 60 );

	povorot_na_1_motore(0, -90 , 100 );

	EnMoveGirRight( 200 , -90 );

	moveKyrsRight( -90 , 60 );

	povorot_na_1_motore(-90, -170 , 100 );

	EnMoveGirRight( 1700 , -180 );

	povorot_na_1_motore(-180, -210 , 100 );

	EnMoveGir( 1500 , -210 );

	povorot_na_1_motore(-210, -180 , 100 );

	EnMoveGirLeft( 2500 , -180 );

/////




	////////////////   END
	dispEndTimer();

}
