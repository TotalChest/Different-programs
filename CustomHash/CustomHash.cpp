#include <bits/stdc++.h>
using namespace std;

struct SomeStruct {
	int a;
	float c;

	SomeStruct(int a = 0, float c = 0): a(a), c(c) {}

	bool operator==(const SomeStruct &oth) const{
		return (oth.a == a && oth.c == c); 
	}
};

struct SomeHash {
	size_t operator()(const SomeStruct &key) const {
		return ((size_t)key.c*401 + 31415) ^ key.a*27183; 
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << SomeHash()(SomeStruct(11,18.5)) << endl;

	unordered_set<SomeStruct, SomeHash> Set;
	Set.insert(SomeStruct(5,6));
	Set.insert(SomeStruct(46,3.1));
	Set.insert(SomeStruct(-5,6.0));
	for(auto elem: Set)
		cout << elem.a << ' ' << elem.c << endl;
	return 0;
}