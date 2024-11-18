
void turn(int new_kurs, int v_max)
{
	//  povorot


	setLEDColor(ledGreen);

	int ugol_povorota = new_kurs;

	int delta_ugol = ugol_povorota - SensorValue(port_gyro);


	if( delta_ugol < 0 )
	{
		while( ugol_povorota+5 < SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=v_max;
			set_ugol_rul(-40);
		}//while( ugol_povorota+5 != SensorValue(port_gyro))
	}//if(ugol_povorota<0)
	else
	{
		while( ugol_povorota-5 > SensorValue(port_gyro))
		{
			int Error_ygol = ugol_povorota - SensorValue(port_gyro);
			motor[mot_left]=v_max;
			motor[mot_right]=Error_ygol;
			set_ugol_rul(40);
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
	set_ugol_rul(0);
}//   turn()      void povopot_na_1_motore()
