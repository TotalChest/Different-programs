#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>


class Mystr{
	char *p;
	int len;
	static int objects;
	static int size;
public:
	Mystr(){
		p = new char[1];
		*p = '\0';
		len = 0;
		++objects;
	}
	
	Mystr(const Mystr & s){
		p = new char[s.len + 1];
		strcpy(p, s.p);
		++objects;
		size += s.len;
		len = s.len;
	}
	
	Mystr(int a){
		char h[20];
		len = sprintf(h, "%d", a);
		p = new char[len + 1];
		strcpy(p, h);
		++objects;
		size += len;
	}
	
	Mystr(const char* a){
		p = new char[strlen(a) + 1];
		strcpy(p, a);
		++objects;
		size += strlen(a);
		len = strlen(a);
	}
	
	Mystr(char c, int n){
		p = new char[n + 1];
		for(int i = 0; i < n; ++i)
			p[i] = c;
		p[n] = '\0';
		len = n;
		++objects;
		size += n;
	}
	
	~Mystr(){
		delete [] p;
		--objects;
		size-=len;
		std::cout << "Left " << objects << " objects of type Mystr (size = " << size << ")\n";
	}
	
	operator int(){
		return atoi(p);
	}
	
	Mystr & operator=(const Mystr & a){
		if(p == a.p)
			return*this;
		delete [] p;
		p = new char[a.len + 1];
		strcpy(p, a.p);
		size = size - len + a.len;
		len = a.len;
		return *this;
	}
	
	Mystr operator+(const Mystr & a){
		Mystr h;
		delete [] h.p;
		h.p = new char[len + a.len + 1];
		strcpy(h.p, p);
		char* k = h.p + len;
		strcpy(k, a.p);
		h.len = len+a.len;
		return h;
	}
	
	Mystr operator+=(const Mystr & a){
		Mystr h(p);
		delete [] p;
		p=new char[len + a.len + 1];
		strcpy(p, h.p);
		char* k = p + len;
		strcpy(k, a.p);
		len = len + a.len;
		size += a.len; 
		return *this;
	}
	
	bool operator==(const Mystr & s){
		if (strcmp(p,s.p)==0)
			return true;
		return false;
	}
	
	char & operator[](int n){
		if (n < len) 
			return *(p + n); 
		char* a;
		a = new char('\0');
		return *a;
	}
	
	friend std::ostream & operator<<(std::ostream & out, const Mystr & s);
	friend std::istream & operator>>(std::istream & in, Mystr & s);
	friend bool operator>(const Mystr & s1, const Mystr & s2);
	friend bool operator<(const Mystr & s1, const Mystr & s2);
};

int Mystr::objects = 0;
int Mystr::size = 0;

bool operator>(const Mystr & s1, const Mystr & s2) {
	if(strcmp(s1.p, s2.p) > 0) 
		return true;
	return false;
}

bool operator<(const Mystr & s1, const Mystr & s2) {
	if(strcmp(s1.p, s2.p) < 0)
		return true;
	return false;
}

std::ostream & operator<<(std::ostream & out, const Mystr & s){
	out << s.p;
	return out;
}

std::istream & operator>>(std::istream & in, Mystr & s) {
	Mystr::size -= s.len;
	std::string m;
	std::getline(in, m);
	delete [] s.p;
	s.p = new char[m.length() + 1];
	s.len = m.length();
	for (int i = 0; i < s.len + 1; ++i)
		s.p[i] = m[i];
	Mystr::size += s.len;
	return in;
}
