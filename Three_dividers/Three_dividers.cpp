#include <iostream>
#include <cmath>

#define min(x,y) ((x)<(y)?(x):(y))

int main(void){

	int n, count = 0;
	std::cin >> n;
	for(int i = ceil((float)n/3); i < n-1; i++)
		for(int j = ceil( ((float)(n-i)) / 2); j <= min(i,n-i-1); j++)
			count++;

	std::cout << count;

	return 0;

}
