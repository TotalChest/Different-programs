#include <iostream>
#include "Mystr.hpp"


int main(){
	Mystr a;	  //without param
	Mystr b("str");	  //const str
	Mystr c(b);	  //copy
	Mystr d(5);	  //int
	Mystr e('k',3);	  //multychar
	
	
	a = b;
	a += 3;
	std::cout << a << std::endl;
	
	a = e + c;
	std::cout << a << std::endl;
	
	a += " s";
	std::cout << a << std::endl;
	
	a[2] = 'o';
	std::cout << a << std::endl;
	std::cin >> b;
	
	if (b == "win")
		printf("Yes!");
		
	if(a > b)
		std::cout << "True" << std::endl;
	else if (a < b)
		std::cout << "False" << std::endl;
	else std::cout << "Ball\n";
		
	return 0;
}
