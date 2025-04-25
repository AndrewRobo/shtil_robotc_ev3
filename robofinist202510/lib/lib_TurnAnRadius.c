
void TurnAnRadius(int v_left, int v_right, int giroTagetXZ)
{
	/* povorachiwaem po radiusu poka ye dosignem nujnogo ygla giriskopa */

setLEDColor(ledGreen);

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
