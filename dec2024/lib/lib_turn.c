
void turn(int new_kurs, int v_max)
{
	//  povorot


	setLEDColor(ledGreen);

	

	int delta_ugol = new_kurs - SensorValue(port_gyro);
	int Error_ygol = delta_ugol;

	if( delta_ugol < 0 )
	{
		while( Error_ygol < (-5) )
		{	
			Error_ygol = new_kurs - SensorValue(port_gyro);
			motor[mot_left]=Error_ygol;
			motor[mot_right]=v_max;
			set_ugol_rul(Error_ygol)
		}//while( ugol_povorota+5 != SensorValue(port_gyro))

	}//if(ugol_povorota<0)
	else
	{
		while( Error_ygol > 5 )
		{
			Error_ygol = new_kurs - SensorValue(port_gyro);
			motor[mot_left]=v_max;
			motor[mot_right]=Error_ygol;
			set_ugol_rul(Error_ygol);
		}//while( ugol_povorota-5 != SensorValue(port_gyro))
	}//else	if(ugol_povorota<0)
	set_ugol_rul(0);
}//   turn()      void povopot_na_1_motore()
