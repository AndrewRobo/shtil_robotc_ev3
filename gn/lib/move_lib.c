


void correct_kurs( int GiroscopTarget, int koef_usilenia  , int v_max )
{
	/*   funkciya razovoi korrektirovki kursa po GYROdatchiku:

	vistavlyaet ugol rulya i moshnosti motorov na vintah
	v zavisimosti ot otklonenii ot celevogo kurca

	v prediduschi versiyah nazivalas moveproporcional() */

	const int k_gyro_rul = 1;
	int dynamic_speed = v_max;

	int ugol_error = GiroscopTarget -  gyro();
	dynamic_speed -= koef_usilenia * ( abs( ugol_error ) );
	if ( dynamic_speed > v_max ) 	    dynamic_speed=v_max;
	else if (dynamic_speed < -v_max )	dynamic_speed=-v_max;
	else if ( dynamic_speed>0 && dynamic_speed<=15 )  dynamic_speed=0;
	else if ( dynamic_speed<0 && dynamic_speed>=-15 ) dynamic_speed=0;
	if ( ugol_error <=0 ){
		motor[mot_left]=dynamic_speed;
		motor[mot_right]=v_max;
	}
	else {
		motor[mot_left]=v_max;
		motor[mot_right]=dynamic_speed;
	}

	set_ugol_rul ( k_gyro_rul * ugol_error);

}


void mvGyroRightToNose(int gyroTaget, int stop_nose)
{
	/* plivem po generalnomu kursu
	korrektiruyas po GYROskopu i pravomu ultazvukovomu datchiku
	do frontalnogo borta po nosovomu radarnomu ultrazvukovomu datchiku*/

	setLEDColor(ledOrange);
	prog = 2 ;

	int GiroscopTargetFrozen = gyroTaget;
	int GiroscopTargetDinamik = gyroTaget;

	while( stop_nose < us_nose() )
	{
		int delta_distans_right =  distans_ot_robota_do_borta - us_right();
		GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
		if(abs(delta_distans_right)<20)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
		else
		{
			if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
			{	correct_kurs( GiroscopTargetFrozen-20, 1 , v_max);	}
			else
			{	correct_kurs( GiroscopTargetFrozen+20, 1 , v_max);
			}
		}//if(abs(delta_distans_right)<10)

	}// while(stoop<SensorValue(port_nose))

}//void mvGyroRightToNose()







void mvGyroRightToEncoder(int EnkoderTarget, int gyroTaget)
{
	setLEDColor(ledRed);
	prog = 1 ;

	int GiroscopTargetFrozen = gyroTaget;
	int GiroscopTargetDinamik = gyroTaget;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	//datalogClear();
	int SumEncoder = sum_encoder();
	int	encoder2 = EnkoderTarget * 2 ; // chtobi summu encoderov ne delit vnutri cikla
	while( SumEncoder < encoder2 )
	{
		int delta_distans_right;
		int ff;


			ff = us_right();
			delta_distans_right =  distans_ot_robota_do_borta - ff;
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<20)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-20, 1, v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+20, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)

		SumEncoder = sum_encoder();
	} // while( SumEncoder < encoder2 )

}// mvGyroRightToEncoder(int EnkoderTarget, int giroTagetXZ)
//   EnMoveGir(int EnkoderTarget, int giroTagetXZ)
