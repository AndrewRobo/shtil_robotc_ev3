
void mvGyroLeftToRightBui(int giroTagetXZ, int LeftBui)
{
  /* plivem po generalnomu kursu
  korrektiruyas po GYRO i levomu ultazvukovomu datchiku
  do bui (pravij ultrazvukovomu datchiku)*/

	setLEDColor(ledOrange);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	sleep(15);
	while(LeftBui<SensorValue(port_right))
	{
			sleep(15);
			int delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_left);
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<20)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen+20, 1 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen-20, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		sleep(15);
	}// while( LeftBui<SensorValue(port_left) )
}//void mvGyroRightToNose()
