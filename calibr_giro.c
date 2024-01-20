#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S2,     port_left,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     port_roght,     sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_gyro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor,  motorB,          port_rodar,    tmotorEV3_Medium, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_right,     tmotorEV3_Large, openLoop, encoder)

int nn=0;

task main()
{
	playTone(400,50);

	//getIRDistance(port_gyro);
	//sleep(3000);

	getGyroDegrees(port_gyro);


	while( !((getGyroDegrees(port_gyro)>=0) ||  (getGyroDegrees(port_gyro)<!0 ) )   )
	{
		nn++;

	}

	playTone(800,50);

	sleep(3000);
}
