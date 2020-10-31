#include <stdio.h>
#include <conio.h>
#include <time.h>

// Parametri sistem de ord I
#define	A1	-0.9900
#define	B0	 0.0141


#define	Ti	 10
#define	Kp	 3.5

clock_t	timp,ta=0;

float	ua0;
float	ya0,ya1=0;

float read_ai(void){
	if(timp<30000)
		ya0=ua0*B0-ya1*A1;
	else
		ya0=ua0*B0-ya1*A1-10*B0;
	if(ya0<0)
		ya0=0;
	ya1=ya0;
	return(ya0);
}

void write_ao(float u){
	ua0=u;
}

int main(void){
	int		gata=0;
	float	u=0,y;

	float	ref=0;
	float	e;
	float	i0,i1=0;

	timp=clock();
	ta=timp;
	do{
		timp=clock();
		if(timp>=ta){
			// Citeste traductorul
			y=read_ai();
//
			// Genereaza comanda regulator
			e=ref-y;
			i0=i1+0.1*Kp*e/Ti;
			if(i0>100)
				i0=100;
			if(i0<0)
				i0=0;
			i1=i0;
			u=Kp*e+i0;
			if(u>100)
				u=100;
			if(u<0)
				u=0;
//
			// Aplica comanda
			write_ao(u);

			printf("[%5.1f]   R: %2.0f\tY: %7.3f\tU: %7.3f\n",timp/1000.0,ref,y,u);
			ta+=100;
		}
		if(kbhit())
		switch(getch()){
			case 'x':
				gata=1;
				break;
			case 224:
				switch(getch()){
					case 72:
						u+=1;
						if(u>100)
							u=100;
						break;
					case 80:
						u-=1;
						if(u<0)
							u=0;
						break;
				}
				break;
			case '0':
				ref=0;
				break;
			case '1':
				ref=10;
				break;
			case '2':
				ref=20;
				break;
			case '3':
				ref=30;
				break;
			case '4':
				ref=40;
				break;
			case '5':
				ref=50;
				break;
			case '6':
				ref=60;
				break;
			case '7':
				ref=70;
				break;
			case '8':
				ref=80;
				break;
			case '9':
				ref=90;
				break;
		}
	}while(gata==0);
	return(0);
}

