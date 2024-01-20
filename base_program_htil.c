#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     port_left,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     port_roght,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_gyro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          port_radar,    tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int en_radar = 1;
int en_radar2 = 2;

void init_radar()/////////////////////////////////////////////////////////////////////////////////////////
{
	motor[port_radar] = 30;
	while(en_radar!=en_radar2)
	{
		en_radar2 = en_radar;

		sleep(100);
		en_radar = getMotorEncoder(port_radar);
	}
	en_radar=resetMotorEncoder(port_radar);
	motor[port_radar] = 0;
	sleep(500);
	en_radar = 0;
}
void init_gir()/////////////////////////////////////////////////////////////////////////////////////////////
{
	sleep(500);
	resetGyro(port_gyro);
	sleep(500);
}
int ryl=1;
int ryl2=2;
void init_rul()/////////////////////////////////////////////////////////////////////////////////////////////
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
}

void kyrs(int ygol,int speed)///////////////////////////////////////////////////////////////////////////////////
{
	if(en_radar!=0)
	{
		en_radar = getMotorEncoder(port_radar);
		moveMotorTarget(port_radar,-ygol,10*(-speed));
		sleep(2000);
		en_radar = getMotorEncoder(port_radar);
	}
	else
	{
		ygol = ygol+16;
		en_radar = getMotorEncoder(port_radar);
		moveMotorTarget(port_radar,-ygol,10*(-speed));
		sleep(2000);
		en_radar = getMotorEncoder(port_radar);
	}
}

void kyrs_rul(int ygol_r,int speed)//////////////////////////////////////////////////////////
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


task main()////////////////////////////////////////////////////////////////////////////////////////
{
init_radar();   // moving into the dead zone(all the way)
init_gir();     // reset giro sensor
init_rul();     // moving into the dead zone(all the way)
kyrs(90,2);     // set kyrs radar
kyrs_rul(90,2); // set kyrs rul (rudder)
int real_yg = SensorValue[port_gyro];


playTone(600,100);

sleep(1000);
}
