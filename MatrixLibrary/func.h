#ifndef fun
#define fun

double **m1, **m2, **m3;
int m,n,m0,n0,i,j;
FILE *fp;
char s[20];

void inputm(int m,int n,double** mas);

void outputm(int m,int n,double** mas);

void summ(int m,int n, double** m1,int m0,int n0,double** m2,double** m3);

void umnch(int m, int n, double ** m1,double** m2,double c);

void umnm(int m,int n,double** m1,int m0,int n0,double** m2,double** m3);

double detm(int m,double** m1);
#endif








