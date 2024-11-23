
void TurnAnRadius(int v_left, int v_right, int giroTagetXZ)
{
	/* povorachiwaem po radiusu poka ye dosignem nujnogo ygla giriskopa */
	if(SensorValue(port_gyro)<giroTagetXZ)
	{
	//	set_ugol_rul(30)
		while(SensorValue(port_gyro)<giroTagetXZ)
		{
			motor[mot_left]=v_left;
			motor[mot_right]=v_right;
		}
	}
	else
	{
	//	set_ugol_rul(-30)
		while((SensorValue(port_gyro)>giroTagetXZ))
		{
			motor[mot_left]=v_left;
			motor[mot_right]=v_right;
		}
	}
}
void set_ugol_rul(int ff)
{
	int f=ff;
	if(f > 60){ f=60;}
	if(f < -60){ f=-60;}
	setMotorTarget(port_rul, f, SPEED_RUL);
	waitUntilMotorStop(port_rul);
    //	rul=getMotorEncoder(port_rul);
}
