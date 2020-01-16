#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <unistd.h>
#include <math.h>


struct{
	long mtype;
	char data [ 256 ];
	} Message;


struct Point {
	float x;
	float y;
};

float min (float a, float b) {
	return a < b ? a : b;
}

//Пересечение луча со стороной многоугольника
bool Crosses (Point p1, Point p2, Point z) {

	if (p1.y == p2.y)
		return false;

	if (min (p1.y, p2.y) != p1.y) {
		Point t = p1;
		p1 = p2;
		p2 = t;
	}

	if (z.y <= p2.y && z.y > p1.y && ((z.x - p1.x) * (p2.y - p1.y) - (z.y - p1.y) * (p2.x - p1.x)) > 0)
		return true;
	return false;
}

int sgn (int a) {
	if (a == 0)
		return 2;
	return (a > 0 ? 1 : -1);
}

//пресечение двух отрезков99
bool Crosses2 (Point a1, Point a2, Point b1, Point b2) {

	float a = (a2.x - a1.x) * (b2.y - a1.y) - (a2.y - a1.y) * (b2.x - a1.x);
	float b = (a2.x - a1.x) * (b1.y - a1.y) - (a2.y - a1.y) * (b1.x - a1.x);
	float c = (b2.x - b1.x) * (a2.y - b1.y) - (b2.y - b1.y) * (a2.x - b1.x);
	float d = (b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x);
 
	if ( ( sgn (a) != sgn (b) && sgn (c) != sgn (d) ) )
		return true;
	else
		return false;
}

int main(){
	
	key_t key;
	key = ftok("abc", 'r');
	
	int msgid = msgget(key, 0666);
	
	Point *mas1 = 0, *mas2 = 0;
	int n, m;

	system ("clear");

		
	while (1) {

		//Вовод вершин внешненго многоугольника
		std::cout << "\033[1;34mInput amount of external polygon vertexs: \033[0m";
		std::cin >> n;

		strcpy (Message.data, " ");
		Message.mtype = 4;
		msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		
		mas1 = (Point*)realloc(mas1, n*sizeof(Point));
		if (n < 3) {
			std::cout << "\033[1;31mError of amount!\033[0m\n";
			free (mas1);
			continue;
		}
		for (int i = 0; i < n; ++i) {
			system ("clear");
			std::cout << "\033[1;34mInput coordinates \033[0m" << std::endl;
			std::cout << "Input x: ";
			std::cin >> mas1[i].x;
			std::cout << "Input y: ";
			std::cin >> mas1[i].y;
		
			sprintf (Message.data, "%f %f", mas1[i].x, mas1[i].y);
			Message.mtype = 1;
			msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		}

		int flag = 0;
		float sgn;
		
		//Проверка ввода многоугольника
		for (int i = 0;i < n; ++i) {
      		int i1 = (i + 1) % n;
      		int i2 = (i + 2) % n;
      		sgn  = (mas1[i1].x - mas1[i].x) * (mas1[i2].y - mas1[i1].y) - (mas1[i1].y - mas1[i].y) * (mas1[i2].x - mas1[i1].x);
         	if (sgn == 0)
         		flag = 1;
   		}

   		if (flag == 1) {
   			std::cout << "\033[1;31mError of polygon!\033[0m\n";
   			free (mas1);
   			continue;
   		}

   		//Ввод вершин внутреннего многоугольника
		std::cout << "\033[1;34mInput amount of internal polygon vertexs: \033[0m";
		std::cin >> m;

		mas2 = (Point*)realloc(mas2, m*sizeof(Point));
		if ( m<3 ){
			std::cout << "\033[1;31mError of amount!\033[0m\n";
			free (mas1);
			free (mas2);
			continue;
		}

		for (int i = 0; i < m; ++i) {
			system ("clear");
			std::cout << "\033[1;34mInput coordinates \033[0m" << std::endl;
			std::cout << "Input x: ";
			std::cin >> mas2[i].x;
			std::cout << "Input y: ";
			std::cin >> mas2[i].y;
		
			sprintf (Message.data, "%f %f", mas2[i].x, mas2[i].y);
			Message.mtype=2;
			msgsnd(msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		}

		//Проверка ввода многоугольника
		for (int i = 0; i < m; ++i) {
      		int i1 = (i + 1) % m;
      		int i2 = (i + 2) % m;
      		sgn  = (mas2[i1].x - mas2[i].x) * (mas2[i2].y - mas2[i1].y) - (mas2[i1].y - mas2[i].y) * (mas2[i2].x - mas2[i1].x);
         	if (sgn == 0)
         		flag = 1;
   		}

   		if (flag == 1) {
   			std::cout << "\033[1;31mError of polygon!\033[0m\n";
   			free (mas1);
   			free (mas2);
   			continue;
   		}

		int c1 = 0,c2 = 0;

		//Вершины внутреннего лежат внутри внешнего?
		for (int i = 0; i < m; ++i) {
			int L = 0;

			for (int j = 0; j < n; ++j)
				if ( Crosses (mas1[j], mas1[(j + 1) % n ], mas2[i]) )
					++L;
			if (L % 2)
				++c1;
		}

		//Стороны внешнего пересекаются со сторонами внутреннего?
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j)
				if (Crosses2 (mas1[i], mas1[(i+1)%n], mas2[j], mas2[(j + 1) % m]))
					++c2;

		}

		if (c1 == m && c2 == 0)
			std::cout << "\033[1;32mThe polygon lies inside!\033[0m\n";
		else
			std::cout << "\033[1;31mThe polygon does not lie inside!\033[0m\n";

		strcpy (Message.data, " ");
			Message.mtype = 3;
			msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);

		free (mas1);
		free (mas2);

	}
	
	return 0;
}