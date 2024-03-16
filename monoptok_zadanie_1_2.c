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

	int rul;  // tekuschij ugol rulua   global
	const int SPEED_RUL=30;

	int distans_ot_robota_do_borta=20;
	int v_max=60;
	// int gyro_real;
	const int K_usil_rula = 3;

//include


#include "init_lib.c"
#include "filter_lib.c"

//voids

void set_ugol_rul(int ff)
	{
		int f=ff;
		if(f > 60){ f=60;}
		if(f < -60){ f=-60;}
		setMotorTarget(port_rul, f, SPEED_RUL);
		waitUntilMotorStop(port_rul);
		rul=getMotorEncoder(port_rul);
	}

	void moveProporcionalrul (int GiroscopTarget, int koef_usilenia , int v_max)
	{
		int GiroscopYgolOnline = SensorValue(port_gyro);
		int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
		motor[mot_left]=v_max;
		//+Error_ygol*koef_usilenia;
		motor[mot_right]=v_max;
		//-Error_ygol*koef_usilenia;
		set_ugol_rul( Error_ygol * K_usil_rula );
	}//void moveProporcional(int GiroscopTarget, int koef_usilenia)

void EnMoveGir(int EnkoderTarget, int giroTagetXZ)
{
	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	while(1)
	{
		int SrArifmetikEnkoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right))/2;
		if(SrArifmetikEnkoder<EnkoderTarget)
		{
			int delta_distans_right =  distans_ot_robota_do_borta - filtr_itog_right;
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	moveProporcionalrul( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	moveProporcionalrul( GiroscopTargetFrozen-15, 1 , v_max);	}
				else
				{	moveProporcionalrul( GiroscopTargetFrozen+15, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(SrArifmetikEnkoder<EnkoderTarget)
		else//if(SrArifmetikEnkoder<EnkoderTarget)
		{ break; }
	}// while(1)
}//EnMoveGir(int EnkoderTarget, int giroTagetXZ)

	void povorot(int ugol_povorota, int v_max)
	{
		if(ugol_povorota<0)
		{
	    	while( ugol_povorota+5 != SensorValue(port_gyro))
	   		{
	   		   int Error_ygol = ugol_povorota - SensorValue(port_gyro);
	   		   motor[mot_left]=Error_ygol;
	   		   motor[mot_right]=-Error_ygol;
	   		}//while( ugol_povorota+5 != SensorValue(port_gyro))
		}//if(ugol_povorota<0)
		else
		{
			while( ugol_povorota-5 != SensorValue(port_gyro))
	   		{
	   		   int Error_ygol = ugol_povorota - SensorValue(port_gyro);
	   		   motor[mot_left]=Error_ygol;
	   		   motor[mot_right]=-Error_ygol;
	   		}//while( ugol_povorota-5 != SensorValue(port_gyro))
		}//else	if(ugol_povorota<0)
	}//povorot(new_kurs)

	void moveProporcional(int GiroscopTarget, int koef_usilenia , int v_max)
	{
	    int GiroscopYgolOnline = SensorValue(port_gyro);
	    int Error_ygol = GiroscopTarget - GiroscopYgolOnline;
	    motor[mot_left]=v_max+Error_ygol*koef_usilenia;
	    motor[mot_right]=v_max-Error_ygol*koef_usilenia;
	}//void moveProporcional(int GiroscopTarget, int koef_usilenia)

	void moveKyrs(int giroTagetXZ, int stoop)
	{
		int GiroscopTargetFrozen = giroTagetXZ;
		int GiroscopTargetDinamik = giroTagetXZ;
		while(1)
		{
			if(stoop<filtr_itog_nose)
			{
				int delta_distans_right =  distans_ot_robota_do_borta - filtr_itog_right;
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

	void moveKyrsNoStop(int giroTagetXZ)
	{
		int GiroscopTargetFrozen = giroTagetXZ;
		int GiroscopTargetDinamik = giroTagetXZ;

		    while(1)
		{
			int delta_distans_right =  distans_ot_robota_do_borta - filtr_itog_right;
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
		}// while(1)

	}

task main()
{
	start_init_main();

	EnMoveGir(7000, 0);

	moveKyrs(0,80);

	povorot(-90, 70);

	moveKyrs(-90,80);

	povorot(-180, 70);

	EnMoveGir(7000, -180);

	moveKyrs(-180,80);

	povorot(-270, 70);

	EnMoveGir(1000, -270);



	/////////////////
	dispEndTimer();
}
