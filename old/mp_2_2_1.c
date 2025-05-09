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
const int distans_ot_robota_do_borta=35;
const int v_max=100;
//int gyro_real;

//include
//#include "filter_lib.c"
#include "init_lib.c"
//voids
void moveProporcional( int GiroscopTarget, int koef_usilenia , int v_max )
{
	int GiroscopYgolOnline = SensorValue(port_gyro);
	int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
	motor[mot_left]=v_max+Error_ygol*koef_usilenia;
	motor[mot_right]=v_max-Error_ygol*koef_usilenia;
}//void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)

void moveKyrsRight( int giroTagetXZ, int pregrada )
{
	setLEDColor(ledOrange);

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
	}while(pregrada<SensorValue(port_nose));
}//void moveKyrsRight(int giroTagetXZ, int pregrada)

void moveKyrsLeft( int giroTagetXZ, int pregrada )
{
	setLEDColor(ledOrange);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	int delta_distans_left;

	do{
		delta_distans_left =  distans_ot_robota_do_borta - SensorValue(port_left);
		GiroscopTargetDinamik = GiroscopTargetFrozen + delta_distans_left;
		if(abs(delta_distans_left)<10)
		{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	moveProporcional( GiroscopTargetFrozen+15, 1 , v_max);	}
			else
			{	moveProporcional( GiroscopTargetFrozen-15, 1 , v_max);	}
		}//if(abs(delta_distans_left)<10)
	}while(pregrada<SensorValue(port_nose));
}//void moveKyrsLeft(int giroTagetXZ, int pregrada)

void povorot_na_1_motore( int prohlii_ygol ,int ugol_povorota, int v_max )
{
	setLEDColor(ledGreen);
	if(ugol_povorota<prohlii_ygol)
	{
		set_ugol_rul(-40) ;
		while( ugol_povorota+5 < SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=0;
			motor[mot_right]=v_max;
		}//while( ugol_povorota+5 != SensorValue(port_gyro))
	}//if(ugol_povorota<0)
	else
	{
		set_ugol_rul(40) ;
		while( ugol_povorota-5 > SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=v_max;
			motor[mot_right]=0;
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
	set_ugol_rul(0) ;
}//void povopot_na_1_motore(int ugol_povorota, int v_max)

void EnMoveGirRight( int giroTagetXZ , int EnkoderTarget )
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

void EnMoveGirLeft( int giroTagetXZ , int EnkoderTarget )
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

void EnMoveGir( int giroTagetXZ , int EnkoderTarget )
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

void moveKyrsLeft_doBuy(int giroTagetXZ, int stoop)
{
	setLEDColor(ledOrangePulse);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	int delta_distans_left;

	do{
		delta_distans_left =  distans_ot_robota_do_borta - SensorValue(port_left);
		GiroscopTargetDinamik = GiroscopTargetFrozen + delta_distans_left;
		if(abs(delta_distans_left)<10)
		{	moveProporcional( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	moveProporcional( GiroscopTargetFrozen+15, 1 , v_max);	}
			else
			{	moveProporcional( GiroscopTargetFrozen-15, 1 , v_max);	}
		}//if(abs(delta_distans_left)<10)
	}while(stoop<SensorValue(port_right));
}//void moveKyrsLeft(int giroTagetXZ, int stoop)

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
		sleep(10)
	}while(stoop<SensorValue(port_left));
}//void moveKyrsRight(int giroTagetXZ, int stoop)


task main()
{
	start_init_main();

//	stopTask(filtr);
//	stopTask(sensors);

	EnMoveGirRight( 0 , 2000 )

	moveKyrsRight_doBuy(0,60)

		EnMoveGirRight( 0 , 1750 )

			moveKyrsRight_doBuy(0,60)

			EnMoveGirRight( 0 , 725 )

			povorot_na_1_motore( 0 ,-80, 100 )

			EnMoveGir(-90,1000)

			povorot_na_1_motore( -90 ,-170, 100 )

			///////////////////////////////////

			EnMoveGir(-180,1500)

			povorot_na_1_motore( -180 ,-260, 100 )

			EnMoveGir(-270,1000)

			povorot_na_1_motore( -270 ,-190, 100 )

			EnMoveGir(-180,1000)
/////////////////////////////////////////////////////
	    moveKyrsLeft_doBuy(-180,60)

	    EnMoveGirLeft( -180 , 1225 )

	    povorot_na_1_motore( -180 ,-100, 100 )

	    EnMoveGir(-90,1000)

	    povorot_na_1_motore( -90 ,-10, 100 )

	    EnMoveGirLeft( 0 , 2000 )

	    ///////////////////////////////////////
	    povorot_na_1_motore( 0 ,80, 100 )

	    EnMoveGir(90,700)

	    povorot_na_1_motore( 90 ,10, 100 )

	    EnMoveGir(0,2000)

	    //////////////////////////////////////////

	    povorot_na_1_motore( 0 ,-80, 100 )

	    EnMoveGir( -90 , 1000 )

	    povorot_na_1_motore( -90 ,-170, 100 )

	    EnMoveGirRight( -180 ,7000 )

	////////////////   END
	dispEndTimer();

}
