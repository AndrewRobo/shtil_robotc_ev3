#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_giro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          port_rodar,    tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// zima, gorodskie sorevnovaniya fml239 vdk kirova
// 4e zadanie. vomerka - nareziltat ne proehala
// komanda shtil2 (5 mesto - zecteno tolko 3e zadanie - s drugoi prog

int no_cikl=1;
int f;
int s;
int delt;
int kurs_war;
int real_yg =SensorValue(port_giro);
int distants_reg = 10;
int distants_real = SensorValue(port_right);
int distants_k = 1;
int nose_z = SensorValue(port_nose);
int en_rodar = 2;
int ryl =1;
int ryl2 =2;
int en_rodar2 = 1;
int g_yg;  //giroskop_yg
int distants_k_gyro = 10;
int speed_koef_gyro = 10;

void set_rul_zero(int ff)
{
	f=ff;
	s=getMotorEncoder(port_rul);
	if(f > 60){ f=60;}
	if(f < -60){ f=-60;}
	int x;
	if(delt<0){ x=1;}
	else { x=-1;}
	setMotorTarget(port_rul, f, 30);
	waitUntilMotorStop(port_rul);
}

void home_radar()
{
	motor[port_rodar] = 30;
	while(en_rodar!=en_rodar2)
	{
		en_rodar2 = en_rodar;

		sleep(100);
		en_rodar = getMotorEncoder(port_rodar);
	}
	en_rodar=resetMotorEncoder(port_rodar);
	motor[port_rodar] = 0;
	sleep(500);
	en_rodar = 0;
}///////////////////////////
void kyrs(int ygol,int speed)
{
	if(en_rodar!=0)
	{
		en_rodar = getMotorEncoder(port_rodar);
		moveMotorTarget(port_rodar,-ygol,30*(-speed));
		sleep(2000);
		en_rodar = getMotorEncoder(port_rodar);
	}
	else
	{
		ygol = ygol+16;
		en_rodar = getMotorEncoder(port_rodar);
		moveMotorTarget(port_rodar,-ygol,30*(-speed));
		sleep(2000);
		en_rodar = getMotorEncoder(port_rodar);
	}
}
void home_gir()
{///////////////////
	sleep(500);
	resetGyro(port_giro);
	sleep(500);
}//////////////////////
void home_rul()
{
	{
		while( ryl !=  ryl2)
		{
			ryl2 = ryl;
			motor[port_rul] = 50;
			sleep(100);
			ryl = getMotorEncoder(port_rul);
		}
		ryl=resetMotorEncoder(port_rul);
		sleep(500);
	}
	ryl = 0;
}////////////////////////////////
void kyrs_rul(int ygol_r,int speed)
{
	if(ryl!=0)
	{
		ryl = getMotorEncoder(port_rul);
		moveMotorTarget(port_rul,-ygol_r,30*(-speed));
		sleep(2000);
		ryl = getMotorEncoder(port_rul);
	}
	else
	{
		ygol_r = ygol_r+16;
		ryl = getMotorEncoder(port_rul);
		moveMotorTarget(port_rul,-ygol_r,30*(-speed));
		sleep(2000);
		ryl = getMotorEncoder(port_rul);
	}
}

/*
///////////////////////////////////////
void dvig_po_bort(int v_max,int cel_yg,int ice)
{
int shet = 1;
while(1)
{

nose_z = SensorValue(port_nose);
if(real_yg>-260)
{
real_yg =SensorValue(port_giro);
distants_real = SensorValue(port_right);
if(nose_z<ice)
{
shet = shet + 1;
if(shet>5)
{
while(nose_z<80)
{
real_yg =SensorValue(port_giro);
if(real_yg<-260)
{
break;
}
nose_z = SensorValue(port_nose);
motor[mot_left]=0;
setMotorTarget(port_rul, -45, 100);
}
shet = 1;
}
}
else
{
motor[mot_left]=v_max;
motor[mot_right]=v_max;
distants_real = SensorValue(port_right);
int distants_eror =distants_reg - distants_real;
kurs_war = distants_k * distants_eror;
real_yg =SensorValue(port_giro);
set_rul_zero(-kurs_war);
}
}
else
{
motor[mot_left]=v_max;
motor[mot_right]=v_max;
distants_real = SensorValue(port_right);
int distants_eror =distants_reg - distants_real;
kurs_war = distants_k * distants_eror;
real_yg =SensorValue(port_giro);
set_rul_zero(-kurs_war);

}
}
}
*/

