//init
void init_gyro()
{
    sleep(500);
    resetGyro(port_gyro);
    sleep(4000);
    resetGyro(port_gyro);
    sleep(4000);
}//init_gyro()

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

void init_rul()
{
    // povopot rulya do fiksatora  vdol zadnego borta
    int ryl = 1;
    int ryl2 = 2;
    motor[port_rul] = 40;
    while (ryl != ryl2)
    {
        ryl2 = ryl;
        sleep(50);
        ryl = getMotorEncoder(port_rul);
    }//while (ryl != ryl2)
    motor[port_rul] = 0;
    //	resetMotorEncoder(port_rul);
    sleep(300);
    // ustanavlivaem nulevim centralnoe pologenie rula
    moveMotorTarget(port_rul, -100, -30); // 100 grad - 90 grad
    //                 plus experimentalnaya korrektirovka
    waitUntilMotorStop(port_rul);
    resetMotorEncoder(port_rul);
}//init_rul()
