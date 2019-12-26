#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void inputm(int m, int n, double **mas){
	printf("Введите матрицу построчно:\n");
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%lf",&(mas[i][j]));
        }
    }
}

void outputm(int m,int n,double** mas){
    int i,j;
    for(j=0;j<n;j++)
		printf("----------");
	printf("-\n");
    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            printf("| %7.3f ", mas[i][j]);
        printf("|\n");
    }
    for(j=0;j<n;j++)
		printf("----------");
	printf("-\n");
}

void summ(int m,int n, double** m1,int m0,int n0,double** m2,double** m3){
    if ((m != m0)||(n !=n0)){
        printf("Нельзя складывать матрицы разных размерностей!\n");
        exit(1);
    }
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++)
            m3[i][j]=m1[i][j]+m2[i][j];
    } 
      
}

void umnch(int m, int n, double** m1,double** m2,double c){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            m2[i][j]=m1[i][j]*c;
        }
    }   
}
void umnm(int m,int n,double** m1,int m0,int n0,double** m2,double** m3){
	if (n != m0){
		printf("Невозможно умножать матрицы данной размерности.\n");
        exit(1);
	}
    int i,j,k;
    for(i=0;i<m;i++){
        for(j=0;j<n0;j++){
            m3[i][j]=0;
            for (k=0;k<n;k++){
                m3[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }   
}

double detm(int m,double** m1){
    double c=1,t,k;
    int i=0,j,b,h;
    for (i=0;i<m;i++){	
		h=i;
		while ((h<m)&&(m1[h][i] == 0))
			h++;
		if (h == m)
			return 0;
		if (h!=i){
			for (j=0;j<m;j++){
				t=m1[h][j];
				m1[h][j]=m1[i][j];
				m1[i][j]=t;
			}
		c=(-1)*c;
		}	
        for (j=i+1;j<m;j++){
            k=(m1[j][i]/m1[i][i]);
            for(b=0;b<m;b++)
				m1[j][b]=m1[j][b]-k*m1[i][b];   
        }
    }
    for (i=0;i<m;i++)
		c*=m1[i][i];
    return c;
}





