void mvGyroToNose(int gyroTarget, int NoseStop)
{   // dvigenie po kursu s korrekciei tolko po Gyro
	// do Enkodera

	setLEDColor(ledRed);

	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	//datalogClear();
  int f = SensorValue(port_nose)
	while( f > NoseStop )
	{
		f = SensorValue(port_nose)
		correct_kurs( gyroTarget, 1 , v_max);
	} // while( SumEncoder < encoder2 )
}