void dvig_po_byu3(int v_max,int cel_yg,int byu, int g_yg2, int cikl_fin)
{
	g_yg = g_yg2;
	int shet = 1;
	no_cikl=0;
	while(1)
	{
		no_cikl=no_cikl+1;
		if(no_cikl<cikl_fin)
		{
			nose_z = SensorValue(port_nose);
			if(real_yg>g_yg)
			{
				real_yg =SensorValue(port_giro);
				distants_real = SensorValue(port_right);
				if(nose_z<byu)
				{
					shet = shet + 1;
					if(shet>5)
					{
						while(nose_z<byu)
						{
							real_yg =SensorValue(port_giro);
							if(real_yg<g_yg)
							{
								break;
							}
							nose_z = SensorValue(port_nose);

							motor[mot_left]=v_max/5;
							setMotorTarget(port_rul, -45, 100);
						}
						shet = 1;
					}
				}
				else
				{
					motor[mot_left]=v_max;
					motor[mot_right]=v_max;
					distants_real = SensorValue(port_right);
					int distants_eror =distants_reg - distants_real;
					kurs_war = distants_k * distants_eror;
					real_yg =SensorValue(port_giro);
					set_rul_zero(-kurs_war);
				}
			}
			else
			{
				motor[mot_left]=v_max;
				motor[mot_right]=v_max;
				distants_real = SensorValue(port_right);
				int distants_eror =distants_reg - distants_real;
				kurs_war = distants_k * distants_eror;
				real_yg =SensorValue(port_giro);
				set_rul_zero(-kurs_war);

			}
		}
		else
		{
			break;
		}
	}
}
void kyrs_rul_gir_bye(int kuyrs/*-210*/, int v_max, int byu)
{
	distants_real = SensorValue(port_giro);
	nose_z = SensorValue(port_nose);
	int counter = 0;
	bool object_detected = false;

	while (1) {
		if (nose_z>byu) counter++;////////////////////////////////////////////////////////////////
		else {
			counter=0;
			if (object_detected) break;
		}
		if (counter>=3) object_detected=true;


		int dynamic_speed = v_max;



		distants_real = SensorValue(port_giro);
		int distants_error =kuyrs - distants_real;
		dynamic_speed -= speed_koef_gyro*(abs(distants_error));
		if (dynamic_speed>100)
			dynamic_speed=v_max;
		else if (dynamic_speed<-v_max)
			dynamic_speed=-v_max;
		else if (dynamic_speed>0 && dynamic_speed<=15)
			dynamic_speed=0;
		else if (dynamic_speed<0 && dynamic_speed>=-15)
			dynamic_speed=0;

		kurs_war = distants_k_gyro * distants_error;

		if (distants_error<=0){
			motor[mot_left]=dynamic_speed;
			motor[mot_right]=v_max;
		}
		else {
			motor[mot_left]=v_max;
			motor[mot_right]=dynamic_speed;
		}
		real_yg =SensorValue(port_giro);
		set_rul_zero(kurs_war);




		nose_z = SensorValue(port_nose);
	}


	motor[mot_left]=0;
	motor[mot_right]=0;


}

