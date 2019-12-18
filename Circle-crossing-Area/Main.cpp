#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstdlib>
#include <signal.h>
#include <unistd.h>
#include <math.h>

const float Pi = 3.14;

struct {
	long mtype;
	char data [ 256 ];
	} Message;

//Площадь пересечения кругов
float Area (float r1, float x1, float y1, float r2, float x2, float y2) {

	float s1, s2;
	float dist = sqrt ( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	if (r1 < r2) {
		float t = r1;
		r1 = r2;
		r2 = t;
	}

	if (dist + r2 <= r1) {
		return Pi * r2 * r2;
	}

	if (dist >= r1 + r2) {
		return 0;
	}

	float s = sqrt ( (r1/2 + r2/2 + dist/2) * (r1/2 + r2/2 - dist/2) * (r1/2 + dist/2 - r2/2) * (dist/2 + r2/2 - r1/2) );
	float l = 2 * s / dist;
	float a1 = 2 * asin ( l / r1 );
	float a2 = 2 * asin ( l / r2 );
	if (r1 * r1 - l * l > dist * dist)
		s2 = ( r2 * r2 * ( (2 * Pi - a2) + sin(a2) ) )/2;
	 else
	 	s2 = ( r2 * r2 * (a2 - sin(a2)) ) / 2;

    s1 = ( r1 * r1 * (a1 - sin(a1)) ) / 2;
    
	return s1 + s2;
}


int main () {

	key_t key;
	key = ftok ("abcd", 'p');
	
	int msgid = msgget (key, 0666);
	
	float S, r1, r2, x1, y1, x2, y2;

	system ( "clear" );
	
	while (1) {
			
		std::cout << "\033[1;34mInput first radius \033[0m" <<std::endl;
		std::cin >> r1;

		if (r1 <= 0) {
			std::cout << "\033[1;31mWrong radius \033[0m\n";
			continue;
		}

		std::cout << "Input x1: ";
		std::cin >> x1;
		std::cout << "Input y1: ";
		std::cin >> y1;

		system ( "clear" );

		std::cout << "\033[1;34mInput second radius \033[0m" <<std::endl;
		std::cin >> r2;

		if (r2 <= 0) {
			std::cout << "\033[1;31mWrong radius \033[0m\n";
			continue;
		}

		std::cout << "Input x2: ";
		std::cin >> x2;
		std::cout << "Input y2: ";
		std::cin >> y2;

		system ( "clear" );
		
		S = Area (r1, x1, y1, r2, x2, y2);

		std::cout << "Area = " << S << std::endl;

		//Рисуем окружности
		sprintf (Message.data, "%f %f %f %f %f %f", r1, x1, y1, r2, x2, y2);
		Message.mtype = 1;
		msgsnd (msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1, 0);
		
	}
	
	return 0;
}
