

void moveProporcional( int GiroscopTarget, int koef_usilenia  , int v_max )

{
	const int k_gyro_rul = 1;
	int dynamic_speed = v_max;

	int ugol_error = GiroscopTarget -  SensorValue(port_giro);
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

	set_ugol_rul ( k_gyro_rul * urol_error);

}
