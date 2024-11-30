//init
void init_gyro()
{
    sleep(500);
    resetGyro(port_gyro);
    sleep(3000);
    resetGyro(port_gyro);
    sleep(400);
}//init_gyro()

task dispGyroInit()
{
    eraseDisplay();
    while(1)
    {
    sleep(300);
    displayBigTextLine(1, "gyro = %d grad", SensorValue(port_gyro));

    displayBigTextLine(5, "rigth= %d sm", SensorValue(port_right));
    displayBigTextLine(9, "left = %d sm", SensorValue(port_left));

    displayBigTextLine(12, "nose = %d grad", SensorValue(port_nose));
    }// while(1)
}//task monnitor()

void init_radar()
{// inicializacia naoravlenia radararadara
    // vraschaem motor radara do ogranichitela
    // i vistavlyaen nulevim kurs vpered
    int en_radar = 1;
    int en_radar2 = 2;
    motor[port_radar] = -30;
    while (en_radar != en_radar2)
    {
        en_radar2 = en_radar;
        sleep(50);
        en_radar = getMotorEncoder(port_radar);
    }//while (en_radar != en_radar2)
    //	resetMotorEncoder(port_radar);
    motor[port_radar] = 0;
    sleep(300);
    moveMotorTarget(port_radar, 100, 30); // 100 grad - 90 grad
    //                 plus experimentalnaya korrektirovka
    waitUntilMotorStop(port_radar);
    resetMotorEncoder(port_radar); // nulevim oschetom graduvov napravlinia radara delaem kurs vpered
}//init_radar()

const int SPEED_RUL=30;

void set_ugol_rul(int ff)
{
	int f=ff;
	if(f > 60){ f=60;}
	if(f < -60){ f=-60;}
	setMotorTarget(port_rul, f, SPEED_RUL);
	waitUntilMotorStop(port_rul);
    //	rul=getMotorEncoder(port_rul);
}

void init_rul()
{
    // povopot rulya do fiksatora  vdol zadnego borta
    int ryl = 1;
    int ryl2 = 2;
    motor[port_rul] = SPEED_RUL;
    while (ryl != ryl2)
    {
        ryl2 = ryl;
        sleep(50);
        ryl = getMotorEncoder( port_rul );
    }//while (ryl != ryl2)
    motor[port_rul] = 0;
    //	resetMotorEncoder(port_rul);
    sleep(300);
    // ustanavlivaem nulevim centralnoe pologenie rula
    moveMotorTarget(port_rul, -100, -SPEED_RUL); // 100 grad - 90 grad
    //                 plus experimentalnaya korrektirovka
    waitUntilMotorStop(port_rul);
    resetMotorEncoder(port_rul);
}//init_rul()


void start_init_main()
{
    //manuallySetConnectionType(port_gyro, conn_none);
    //sleep(4000);

    //resetAllSensorAutoID();
    //sleep (4000);

    init_radar();
        sleep(300);
    init_rul();
        sleep(300);
    init_gyro();
        sleep(300);


    startTask(dispGyroInit);    playTone(1600,10);
        sleep(1000);

    waitForButtonPress();    playTone(600,20);

    stopTask(dispGyroInit);

    time1[3]=0;
}

void dispEndTimer()
{ // posle zapliva  pischim, vivodim na ekran timer i gdem knopku
    motor[mot_left]=0 ;
    motor[mot_right]=0 ;

                                playTone(1200,40);

    eraseDisplay();

    displayBigTextLine(5, "time %d sek", time1[3]);

    waitForButtonPress();
    sleep(25000);

}
