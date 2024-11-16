


void correct_kurs( int GiroscopTarget, int koef_usilenia  , int v_max )

{
/*   funkciya razovoi korrektirovki kursa po GYROdatchiku:

vistavlyaet ugol rulya i moshnosti motorov na vintah
v zavisimosti ot otklonenii ot celevogo kurca

v prediduschi versiyah nazivalas moveproporcional() */


	const int k_gyro_rul = 1;
	int dynamic_speed = v_max;

	int ugol_error = GiroscopTarget -  SensorValue(port_gyro);
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


void mvGyroRightToNose(int giroTagetXZ, int stoop)
{
  /* plivem po generalnomu kursu
  korrektiruyas po GYROskopu i pravomu ultazvukovomu datchiku
  do frontalnogo borta po nosovomu radarnomu ultrazvukovomu datchiku*/

	setLEDColor(ledOrange);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	while(1)
	{
		if(stoop<SensorValue(port_nose))
		{
			int delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_right);
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-15, 1 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+15, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(70<filtr_itog_nose)
		else//if(70>filtr_itog_nose)
		{ break; }
	}// while(1)
}//void mvGyroRightToNose()

void mvGyroRightToLeftBui(int giroTagetXZ, int LeftBui)
{
  /* plivem po generalnomu kursu
  korrektiruyas po GYROskopu i pravomu ultazvukovomu datchiku
  do frontalnogo borta po nosovomu radarnomu ultrazvukovomu datchiku*/

	setLEDColor(ledOrange);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	while(1)
	{
		if(LeftBui<SensorValue(port_left))
		{
			int delta_distans_right =  distans_ot_robota_do_borta - SensorValue(port_right);
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-15, 1 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+15, 1 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(70<filtr_itog_nose)
		else//if(70>filtr_itog_nose)
		{ break; }
	}// while(1)
}//void mvGyroRightToNose()


void turn(int new_kurs, int v_max)
{
    /*  povorot

    est oshibra s pologitelnimi i otricatelnimi povorotami*/


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



void mvGyroRightToEncoder(int EnkoderTarget, int giroTagetXZ)
{
	setLEDColor(ledRed);

	int GiroscopTargetFrozen = giroTagetXZ;
	int GiroscopTargetDinamik = giroTagetXZ;
	resetMotorEncoder(mot_left);
	resetMotorEncoder(mot_right);
	datalogClear();
	while(1){
		int delta_distans_right;
		int ff;
		int SrArifmetikEnkoder = (getMotorEncoder(mot_left)+getMotorEncoder(mot_right))/2;
		if(SrArifmetikEnkoder<EnkoderTarget)
		{
			ff = SensorValue(port_right);
			delta_distans_right =  distans_ot_robota_do_borta - ff;
			GiroscopTargetDinamik = GiroscopTargetFrozen - delta_distans_right;
			if(abs(delta_distans_right)<10)
			{	correct_kurs( GiroscopTargetDinamik, 1 , v_max);	}
			else
			{
				if(GiroscopTargetFrozen-GiroscopTargetDinamik>0)
				{	correct_kurs( GiroscopTargetFrozen-30, 3.5 , v_max);	}
				else
				{	correct_kurs( GiroscopTargetFrozen+30, 3.5 , v_max);	}
			}//if(abs(delta_distans_right)<10)
		}//if(SrArifmetikEnkoder<EnkoderTarget)
		else//if(SrArifmetikEnkoder<EnkoderTarget)
		{ break; }
	}// while(1)
}// mvGyroRightToEncoder(int EnkoderTarget, int giroTagetXZ)
//   EnMoveGir(int EnkoderTarget, int giroTagetXZ)
