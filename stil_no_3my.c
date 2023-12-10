#pragma config(Sensor, S4,     port_giro,           sensorEV3_Gyro)
#pragma config(Sensor, S1,     port_nose,           sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     port_right,           sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          mot_left,          tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          port_rodar,         tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          port_rul,           tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_right,         tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int no_cikl=1;
int f;
int s;
int delt;
int kurs_war;
int real_yg =SensorValue(port_giro);
int distants_reg = 35;
int distants_real = SensorValue(port_right);
int distants_k = 1.5;
int nose_z = SensorValue(port_nose);
int en_rodar = 2;
int ryl =1;
int ryl2 =2;
int en_rodar2 = 1;
int g_yg;  //giroskop_yg

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
	home_radar();
	motor[mot_left]=100;
	motor[mot_right]=100;
	sleep(4000);
	dvig_po_byu3(80,0,50,-170,80);
	dvig_po_byu3(80,-180,50,-350,60);
	dvig_po_byu3(80,-360,50,-53,	0);
	sleep(1000);









}
