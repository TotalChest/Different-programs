#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){
    printf("Выберите операцию (цыфру):\n1. Помощь по программе\n2. Сложение матриц\n3. Умножение матрицы на число\n4. Умножение матриц\n5. Оределитедь матрицы\n");
    char nom=getchar();
    switch (nom){
		case '1':
			if((fp=fopen("helpfile","r"))==NULL){
				printf("Файл с помощью отсутствует.\n");
				return 0;
			}
			while(!feof(fp)){
				if (fgets(s,10,fp))
					printf("%s", s);
			}
			fclose(fp);
		    break;
        case '2':
            printf("Введите размерность первой матрицы (m n):\n");
			scanf("%d %d",&m,&n);
			if ((m<=0)||(n<=0)){
				printf("Неверная размерность.\n");
				return 1;
			}
			m1=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m1[i]=(double*)malloc(n*sizeof(double));
			inputm(m,n,m1);
			printf("Введенная матрица:\n");
            outputm(m,n,m1);
			printf("Введите размерность второй матрицы (m n):\n");
			scanf("%d %d",&m0,&n0);
			if ((m0<=0)||(n0<=0)){
				printf("Неверная размерность.\n");
				return 1;
			}
			m2=(double**)malloc(m0*sizeof(double*));
			for (i=0;i<m0;i++)
				m2[i]=(double*)malloc(n0*sizeof(double));
			inputm(m0,n0,m2);
			printf("Введенная матрица:\n");
			outputm(m0,n0,m2); 
			m3=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m3[i]=(double*)malloc(n*sizeof(double));
            summ(m,n,m1,m0,n0,m2,m3);
			printf("Сумма матриц:\n");
            outputm(m,n,m3);
            for (i=0;i<n;i++){
				free(m1[i]);
				free(m2[i]);
				free(m3[i]);
			}
			free(m1);
			free(m2);
			free(m3);
            break;
        case '3':
            printf("Введите размерность матрицы (m n):\n");
            scanf("%d %d",&m,&n);
            if ((m<=0)||(n<=0)){
                printf("Неверная размерность.\n");
                return 1;
            }
			m1=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m1[i]=(double*)malloc(n*sizeof(double));
            inputm(m,n,m1);
            printf("Введенная матрица:\n");
            outputm(m,n,m1);
            printf("Введите число:\n");
            double c1;
            scanf("%lf", &c1);
			m2=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m2[i]=(double*)malloc(n*sizeof(double));
            umnch(m,n,m1,m2,c1);
            printf("Матрица умноженная на %4.2f:\n",c1);
            outputm(m,n,m2);
            for (i=0;i<n;i++){
				free(m1[i]);
				free(m2[i]);
			}
			free(m1);
			free(m2);
            break;
        case '4':
            printf("Введите размерность первой матрицы (m n):\n");
            scanf("%d %d",&m,&n);
            if ((m<=0)||(n<=0)){
                printf("Неверная размерность.\n");
                return 1;
            }
			m1=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m1[i]=(double*)malloc(n*sizeof(double));
            inputm(m,n,m1);
            printf("Введенная матрица:\n");
            outputm(m,n,m1);  
            printf("Введите размерность второй матрицы (m n):\n");
            scanf("%d %d",&m0,&n0);
            if ((m0<=0)||(n0<=0)){
                printf("Неверная размерность.\n");
                return 1;
            }
            m2=NULL;
			m2=(double**)malloc(m0*sizeof(double*));
			for (i=0;i<m0;i++)
				m2[i]=(double*)malloc(n0*sizeof(double));
            inputm(m0,n0,m2);
            printf("Введенная матрица:\n");
            outputm(m0,n0,m2);
			m3=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m3[i]=(double*)malloc(n0*sizeof(double));
            umnm(m,n,m1,m0,n0,m2,m3);
            printf("Произвеление матрица:\n");
            outputm(m,n0,m3);
            for (i=0;i<n;i++)
				free(m1[i]);
			for (i=0;i<n0;i++){
				free(m2[i]);
				free(m3[i]);
			}
			free(m1);
			free(m2);
			free(m3);
            break;
        case '5':
            printf("Введите размерность матрицы (m n):\n");
            scanf("%d %d",&m,&n);
            if ((m<=0)||(n<=0)){
                printf("Неверная размерность.\n");
                return 1;
            }
            if (m!=n){
                printf("Невозможно посчитать определитель не квадратной матрицы.\n");
                return 1;
            }
			m1=(double**)malloc(m*sizeof(double*));
			for (i=0;i<m;i++)
				m1[i]=(double*)malloc(m*sizeof(double));
            inputm(m,m,m1);
            printf("Введенная матрица:\n");
            outputm(m,m,m1);
            double c2;
            c2 = detm(m,m1);
            printf("Определитель матрицы: %-6.3f\n",c2);
            for (i=0;i<n;i++)
				free(m1[i]);
			free(m1);
            break;
        default:
            printf("Некорректный номер операции.\n");
            return 1;
            break;
    }
    return 0;
}
