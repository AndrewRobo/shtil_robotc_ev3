#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     port_left,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     port_roght,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_gyro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          port_radar,    tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#pragma DebuggerWindows("JoystickSimple")
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
init_rul();
kyrs_rul(90,2);
resetMotorEncoder(port_rul);
while(1)
{
	getJoystickSettings(joystick);
	motor[mot_left]  = joystick.joy1_y1;
	motor[mot_right] = joystick.joy1_y2;
  if(joy1Btn(Btn1))
  	{
  		if(nMotorEncoder(port_rul)<-60)
  		{}
  else
  {
  		moveMotorTarget(port_rul,-10,-10);
  		waitUntilMotorStop(port_rul);

  	}
  	}
  if(joy1Btn(Btn2))
  	{
  		if(nMotorEncoder(port_rul)>60)
  		{}
  else
  {
  		moveMotorTarget(port_rul,+10,10);
  		waitUntilMotorStop(port_rul);
 		}
}
}






































































































































































































































































































































































































































}
