#pragma config(Sensor, S1, port_nose, sensorEV3_Ultrasonic)
#pragma config(Sensor, S2, port_left, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3, port_right, sensorEV3_Ultrasonic)
#pragma config(Sensor, S4, port_gyro, sensorEV3_Gyro)
#pragma config(Motor, motorA, mot_left, tmotorEV3_Large, openLoop, encoder)
#pragma config(Motor, motorB, port_radar, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorC, port_rul, tmotorEV3_Medium, openLoop, encoder)
#pragma config(Motor, motorD, mot_right, tmotorEV3_Large, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// zamer uplivania girodatchika

const int LEN_ARR=120;
int arr_gyro[2][LEN_ARR];

int pointer=0; 

const int v_max = 50;

long krug=0;
int kk = 1;



task main()
{

 
  time1[0]=0;

 	sleep(500);
    
	resetGyro(port_gyro);
	sleep(3000);

	resetGyro(port_gyro);
	sleep(4000);
    
    playtone(400,50);

  
            arr_gyro[0][pointer] = time1[0];
            arr_gyro[1][pointer]  = SensorValue( port_gyro );

  
                displayBigTextLine(1,"%d",arr_gyro[0][pointer]);
                displayBigTextLine(3,"%d",arr_gyro[1][pointer]);

            pointer++;        


        while(krug < 1000 )
        {
            arr_gyro[0][pointer] = time1[0];
            arr_gyro[1][pointer]  = SensorValue( port_gyro );


            if ( pointer== 0 ){
                displayBigTextLine(6,"%d",krug)
                displayBigTextLine(8,"%d",arr_gyro[0][pointer]);
                displayBigTextLine(10,"%d",arr_gyro[1][pointer]);
              }
              
                displayBigTextLine(12,"%d",arr_gyro[0][pointer]);
                displayBigTextLine(14,"%d",arr_gyro[1][pointer]);


            pointer++;

            if ( pointer >= LEN_ARR )
             { pointer = 0 ;
               krug++;
                if ( kk > 0 ) { kk = -1; }else{ kk = 1; }
                motor[mot_left] = v_max *  kk ;
                motor[mot_right] = - v_max * kk;
               playtone(400,50);
             }

            sleep(1000);


        }


}
