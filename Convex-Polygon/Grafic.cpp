#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cmath>



struct {
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
	
	char *pch = 0;
	Point *mas = 0;
	int amount = 0;
	
	
	while (1) {

		int f = 0;

		msgrcv (msgid, (struct msgbuf*) (&Message), 256, 0, 0);	

		switch (Message.mtype) {
			case 1:

				f = 1;
			
				int x, y;
				
				pch = strtok (Message.data, " ");
				x = atoi (pch);
				pch = strtok (NULL, " ");
				y = atoi (pch);
				++amount;
				mas = (Point*)realloc(mas, amount*sizeof(Point));
				mas[amount-1].x = x;
				mas[amount-1].y = y;
				
				break;
			
			case 2:
				f = 2;
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
			for(int j = 0; j < 130; ++j) {
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
		if (f == 1) 
			for(int i = 0; i < amount; a[25 - mas[i].y][mas[i].x + 40] = (char*)"o", ++i);
		
		//Рисование невыпуклого многоугольника
		if (f == 2){
			for (int i = 0; i < amount; ++i) {
				int i1 = (i + 1) % amount;
				if ( abs (mas[i].x - mas[i1].x) > abs (mas[i].y - mas[i1].y) )
					for (int j = mas[i].x; j != mas[i1].x; j += sgn (mas[i1].x - mas[i].x)) {
						int y = ((j - mas[i].x) * (mas[i1].y - mas[i].y) / (mas[i1].x - mas[i].x) + mas[i].y);
						a[25 - y][40 + j] = (char*)"\033[1;31m*\033[0m";	
					}
				else
					for (int j = mas[i].y; j != mas[i1].y; j += sgn (mas[i1].y - mas[i].y)) {
						int x = ((j - mas[i].y) * (mas[i1].x - mas[i].x) / (mas[i1].y - mas[i].y) + mas[i].x);
						a[25 - j][40 + x] = (char*)"\033[1;31m*\033[0m";	
					}
			}
			for(int i = 0; i < amount; a[25 - mas[i].y][mas[i].x + 40] = (char*)"o", ++i);
		}
		
		//Рисование выпуклого многоугольника
		if (f == 3){
			for (int i = 0; i < amount; ++i) {
				int i1 = (i + 1) % amount;
				if ( abs (mas[i].x - mas[i1].x) > abs (mas[i].y - mas[i1].y) )
					for (int j = mas[i].x; j != mas[i1].x; j += sgn(mas[i1].x - mas[i].x)) {
						int y = ((j - mas[i].x) * (mas[i1].y - mas[i].y) / (mas[i1].x - mas[i].x) + mas[i].y);
						a[25 - y][40 + j] = (char*)"\033[1;32m*\033[0m";	
					}
				else
					for(int j = mas[i].y; j != mas[i1].y; j += sgn (mas[i1].y - mas[i].y)) {
						int x = ((j - mas[i].y) * (mas[i1].x - mas[i].x) / (mas[i1].y - mas[i].y) + mas[i].x);
						a[25 - j][40 + x] = (char*)"\033[1;32m*\033[0m";	
					}
			}
			for (int i = 0; i < amount; a[25 - mas[i].y][mas[i].x + 40] = (char*)"o", ++i);
		} 

		if (f == 4) {
			free (mas);
			amount = 0;
		}

		for (int i = 0; i < 35; ++i) {
			for(int j = 0; j < 130; ++j)
				printf ("%s", a[i][j]);
			printf ("\n");
		}
		
	}
	
	return 0;
}