
void TurnAnRadius(int v_left, int v_right, int giroTagetXZ)
{
	/* povorachiwaem po radiusu poka ye dosignem nujnogo ygla giriskopa */
	if(SensorValue(port_gyro)<giroTagetXZ)
	{
		while(SensorValue(port_gyro)<giroTagetXZ)
		{
			motor[mot_left]=v_left;
			motor[mot_right]=v_right;
		}
	}
	else
	{
		while((SensorValue(port_gyro)>giroTagetXZ))
		{
			motor[mot_left]=v_left;
			motor[mot_right]=v_right;
		}
	}
}
