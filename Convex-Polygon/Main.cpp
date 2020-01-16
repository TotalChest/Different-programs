#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <unistd.h>
#include <math.h>

struct {
	long mtype;
	char data [ 256 ];
	} Message;


struct Point {
	float x;
	float y;
};

int sgn (int a) {
	if (a == 0)
		return 2;
	return (a > 0 ? 1 : -1);
}

float Perimeter (Point* mas, int n) {
	float c = 0;
	for (int i = 0; i < n; ++i) {
		int j = (i + 1) % n;
		c += sqrt ( (mas[j].x - mas[i].x) * (mas[j].x - mas[i].x) + (mas[j].y - mas[i].y) * (mas[j].y - mas[i].y) );
	}
	return c;
}

//Площадь треугольника со знаком
float Squ (float x1, float x2, float y1, float y2) {
	return (x1 * y2 - x2 * y1) / 2;
}

//Площадь многоугольника
float Area (Point* mas, int n) {
	float s = 0;
	for (int i = 0; i < n; ++i)
		s += Squ (mas[i].x, mas[(i + 1) % n].x, mas[i].y, mas[(i + 1) % n].y);
	return abs (s);
}

float max (float a, float b) {
	return (a > b ? a : b);
}

float min (float a, float b) {
	return (a > b ? b : a);
}

//Пересечение двух прямых
bool Crosses (Point a1, Point a2, Point b1, Point b2) {

	float a = (a2.x - a1.x) * (b2.y - a1.y) - (a2.y - a1.y) * (b2.x - a1.x);
	float b = (a2.x - a1.x) * (b1.y - a1.y) - (a2.y - a1.y) * (b1.x - a1.x);
	float c = (b2.x - b1.x) * (a2.y - b1.y) - (b2.y - b1.y) * (a2.x - b1.x);
	float d = (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
 
	if ( ( sgn (a) != sgn (b) && sgn (c) != sgn (d) ) )
		return true;
	else
		return false;
}

bool Simple(Point* mas, int n) {
	for (int i = 0; i < n; ++i)
		for (int j = i + 2; j < n + i - 1; ++j)
			if (Crosses (mas[i], mas[(i + 1) % n], mas[j % n], mas[(j + 1) % n]))
				return false;
	return true;
}

int main() {
	
	key_t key;
	key = ftok ("abc", 'r');
	
	int msgid = msgget (key, 0666);
	
	Point *mas = 0;
	int n;

	system ("clear");

		
	while (1) {

		//Ввод точек многоугольника
		std::cout << "\033[1;34mInput amount of polygon vertexs: \033[0m";
		std::cin >> n;

		strcpy (Message.data, " ");
		Message.mtype = 4;
		msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		
		mas = (Point*)realloc(mas, n*sizeof(Point));
		if (n < 3) {
			std::cout << "\033[1;31mError of amount!\033[0m\n";
			free (mas);
			continue;
		}

		for (int i = 0;i < n; ++i) {
			system ("clear");
			std::cout << "\033[1;34mInput coordinates \033[0m" << std::endl;
			std::cout << "Input x: ";
			std::cin >> mas[i].x;
			std::cout << "Input y: ";
			std::cin >> mas[i].y;
		
			sprintf (Message.data, "%f %f",mas[i].x, mas[i].y);
			Message.mtype = 1;
			msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		}

		int flag = 0;
		float sgn;
		
		//Проверка на выпуклость
		for (int i = 0; i < n; ++i) {
      		int i1 = (i + 1) % n;
      		int i2 = (i + 2) % n;
      		sgn  = (mas[i1].x - mas[i].x) * (mas[i2].y - mas[i1].y) - (mas[i1].y - mas[i].y) * (mas[i2].x - mas[i1].x);
     		if (sgn < 0)
       			flag = flag | 1;
     		else if (sgn > 0)
         		flag = flag | 2;
         	if (sgn == 0)
         		flag =7;
   		}

   		if (flag == 3){
   			if (Simple (mas, n)){
   				std::cout << "Simple figure\n\033[1;31mNot convex!\033[0m\n";
   				std::cout << "Perimeter = " << Perimeter (mas, n) << "\nArea = " << Area (mas, n) << std::endl;
   			}
   			else
   				std::cout << "Not simple figure\n";
   			
   			//Постороение невыпуклой фигуры
   			strcpy (Message.data, " ");
			Message.mtype = 2;
			msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
   		}
   		else if (flag !=7 ) {
   			if (Simple (mas, n)){
      			std::cout << "Simple figure\n\033[1;32mConvex!\033[0m\n";
      			std::cout << "Perimeter = " << Perimeter (mas, n) << "\nArea = " << Area (mas, n) << std::endl;
      		}
      		else
   				std::cout << "Not simple figure\n";

   			//постороение выпуклой фигуры
      		strcpy (Message.data, " ");
			Message.mtype = 3;
			msgsnd(msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1,0);
   		}
   		else
      		std::cout << "\033[1;31mError of polygon!\033[0m\n";

		free(mas);
	
	}
	
	return 0;
}