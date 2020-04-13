#include <iostream>
#include <string>
#include <vector>
using namespace std;

const unsigned PRIMARY = 401;


unsigned str_hash(const string &s, unsigned l, unsigned r, const vector<unsigned> &ptab) {
	unsigned sum = 0;
	for (unsigned i = l; i < r; i++)
		sum += (s[i]-'A'+1) * ptab[i-l];
	return sum;
}

int karp_rabin(const string &s1, const string s2, const vector<unsigned> &ptab) {
	unsigned hs1 = str_hash(s1, 0, s1.size(), ptab);
	vector<unsigned> htab(s2.size()+1, 0);
	for (unsigned i = 1; i <= s2.size(); i++)
		htab[i] = htab[i-1] + (s2[i-1]-'A'+1)*ptab[i-1];
	for (unsigned i = 0; i <= s2.size() - s1.size(); i++) {
		unsigned hs2 = htab[i+s1.size()] - htab[i];
		if (hs2 == hs1) {
			bool ok = true;
			for (unsigned j = 0; j < s1.size(); j++)
				if (s1[j] != s2[i+j])
					ok = false;
			if (ok)
				return i;
		}
		hs1 *= PRIMARY;
	}
	return -1;
}

int main() {
	string str("NKJBAFMOMMDKFNTUQNDJONVHDKAMXKKVNDJVNVINVIRBVEVPXNQOSJRCEV");
	string pat("HDKA");

	vector<unsigned> ptab(str.size(), 1);
	for(int i = 1; i < str.size(); ++i) 
		ptab[i] = ptab[i-1]*PRIMARY;

	int p = karp_rabin(pat, str, ptab);
	cout << p << '\n';
	for(int i = p; i < p + pat.size(); ++i)
		cout << str[i];

	return 0;
}