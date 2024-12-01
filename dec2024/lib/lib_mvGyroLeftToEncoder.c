
void mvGyroleftToEncoder(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	//datalogClear();
	int SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	int	encoder2 = EnkoderTarget * 2 ; // chtobi summu encoderov ne delit vnutri cikla
	while( SumEncoder < encoder2 )
	{
		int delta_distans_right;
		int ff;

			ff = SensorValue(port_left);
			delta_distans_right =  distans_ot_robota_do_borta - ff;
			GiroscopTargetDinamik = GiroscopTargetFrozen + delta_distans_right;
			if(abs(delta_distans_right)<15)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-15, 2 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+15, 2 , v_max);	}
			}//if(abs(delta_distans_right)<10)

		SumEncoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right));
	} // while( SumEncoder < encoder2 )

}// mvGyroRightToEncoder(int EnkoderTarget, int giroTagetXZ)
//   EnMoveGir(int EnkoderTarget, int giroTagetXZ)
