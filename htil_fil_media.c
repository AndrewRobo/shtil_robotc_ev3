#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_giro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          port_rodar,    tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_rght,      tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


const int len_arr = 11; //dlina massivov
int Arr[len_arr];  // massiv znacenij s datchika
int Arr_frisen[len_arr]; // massiv dlya sortirovki
//int x = 1;
int caunter_if = 0;//skolko ras sravnili paru
int caunter_swp = 0;//skolko raz pomenalis mestnami

void maseiwe_s_datcika()
{  // chitaem  s datchika v massiv  Arr[]
	int ih = 0 ;
	//int whilee =1
	while(ih<len_arr)
	{
		Arr[ih]=SensorValue(port_nose);
		ih++;
		sleep(100);

	}
}

void cp_arr()
{// kopiryem massiwe arr v massiwe arr_frisen
	int ih = 0 ;
	while(ih<len_arr)
	{
		Arr_frisen[ih]=Arr[ih];
		ih++;
		A
	}
}

void sortirovka()
{// sortirovka na osnove pyzira
	datalogClear();
	int im, j;
	im=0;
	while( im < len_arr-1 )
	{
		j=0;
		while( j < len_arr-im-1 )
		{
			int tmp1=Arr_frisen[j+1];int tmp2=Arr_frisen[j];
			caunter_if++;
			int flag_swp = 0;
			if( Arr_frisen[j+1] > Arr_frisen[j] )
			{
				caunter_swp++;
				flag_swp=1;
				int swap=Arr_frisen[j];
				Arr_frisen[j]=Arr_frisen[j+1];
				Arr_frisen[j+1]=swap;
			}
			datalogDataGroupStart();
			datalogAddValue(0, im);
			datalogAddValue(1, j);
			datalogAddValue(2, tmp1);
			datalogAddValue(3, tmp2);
			datalogAddValue(4, caunter_if);
			datalogAddValue(5, caunter_swp);
			datalogAddValue(6, flag_swp);
			datalogDataGroupEnd();

			j++	;
		}
		im++;
	}
}
//nDatalogBufferSize
task main()//+++++++++++++++++++++=====+++++
{
clearTimer(1);


	maseiwe_s_datcika();
	cp_arr();
	sortirovka();
	clearTimer(2);
while(1)
{
  displayBigTextLine(3, "%d", SensorValue(port_giro));
displayBigTextLine(8, "%d", time1[1]);

displayBigTextLine(10, "%d", time1[2]);
}




}
