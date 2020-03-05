#include <iostream>
#include <string>

int main()
{
	unsigned int k;
	std::string S, temp;
	std::cin >> S >> temp;

	S = temp + '@' + S;
	unsigned int *m = new unsigned int[S.length()];


	for(size_t i = 0; i < S.length(); ++i)
		m[i] = 0;

	for(size_t i = 1; i < S.length(); ++i)
	{

		k = m[i - 1];

		while(k > 0 && S[i] != S[k])
			k = m[k - 1];

		if(S[i] == S[k])
			k++;

		m[i] = k;

	}

	for(size_t i = 0; i < S.length(); ++i)
		if(m[i] == temp.length())
			std::cout << i - 2 * temp.length() << std::endl;

	delete []m;

	return 0;
}