#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cmath>


const double E = 0.1;

struct {
	long mtype;
	char data [ 256 ];
	} Message;


int main(){

	key_t key;
	key = ftok ("abcd", 'p');

	int msgid = msgget (key, 0666 | IPC_CREAT);
	
	char* (a[35][130]);
				
	for (int i=0; i<35; ++i)
		for (int j=0; j<130; ++j) {
			if (i == 25)
				a[i][j] = (char*)"\033[1;34m-\033[0m";
			else {
				if (j == 40)
					a[i][j] = (char*)"\033[1;34m|\033[0m";
				else 
					a[i][j] = (char*)"\033[1;34m \033[0m";
			}
		}
	a[0][40] = (char*)"\033[1;34m^\033[0m";
	a[25][129] = (char*)"\033[1;34m>\033[0m";
	a[25][40] = (char*)"\033[1;34m+\033[0m";
	
	for (int i=0; i<35; ++i){
		for (int j=0; j<130; ++j)
			printf ("%s", a[i][j]);
		printf ("\n");
	}
	
	char *pch = 0;
	int r1, x1, y1, r2, x2, y2;
	
	while (1) {

		msgrcv (msgid, (struct msgbuf*) (&Message), 256, 0, 0);	
	
		pch = strtok (Message.data, " ");
		r1 = atoi (pch);
		pch = strtok (NULL, " ");
		x1 = atoi (pch);
		pch = strtok (NULL, " ");
		y1 = atoi (pch);
		pch = strtok (NULL, " ");
		r2 = atoi (pch);
		pch = strtok (NULL, " ");
		x2 = atoi (pch);;
		pch = strtok (NULL, " ");
		y2 = atoi (pch);
							

		system("clear") ;

			for (int i = 0; i<35; ++i)
			for (int j = 0; j<130; ++j) {
				if (i == 25)
					a[i][j] = (char*)"\033[1;34m-\033[0m";
				else {
					if (j == 40)
						a[i][j] = (char*)"\033[1;34m|\033[0m";
					else 
						a[i][j] = (char*)"\033[1;34m \033[0m";
				}
			}
			
		a[0][40] = (char*)"\033[1;34m^\033[0m";
		a[25][129] = (char*)"\033[1;34m>\033[0m";
		a[25][40] = (char*)"\033[1;34m+\033[0m";

		for (int i = (-1) * r2; i <= r2; ++i)
			for (int j = (-1) * r2; j <= r2; ++j)
				if ( ((float)i*i)/(r2*r2) + ((float)j*j)/(r2*r2) < (1 + E) && ((float)(i-y1+y2) * (i-y1+y2))/(r1*r1) + ((float)((j-x1+x2) * (j-x1+x2))/(r1*r1)) < (1 + E) )
					a[25-i-y2][40+j+x2] = (char*)"\033[1;31mo\033[0m";

		for (int i = (-1) * r1; i <= r1; ++i)
			for (int j = (-1) * r1; j <= r1; ++j)
				if ( ( ((float)i*i)/(r1*r1) + ((float)j*j)/(r1*r1) ) < (1 + E) && ( ((float)i*i)/(r1*r1) + ((float)j*j)/(r1*r1) ) > (1 - E) )
					a[25-i-y1][40+j+x1] = (char*)"\033[1;33mo\033[0m";

		for (int i = (-1) * r2; i <= r2; ++i)
			for (int j = (-1) * r2; j <= r2; ++j)
				if ( ( ((float)i*i)/(r2*r2) + ((float)j*j)/(r2*r2) ) < (1 + E) && ( ((float)i*i)/(r2*r2) + ((float)j*j)/(r2*r2) ) >(1 - E) )
					a[25-i-y2][40+j+x2] = (char*)"\033[1;33mo\033[0m";

		
		for (int i = 0;i < 35; ++i) {
			for (int j = 0; j < 130; ++j)
				printf("%s", a[i][j]);
			printf("\n");
		}
		
	}
	
	return 0;
}
