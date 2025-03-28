void mvGyroToNose(int distansNose, int gyroTaget)
{
	setLEDColor(ledRed);

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	//datalogClear();
	//int SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	//int	encoder2 = EnkoderTarget * 2 ; // chtobi summu encoderov ne delit vnutri cikla

	while( distansNose < SensorValue(port_nose) )
	{
		correct_kurs( gyroTarget, 1 , v_max);	//
		SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	} 
}