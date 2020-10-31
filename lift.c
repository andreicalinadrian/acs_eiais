#include <stdio.h>
#include <conio.h>
#include <time.h>

int		gata=0;
time_t	timp;
time_t	timp_buton;
time_t	timp_senzor;
time_t	timp_motor=0;

int		senzor_1=0;		// Senzor pozitie etaj 1
int		senzor_2=0;		// Senzor pozitie etaj 2
int		senzor_3=0;		// Senzor pozitie etaj 3
int		senzor_4=0;		// Senzor pozitie etaj 4
int		buton_1=0;		// Buton comanda catre etaj 1
int		buton_2=0;		// Buton comanda catre etaj 2
int		buton_3=0;		// Buton comanda catre etaj 3
int		buton_4=0;		// Buton comanda catre etaj 4
int		motor_sus=0;	// Comanda motor urcare
int		motor_jos=0;	// Comana motor coborire

int		etaj=160;		// Pozitie lift (100=etaj 1, 200=etaj 2,...)

int		stare=0;		// Starea automatului de control lift

// Simulator lift
void lift(void)
{
	int			d;

	// Citire tastatura
	if(kbhit())
		switch(getch()){
			case 'x':
				gata=1;
				break;
			case '0':
				buton_1=1;
				buton_2=buton_3=buton_4=0;
				timp_buton=clock()+1000;
				break;
			case '1':
				buton_2=1;
				buton_1=buton_3=buton_4=0;
				timp_buton=clock()+1000;
				break;
			case '2':
				buton_3=1;
				buton_1=buton_2=buton_4=0;
				timp_buton=clock()+1000;
				break;
			case '3':
				buton_4=1;
				buton_1=buton_2=buton_3=0;
				timp_buton=clock()+1000;
				break;
		}

	timp=clock();

	// Gestionare persistenta butoane si senzori
	if(timp>=timp_buton)
		buton_1=buton_2=buton_3=buton_4=0;
	if(timp>=timp_senzor)
		senzor_1=senzor_2=senzor_3=senzor_4=0;

	// Simulare deplasare lift
	if(timp>=timp_motor){
			timp_motor+=100;
        if(motor_sus){
			etaj+=2;
			if(etaj>300)
				etaj=300;
        }
        if(motor_jos){
			etaj-=2;
			if(etaj<0)
				etaj=0;
        }
	}

	// Activare senzori
	switch(etaj){
		case 0:
			senzor_1=1;
			timp_senzor=clock()+1000;
			break;
		case 100:
			senzor_2=1;
			timp_senzor=clock()+1000;
			break;
		case 200:
			senzor_3=1;
			timp_senzor=clock()+1000;
			break;
		case 300:
			senzor_4=1;
			timp_senzor=clock()+1000;
			break;
	}
	// Afisare etaj, butoane, senzori, comenzi si stare automat de control lift
	printf("Nivel: %3d",etaj);

	printf("\tSenzori: ");
	d=0;
	if(senzor_1){
		printf("S0");
		d=1;
	}
	if(senzor_2){
		printf("S1");
		d=1;
	}
	if(senzor_3){
		printf("S2");
		d=1;
	}
	if(senzor_4){
		printf("S3");
		d=1;
	}
	if(d==0)
		printf("  ");

	printf("\tButoane: ");
	d=0;
	if(buton_1){
		printf("B0");
		d=1;
	}
	if(buton_2){
		printf("B1");
		d=1;
	}
	if(buton_3){
		printf("B2");
		d=1;
	}
	if(buton_4){
		printf("B3");
		d=1;
	}
	if(d==0)
		printf("  ");


	printf("\tComenzi: ");
	d=0;
	if(motor_sus){
		printf("SUS");
		d=1;
	}
	if(motor_jos){
		printf("JOS");
		d=1;
	}
	if(d==0)
		printf(" - ");


	printf("\t[Stare automat: %2d]     \r",stare);
}

int main(void)
{
	do{
		lift();

		switch(stare){
			case 0:		// Stare intitiala - se indreapta catre etajul 1
				motor_jos=1;
				if(senzor_1)
					stare=1;
				break;
			case 1:		// Lift oprit la etajul 1
				motor_sus=motor_jos=0;
				if(buton_2)
					stare=12;
				if(buton_3)
					stare=13;
				if(buton_4)
					stare=14;
				break;
			case 2:		// Lift oprit la etajul 2
				motor_sus=motor_jos=0;
				if(buton_1)
					stare=21;
				if(buton_3)
					stare=13;
				if(buton_4)
					stare=14;
				break;
			case 3:		// Lift oprit la etajul 3
				motor_sus=motor_jos=0;
				if(buton_1)
					stare=21;
				if(buton_2)
					stare=22;
				if(buton_4)
					stare=14;
				break;
			case 4:		// Lift oprit la etajul 4
				motor_sus=motor_jos=0;
				if(buton_1)
					stare=21;
				if(buton_2)
					stare=22;
				if(buton_3)
					stare=23;
				break;
			case 12:	// Lift in urcare catre etajul 2
				motor_sus=1;
				if(senzor_2)
					stare=2;
				break;
			case 13:	// Lift in urcare catre etajul 3
				motor_sus=1;
				if(senzor_3)
					stare=3;
				break;
			case 14:	// Lift in urcare catre etajul 4
				motor_sus=1;
				if(senzor_4)
					stare=4;
				break;
			case 21:	// Lift in coborire catre etajul 1
				motor_jos=1;
				if(senzor_1)
					stare=1;
				break;
			case 22:	// Lift in coborire catre etajul 2
				motor_jos=1;
				if(senzor_2)
					stare=2;
				break;
			case 23:	// Lift in coborire catre etajul 3
				motor_jos=1;
				if(senzor_3)
					stare=3;
				break;
		}
	}while(gata==0);
	return(0);
}