void kyrs_rul_gir(int kuyrs/*-210*/, int v_max, int byu)
{
	distants_real = SensorValue(port_giro);
	nose_z = SensorValue(port_nose);
	int counter = 0;
	bool object_detected = false;

	while (1) {
		if (nose_z<byu) counter++;
		else {
			counter=0;
		}
		if (counter>=5) break;


		int dynamic_speed = v_max;



		distants_real = SensorValue(port_giro);
		int distants_error =kuyrs - distants_real;
		dynamic_speed -= speed_koef_gyro*(abs(distants_error));
		if (dynamic_speed>100)
			dynamic_speed=v_max;
		else if (dynamic_speed<-v_max)
			dynamic_speed=-v_max;
		else if (dynamic_speed>0 && dynamic_speed<=15)
			dynamic_speed=0;
		else if (dynamic_speed<0 && dynamic_speed>=-15)
			dynamic_speed=0;

		kurs_war = distants_k_gyro * distants_error;

		if (distants_error<=0){
			motor[mot_left]=dynamic_speed;
			motor[mot_right]=v_max;
		}
		else {
			motor[mot_left]=v_max;
			motor[mot_right]=dynamic_speed;
		}
		real_yg =SensorValue(port_giro);
		set_rul_zero(kurs_war);




		nose_z = SensorValue(port_nose);
	}


	motor[mot_left]=0;
	motor[mot_right]=0;


}

void rotate_boat(int kuyrs/*-210*/, int v_max)
{
	distants_real = SensorValue(port_giro);

	while (1) {


		int dynamic_speed = v_max;



		distants_real = SensorValue(port_giro);
		int distants_error =kuyrs - distants_real;

		if (abs(distants_error)<5) break;

		dynamic_speed -= speed_koef_gyro*(abs(distants_error));
		if (dynamic_speed>100)
			dynamic_speed=v_max;
		else if (dynamic_speed<-v_max)
			dynamic_speed=-v_max;
		else if (dynamic_speed>0 && dynamic_speed<=15)
			dynamic_speed=0;
		else if (dynamic_speed<0 && dynamic_speed>=-15)
			dynamic_speed=0;

		kurs_war = distants_k_gyro * distants_error;

		if (distants_error<=0){
			motor[mot_left]=dynamic_speed;
			motor[mot_right]=v_max;
		}
		else {
			motor[mot_left]=v_max;
			motor[mot_right]=dynamic_speed;
		}
		real_yg =SensorValue(port_giro);
		set_rul_zero(kurs_war);




		nose_z = SensorValue(port_nose);
	}


	motor[mot_left]=0;
	motor[mot_right]=0;


}

void circle_move_boat(){

}


task main()
{
	home_rul();
	//	playTone(600,10);
	home_gir();
	//	playTone(700,10);
	home_radar();
	//	playTone(800,100);
	sleep(1000);

	kyrs(90,1);
	//	playTone(700,100);
	kyrs_rul(90,1);
	resetMotorEncoder(port_rul);
	playTone(600,100);

	sleep(1000);
	waitForButtonPress();
	playTone(600,100);

	sleep(1000);
	// home_radar();
	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2500);
	home_radar();
	// kyrs_rul_gir(0, 80, 50);
	// kyrs_rul_gir(0, 80, 50);
	// dvig_po_byu3(80,0,50,-180, 3);
	int speed_main = 60;

	kyrs_rul_gir_bye(0, speed_main, 70);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(1000);

	kyrs_rul_gir_bye(0, speed_main, 75);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2500);

	rotate_boat(-90, speed_main);

	kyrs_rul_gir_bye(-90, speed_main, 150);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2000);

 	rotate_boat(-180, speed_main);

	kyrs_rul_gir_bye(-180, speed_main, 75);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2500);

 	rotate_boat(-270, speed_main);

 	kyrs_rul_gir_bye(-270, speed_main, 75);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(1500);

 	rotate_boat(-180, speed_main);

 		kyrs(185,1);//1 povorot rodara

 			kyrs_rul_gir_bye(-180, speed_main, 60);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(3000);

 	rotate_boat(-90, speed_main);

 	 			kyrs_rul_gir_bye(-90, speed_main, 150);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(500);

	rotate_boat(5, speed_main);

	 	 			kyrs_rul_gir_bye(5, speed_main, 75);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2500);

		rotate_boat(95, speed_main);

	 	 			kyrs_rul_gir_bye(95, speed_main, 150);
	playSound(soundBlip);

	motor[mot_left]=40;
	motor[mot_right]=40;
	sleep(2500);

	rotate_boat(5, speed_main);


}
