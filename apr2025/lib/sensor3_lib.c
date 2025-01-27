int prog = 0;

int us_left()
{
	int R_left = SensorValue(port_left);

	datalogDataGroupStart();

	datalogAddValue(0,time1[3]);
	datalogAddValue(1,R_left);

	datalogAddValue(7,prog);

	datalogDataGroupEnd();
	return R_left;
}
int us_right()
{
	int R_right = SensorValue(port_right);

	datalogDataGroupStart();

	datalogAddValue(0,time1[3]);
	datalogAddValue(2,R_right);
  datalogAddValue(7,prog);

	datalogDataGroupEnd();
	return R_right;
}
int us_nose()
{
	int R_nose = SensorValue(port_nose);

	datalogDataGroupStart();

	datalogAddValue(0,time1[3]);
	datalogAddValue(3,R_nose);
  datalogAddValue(7,prog);

	datalogDataGroupEnd();
	return R_nose;
}

int gyro()
{
	int R_gyro = SensorValue(port_gyro);

	datalogDataGroupStart();

	datalogAddValue(0,time1[3]);
	datalogAddValue(4,R_gyro);

	datalogAddValue(7,prog);

	datalogDataGroupEnd();
	return R_gyro;
}
