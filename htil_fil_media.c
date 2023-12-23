#pragma config(Sensor, S1,     port_nose,      sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     port_giro,      sensorEV3_Gyro)
#pragma config(Motor,  motorA,          mot_left,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          port_rodar,    tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          port_rul,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          mot_rght,      tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


const int len_arr = 100;
int Arr[len_arr];
int Arr_frisen[len_arr];
int x = 1;
void maseiwe_s_datcika()
{
	int ih = 0 ;
	int whilee =1
	while(ih<len_arr)
	{
		Arr[ih]=SensorValue(port_nose);
		ih++;
		sleep(100);

	}
}
void cp_arr()
{
	int ih = 0 ;
	while(ih<len_arr)
	{
		Arr_frisen[ih]=Arr[ih];
		ih++;
	}
}
void sortirovka()
{
	int im, j;
	im=0;
	while(i<len_arr-1)
	{
		j=0
		while(j<len_arr-im-1)
		{
			if(Arr_frisen[j+1]>Arr_frisen[j])
			{
				int swap=Arr_frisen[j];
				Arr_frisen[j]=Arr_frisen[j+1];
				Arr_frisen[j+1]=swap;
			}
			j++
		}
		im++
	}
}

task main()
{
	maseiwe_s_datcika();
	cp_arr();
	sortirovka();






}
