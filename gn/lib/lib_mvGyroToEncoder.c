void mvGyroToEncoder(int EnkoderTarget, int gyroTarget)
{   // dvigenie po kursu s korrekciei tolko po Gyro
	// do Enkodera

	setLEDColor(ledRed);

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	//datalogClear();
	int SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	int	encoder2 = EnkoderTarget * 2 ; // chtobi summu encoderov ne delit vnutri cikla

	while( SumEncoder < encoder2 )
	{
		correct_kurs( gyroTarget, 1 , v_max);	//
		SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	} // while( SumEncoder < encoder2 )
}
