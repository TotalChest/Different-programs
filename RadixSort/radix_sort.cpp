#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <memory.h>

using namespace std;

void radix_sort(unsigned int *a, int n)
{
	union double_word{
		unsigned int *a;
		unsigned char *c;
	} a1, a2;

	a1.a = (unsigned int*)malloc(n * sizeof(unsigned int));
	a2.a = (unsigned int*)malloc(n * sizeof(unsigned int));

	vector<unsigned int> b(257, 0);

	memcpy(a1.a, a, n * sizeof(int));

	for(short i = 0; i < 4; ++i)
	{

		if(!(i & 1u))
		{
			for(int j = 0; j < n; ++j)
				++b[a1.c[(j<<2)+i] + 1];
			for(int j = 1; j < 256; ++j)
				b[j] = b[j - 1] + b[j];
			for(int j = 0; j < n; ++j)
				a2.a[b[a1.c[(j<<2)+i]]++] = a1.a[j];
			for(int j = 0; j < 257; ++j)
				b[j] = 0;
		}
		else
		{
			for(int j = 0; j < n; ++j)
				++b[a2.c[(j<<2)+i] + 1];
			for(int j = 1; j < 256; ++j)
				b[j] = b[j - 1] + b[j];
			for(int j = 0; j < n; ++j)
				a1.a[b[a2.c[(j<<2)+i]]++] = a2.a[j];
			for(int j = 0; j < 257; ++j)
				b[j] = 0;
		}
	}

	memcpy(a, a1.a, n * sizeof(int));
	free(a1.a);
	free(a2.a);
}

const unsigned int N = 10000000;

int main()
{
	unsigned int *a = new unsigned int[N];
	
	for (int i = 0; i < N; i++)
		a[i] = rand();

	clock_t start = clock();
	radix_sort(a, N);
	clock_t end = clock();
	float radix_time = (end - start) / (float)CLOCKS_PER_SEC;

	for (int i = 0; i < N-1; i++)
        if (a[i] > a[i+1])
        {
            cout << "Radix sort failed!\n";
            break;
    	}

	for (int i = 0; i < N; i++)
		a[i] = rand();

	start = clock();
	sort(a, a+N);
	end = clock();
	float qsort_time = (end - start) / (float)CLOCKS_PER_SEC;

	for (int i = 0; i < N-1; i++)
        if (a[i] > a[i+1])
        {
            cout << "Quick sort failed!\n";
            break;
    	}

    cout.precision(7);
	cout << "Radix sort time: " << radix_time << endl;
	cout << "Quick sort time: " << qsort_time << endl;

	delete [] a;

	return 0;
}