#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cmath>



struct{
	long mtype;
	char data [ 256 ];
	} Message;
	
	
int sgn (int a) {
	return (a > 0 ? 1 : -1);
}

struct Point {
	int x;
	int y;
};

int main() {
	key_t key;
	key = ftok("abc", 'r');

	int msgid = msgget (key, 0666 | IPC_CREAT);
	
	char* (a[35][130]);
				
	for (int i = 0; i < 35; ++i)
		for (int j = 0; j < 130; ++j) {
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
	
	for (int i = 0; i < 35; ++i) {
		for (int j = 0; j < 130; ++j)
			printf ("%s", a[i][j]);
		printf ("\n");
	}
	
	char *pch;
	Point *mas1 = 0, *mas2 = 0;
	int amount1 = 0, amount2 = 0;
	
	
	while (1) {

		int f = 0;

		msgrcv (msgid, (struct msgbuf*) (&Message), 256, 0, 0);	
		int x, y;

		switch (Message.mtype) {
			case 1:
				f = 1;
				
				pch = strtok (Message.data, " ");
				x = atoi (pch);
				pch = strtok (NULL, " ");
				y = atoi (pch);
				++amount1;
				mas1 = (Point*)realloc(mas1, amount1*sizeof(Point));
				mas1[amount1 - 1].x = x;
				mas1[amount1 - 1].y = y;
				
				break;
			
			case 2:
				f = 1;
				
				pch = strtok (Message.data, " ");
				x = atoi(pch);
				pch = strtok (NULL, " ");
				y = atoi(pch);
				++amount2;
				mas2 = (Point*)realloc(mas2, amount2*sizeof(Point));
				mas2[amount2 - 1].x = x;
				mas2[amount2 - 1].y = y;
				
				break;
			case 3:
				f = 3;
				break;
			case 4:
				f = 4;
				break;
		}

		system ("clear") ;
			for (int i = 0; i < 35; ++i)
			for (int j = 0; j < 130; ++j) {
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
 		
 		//Рисование точек
		if (f == 1) {
			for (int i = 0; i < amount1; a[25 - mas1[i].y][mas1[i].x + 40] = (char*)"\033[1;32mo\033[0m", ++i);
			for (int i = 0; i < amount2; a[25 - mas2[i].y][mas2[i].x + 40] = (char*)"\033[1;31mo\033[0m", ++i);
		}
		
		//Рисование внешнего и внутреннего многоугольников
		if (f == 3){
			for (int i = 0; i < amount1; ++i) {
				int i1 = (i + 1) % amount1;
				if( abs (mas1[i].x - mas1[i1].x) > abs (mas1[i].y - mas1[i1].y) )
					for (int j = mas1[i].x; j != mas1[i1].x; j += sgn (mas1[i1].x - mas1[i].x)) {
						int y = ((j - mas1[i].x) * (mas1[i1].y - mas1[i].y) / (mas1[i1].x - mas1[i].x) + mas1[i].y);
						a[25 - y][40 + j] = (char*)"\033[1;32m*\033[0m";	
					}
				else
					for (int j = mas1[i].y; j != mas1[i1].y; j += sgn (mas1[i1].y - mas1[i].y)) {
						int x = ((j - mas1[i].y) * (mas1[i1].x - mas1[i].x) / (mas1[i1].y - mas1[i].y) + mas1[i].x);
						a[25 - j][40 + x] = (char*)"\033[1;32m*\033[0m";	
					}
			}

			for (int i = 0; i < amount2; ++i) {
				int i1 = (i + 1) % amount2;
				if ( abs (mas2[i].x - mas2[i1].x) > abs (mas2[i].y - mas2[i1].y))
					for (int j = mas2[i].x; j != mas2[i1].x; j += sgn (mas2[i1].x - mas2[i].x)) {
						int y = ((j - mas2[i].x) * (mas2[i1].y - mas2[i].y) / (mas2[i1].x - mas2[i].x) + mas2[i].y);
						a[25 - y][40 + j] = (char*)"\033[1;31m*\033[0m";	
					}
				else
					for (int j = mas2[i].y; j != mas2[i1].y; j += sgn (mas2[i1].y - mas2[i].y)) {
						int x = ((j - mas2[i].y) * (mas2[i1].x - mas2[i].x) / (mas2[i1].y - mas2[i].y) + mas2[i].x);
						a[25 - j][40 + x] = (char*)"\033[1;31m*\033[0m";	
					}
			}

			for (int i = 0; i < amount1; a[25 - mas1[i].y][mas1[i].x + 40] = (char*)"o", ++i);
			for (int i = 0; i < amount2; a[25 - mas2[i].y][mas2[i].x + 40] = (char*)"o", ++i);
		}

		//Удаление точек
		if (f == 4) {
			free (mas1);
			free (mas2);
			amount1 = 0;
			amount2 = 0;
		}

		for (int i = 0; i < 35; ++i) {
			for (int j = 0; j < 130; ++j)
				printf ("%s", a[i][j]);
			printf ("\n");
		}
		
	}
	
	return 0;
}
