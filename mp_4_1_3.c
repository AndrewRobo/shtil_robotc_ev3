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

int distans_ot_robota_do_borta=30;
const int v_max=100;

void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)
{
	int GiroscopYgolOnline = SensorValue(port_gyro);
	int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
	motor[mot_left]=v_max+Error_ygol*koef_usilenia;
	motor[mot_right]=v_max-Error_ygol*koef_usilenia;
}//void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)

void moveKyrsRight(int giroTagetXZ, int stoop)
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
	}while(stoop<SensorValue(port_nose));
}//void moveKyrsRight(int giroTagetXZ, int stoop)

void moveKyrsLeft(int giroTagetXZ, int stoop)
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
	}while(stoop<SensorValue(port_nose));
}//void moveKyrsLeft(int giroTagetXZ, int stoop)

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
	}while(stoop<SensorValue(port_left));
}//void moveKyrsRight(int giroTagetXZ, int stoop)

void povorot_na_1_motore(int prohlii_ygol ,int ugol_povorota, int v_max)
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

task main()
{
	start_init_main();
	//-------------------------------------------

	EnMoveGirRight( 6000 , 0 );
	       // edem do srednego encodera   6000 gradusov (5.5mbassein) po gyro kurs 0 gradusov
		   // vdol pravogo borta po pravomu UltraSonic datchuku
		   // raasoyanie do borta v globalnoj    const int distans_ot_robota_do_borta=30

	moveKyrsRight( 0 , 70 );
			// plivem po gyru kurs 0, otslegivaya pravij bort po US datchiku
			// do  borta speredi po nosovomu radarnomu US datchiku do 70 santimetrov

	povorot_na_1_motore(0, -90 , 100 );  
			// povorachivaem  s kursa 0 na kurs -90 ( nalevo ) ns skorosti 100 %

	EnMoveGirRight( 200 , -90 );
			//edem do enkodera 200 gradusov po kursu  -90,  otslejivaya pravij bort

	moveKyrsRight( -90 , 60 );
			//  po kusu -90 vdol zadnej stenki bassina, do obnarugenij radarnim US datchikom
			//  levoi stenki basseina na rasstoyanii 60 santimetro


	povorot_na_1_motore(-90, -170 , 100 );
			// povorot s kursa -90 na kurs -170 (-180 s zapasom) so skoroctyu 1000.





	//EnMoveGirRight( 1700 , -180 );
			//  edei nazad (kurs -180) vdol levoj stenki bassina 
			// otstlegivaem levuyu stenku pravim US datchikom
			// do 1/3 bassejna (encoder 1700)

    moveKyrsRight_doBuy(-180,60)




	povorot_na_1_motore(-180, -210 , 100 );
			// povorachvaem na diagonal vosmerki  s -180 na -210   so skorostyu 100 

	EnMoveGir( 1900 , -210 );  
			// dvigemsya po pervoj diagonali ( kurs -210) enkoder 1700
			// US ne smotrim

	povorot_na_1_motore(-210, -180 , 100 );
			//pravij povorot s diagolali (s kursa -210 na kurs -180) so skorostiyu 100

	EnMoveGirLeft( 2300 , -180 );
			// dvigaemsya po pravoj stenke basseina levim bortom robota
			// otslegivaem  distanci

	moveKyrsLeft(-180 , 60);

	povorot_na_1_motore(-180 , -90 , 100);

	EnMoveGirLeft( 200 , -90 );

	moveKyrsLeft(-90 , 60);

	povorot_na_1_motore(-90 , 0 , 100);

	distans_ot_robota_do_borta=20;  // ???????



	//EnMoveGirLeft( 2000 , 0 );

    moveKyrsLeft_doBuy(0 , 60);




	povorot_na_1_motore(0 , 25 , 100) ;

	EnMoveGir( 2000 , 25 );

	povorot_na_1_motore( 25 , 0 , 100) ;

	EnMoveGirRight( 1500 , 0 );

	moveKyrsRight( 0 , 70 );

	povorot_na_1_motore(0, -90 , 100 );

	EnMoveGirRight( 200 , -90 );

	moveKyrsRight( -90 , 60 );

	povorot_na_1_motore(-90, -170 , 100 );

	EnMoveGirRight( 7000 , -180 );

	////////////////   END
	dispEndTimer();

}
