    int my_timer;
    int my_delta_timer;

    int filtr_itog_left;
    int filtr_itog_nose;
    int filtr_itog_right;

//massives
    const int len_left_real = 17;
    int arr_left[len_left_real];
    int ih_left = 0;

    const int len_left_frozen = 11;
    const int middle_left = len_left_frozen/2;
    int arr_left_frozen[len_left_frozen];

    //////////////////////////////////////////////////////////////////////////
    const int len_right_real = 19;
    int arr_right[len_right_real];
    int ih_right = 0;

    const int len_right_frozen = 11;
    const int middle_right = len_right_frozen/2;
    int arr_right_frozen[len_right_frozen];

    //////////////////////////////////////////////////////////////////////////
    const int len_nose_real = 20;
    int arr_nose[len_nose_real];
    int ih_nose = 0;

    const int len_nose_frozen = 11;
    const int middle_nose = len_nose_frozen/2;
    int arr_nose_frozen[len_nose_frozen];

//voids
    void buble_sort( int *arr, int lenn )
    { // sortirovka puzirkom
        int tmp;
        int last = lenn - 1;
        do{
            tmp = 0;
            for( int n = last ;   n > 0 ;   n-- )
            {
                if (arr[ n-1 ] > arr[ n ])
                {
                    int imp = arr[ n ];
                    arr[ n ] = arr[ n-1 ];
                    arr[ n-1 ] = imp;
                    tmp++;
                }//if (arr[ n-1 ] > arr[ n ])
            }//for( int n = last ;   n > 0 ;   n-- )
        }while ( tmp > 0 );
    }//void buble_sort( int *arr, int lenn )

    void frozen( int* raw, int len_raw, int raw_pointer, int* frozen, int len_frozen   )
    { // ficsaruem - zamorajivae  massiv dlya sortirovki
        int ih = raw_pointer-1 ;
        if ( ih < 0 ) {ih = len_raw - 1;}

        for( int ii = len_frozen - 1; ii >= 0; ii-- )
        {
            frozen[ii] = raw[ih];
            ih--;
            if ( ih < 0 ) {ih = len_raw - 1;}
        }//for( int ii = len_frozen - 1; ii >= 0; ii-- )
    }//void frozen( int* raw, int len_raw, int raw_pointer, int* frozen, int len_frozen   )


//tasks
    task sensors()
    { // oprashivaem datchiki i po krugu zapisivaem v massivi
        // originalnih poslednih znachenij datchika
        while (1)
        {

            arr_left[ ih_left ] = SensorValue(port_left);
            ih_left++;
            if (ih_left >= len_left_real)	{ih_left = 0;}
            sleep(10);

            arr_right[ih_right] = SensorValue(port_right);
            ih_right++;
            if (ih_right >= len_right_real)		{ih_right = 0;}
            sleep(10);

            arr_nose[ih_nose] = SensorValue(port_nose);
            ih_nose++;
            if (ih_nose >= len_nose_real)	{ih_nose = 0;}
            sleep(10);

        } // while(1)
    } // task sensors()

    task filtr()
        {
            time1[0]=0;
            while(1)
            {
                my_timer=time1[0];
    
                frozen( arr_right, len_right_real, ih_right, arr_right_frozen, len_right_frozen);
                buble_sort( arr_right, len_right_real );
                filtr_itog_right = arr_right_frozen[middle_right];
    
                frozen( arr_nose, len_nose_real, ih_nose, arr_nose_frozen, len_nose_frozen);
                buble_sort( arr_nose, len_nose_real );
                filtr_itog_nose = arr_nose_frozen[middle_nose];
    
                my_delta_timer=time1[0]- my_timer ;
    
                //displayBigTextLine(10, "%d", my_delta_timer);
            }// while(1)
        }//task filtr()