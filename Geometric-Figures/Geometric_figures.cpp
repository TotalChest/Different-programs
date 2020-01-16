#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

class Geom{
	int x,y,a;
public:
	Geom(int a0, int b0){x=a0;y=b0;a=0;}
	void move(int x1, int y1){x=x1;y=y1;}
	void rot(int a0){a=a0;}
	int retx() const {return x;}
	int rety() const {return y;}
	int reta() const {return a;}
};

class Circle: public Geom{
	int r;
public:
	Circle(int a=1, int x1=0, int y1=0):Geom(x1,y1) {r=a;
	std::cout<<"Создан КРУГ радиуса: "<<a<<". Коородинаты центра: ("<<x1<<" , "<<y1<<")"<<std::endl;
	} 
	void change(int a){r=a;}
	int retr() const {return r;}
};

class Rectangle: public Geom{
	int h,w;
public:
	Rectangle(int a=1, int b=1,int x1=0,int y1=0):Geom(x1,y1){h=a; w=b;
		std::cout<<"Создан ПРЯМОУГОЛЬНИК со сторонами: "<<a<<" и "<<b<<". Коородинаты центра: ("<<x1<<" , "<<y1<<")"<<std::endl;
		}
	void change(int a,int b){h=a;w=b;}
	int reth() const {return h;}
	int retw() const {return w;}
};

class Square: public Geom{
	int h;
public:
	Square(int a=1, int x1=0,int y1=0):Geom(x1,y1) {h=a;
		std::cout<<"Создан КВАДРАТ со стороной: "<<a<<". Коородинаты центра: ("<<x1<<" , "<<y1<<")"<<std::endl;
		}
	void change(int a){h=a;}
	int reth() const {return h;}
};

int main(){
	
	int f=1,ci=0,ri=0,si=0,nf,n,d;
	
	
	Circle** cir=0;
	Rectangle** rec=0;
	Square** squ=0;
	
	
	std::cout<<"\033[1;34mМЕНЮ: Создать - 1 | Удалить - 2 | Изменить - 3 | Нарисовать - 4 | Выйти - 0\033[0m"<<std::endl;
	scanf("%d",&f);
	
	while(f!=0){
		
		switch(f){
			case 1: 
				std::cout<<"Режим создания фигуры:\n    1 - Окружность\n    2 - Прямоугольник\n    3 - Квадрат\n";
				scanf("%d",&nf);
				switch(nf){
					case 1:
					
						++ci;
						int rad,cx,cy;
						std::cout<<"Введите радиус: ";
						std::cin>>rad;
						std::cout<<"Введите x: ";
						std::cin>>cx;
						std::cout<<"Введите y: ";
						std::cin>>cy;
						
						cir=(Circle**)realloc(cir,ci*sizeof(Circle*));
						cir[ci-1]=new Circle(rad,cx,cy);
						 
						break;
					case 2:
					
						++ri;
						int ra,rb,rx,ry;
						std::cout<<"Введите первую сторону: ";
						std::cin>>ra;
						std::cout<<"Введите вторую сторону: ";
						std::cin>>rb;
						std::cout<<"Введите x: ";
						std::cin>>rx;
						std::cout<<"Введите y: ";
						std::cin>>ry;
						
						rec=(Rectangle**)realloc(rec,ri*sizeof(Rectangle*));
						rec[ri-1]=new Rectangle(ra,rb,rx,ry);
						 
						break;
					case 3:
					
						++si;
						int sa,sx,sy;
						std::cout<<"Введите сторону: ";
						std::cin>>sa;
						std::cout<<"Введите x: ";
						std::cin>>sx;
						std::cout<<"Введите y: ";
						std::cin>>sy;
						
						squ=(Square**)realloc(squ,si*sizeof(Square*));
						squ[si-1]=new Square(sa,sx,sy);
					
						break;
					default:
						std::cout<<"Ошибка кода операции!\n"<<std::endl;
						break;
				}
				break;
			case 2:
				std::cout<<"Режим удаления фигуры:\n    1 - Окружность\n    2 - Прямоугольник\n    3 - Квадрат\n";
				scanf("%d",&nf);
				switch(nf){
					case 1:
						std::cout<<"Выберите номер окружности: ";
						std::cin>>n;
						if(n>ci)
							printf("Нет такой окружности!\n");
						else{
							delete cir[n-1];
							--ci;
							for(int i=n-1;i<ci;++i)
								cir[i]=cir[i+1];
							cir=(Circle**)realloc(cir,ci*sizeof(Circle*));
						}
						break;
					case 2:
						std::cout<<"Выберите номер прямоугольника: ";
						std::cin>>n;
						if(n>ri)
							printf("Нет такого прямоугольника!\n");
						else{
							delete rec[n-1];
							--ri;
							for(int i=n-1;i<ri;++i)
								rec[i]=rec[i+1];
							rec=(Rectangle**)realloc(rec,ri*sizeof(Rectangle*));
						}
						break;
					case 3:
						std::cout<<"Выберите номер квадрата: ";
						std::cin>>n;
						if(n>si)
							printf("Нет такого квадрата!\n");
						else{
							delete squ[n-1];
							--si;
							for(int i=n-1;i<si;++i)
								squ[i]=squ[i+1];
							squ=(Square**)realloc(squ,si*sizeof(Square*));
						}
						break;
					default:
						std::cout<<"Ошибка кода операции!\n"<<std::endl;
						break;
				}
				break;
			case 3:
				std::cout<<"Режим изменения фигуры:\n    1 - Окружность\n    2 - Прямоугольник\n    3 - Квадрат\n";
				scanf("%d",&nf);
				switch(nf){
					case 1:
						std::cout<<"Выберите номер окружности: ";
						std::cin>>n;
						if(n>ci)
							printf("Нет такой окружности!\n");
						else{
							std::cout<<"Выберите действие:\n  1 - Переместить\n  2 - Повернуть\n  3 - Изменить радиус\n";
							std::cin>>d;
							switch(d){
								case 1: 
									int x1,y1;
									std::cout<<"Введите x: ";
									std::cin>>x1;
									std::cout<<"Введите y: ";
									std::cin>>y1;								
									cir[n-1]->move(x1,y1);
									break;
								case 2:
									int a1;
									std::cout<<"Введите Угол: ";
									std::cin>>a1;
									cir[n-1]->rot(a1);
									break;
								case 3:
									int r1;
									std::cout<<"Введите Радиус: ";
									std::cin>>r1;
									cir[n-1]->change(r1);
									break;	
								default:
									std::cout<<"Ошибка кода действия!\n"<<std::endl;
									break;
							}	
						}
						break;
					case 2:
						std::cout<<"Выберите номер прямоугольника: ";
						std::cin>>n;
						if(n>ri)
							printf("Нет такого прямоугольника!\n");
						else{
							std::cout<<"Выберите действие:\n  1 - Переместить\n  2 - Повернуть\n  3 - Изменить размеры\n";
							std::cin>>d;
							switch(d){
								case 1: 
									int x1,y1;
									std::cout<<"Введите x: ";
									std::cin>>x1;
									std::cout<<"Введите y: ";
									std::cin>>y1;								
									rec[n-1]->move(x1,y1);
									break;
								case 2:
									int a1;
									std::cout<<"Введите Угол: ";
									std::cin>>a1;
									rec[n-1]->rot(a1);
									break;
								case 3:
									int h1,w1;
									std::cout<<"Введите первую сторону: ";
									std::cin>>h1;
									std::cout<<"Введите вторую сторону: ";
									std::cin>>w1;
									rec[n-1]->change(h1,w1);
									break;
								default:
									std::cout<<"Ошибка кода действия!\n"<<std::endl;
									break;	
							}	
						}
						break;
					case 3:
						std::cout<<"Выберите номер квадрата: ";
						std::cin>>n;
						if(n>si)
							printf("Нет такого кватрата!\n");
						else{
							std::cout<<"Выберите действие:\n  1 - Переместить\n  2 - Повернуть\n  3 - Изменить сторону\n";
							std::cin>>d;
							switch(d){
								case 1: 
									int x1,y1;
									std::cout<<"Введите x: ";
									std::cin>>x1;
									std::cout<<"Введите y: ";
									std::cin>>y1;								
									squ[n-1]->move(x1,y1);
									break;
								case 2:
									int a1;
									std::cout<<"Введите Угол: ";
									std::cin>>a1;
									squ[n-1]->rot(a1);
									break;
								case 3:
									int h1;
									std::cout<<"Введите сторону: ";
									std::cin>>h1;
									squ[n-1]->change(h1);
									break;
								default:
									std::cout<<"Ошибка кода действия!\n"<<std::endl;
									break;	
							}	
						}
						break;
					default:
						std::cout<<"Ошибка кода операции!\n"<<std::endl;
						break;
				}
				
				break;
			case 4:
			
				char* (a[30][100]);
				
				for (int i=0;i<30;++i)
					for(int j=0;j<100;++j){
						a[i][j]=(char*)malloc(20*sizeof(char));
						if (i==19)
							a[i][j]=(char*)"\033[1;34m-\033[0m";
						else {
							if (j==25)
								a[i][j]=(char*)"\033[1;34m|\033[0m";
							else 
								a[i][j]=(char*)"\033[1;34m \033[0m";
							}
					}
				a[0][25]=(char*)"\033[1;34m^\033[0m";
				a[19][99]=(char*)"\033[1;34m>\033[0m";
						
				for (int i=0;i<ci;++i){
					a[19-(cir[i]->rety())][(cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-(cir[i]->retr())*sin(cir[i]->reta()*(3.14/180))-cir[i]->rety())][(int)round(cir[i]->retr()*cos(cir[i]->reta()*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-((-1)*cir[i]->retr())*sin(cir[i]->reta()*(3.14/180))-cir[i]->rety())][(int)round((-1)*cir[i]->retr()*cos(cir[i]->reta()*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-(cir[i]->retr())*cos(cir[i]->reta()*(3.14/180))-cir[i]->rety())][(int)round((-1)*cir[i]->retr()*sin(cir[i]->reta()*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-((-1)*cir[i]->retr())*cos(cir[i]->reta()*(3.14/180))-cir[i]->rety())][(int)round(cir[i]->retr()*sin(cir[i]->reta()*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-(cir[i]->retr())*sin((cir[i]->reta()+45)*(3.14/180))-cir[i]->rety())][(int)round(cir[i]->retr()*cos((cir[i]->reta()+45)*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-((-1)*cir[i]->retr())*sin((cir[i]->reta()+45)*(3.14/180))-cir[i]->rety())][(int)round((-1)*cir[i]->retr()*cos((cir[i]->reta()+45)*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-(cir[i]->retr())*cos((cir[i]->reta()+45)*(3.14/180))-cir[i]->rety())][(int)round((-1)*cir[i]->retr()*sin((cir[i]->reta()+45)*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
					a[(int)round(19-((-1)*cir[i]->retr())*cos((cir[i]->reta()+45)*(3.14/180))-cir[i]->rety())][(int)round(cir[i]->retr()*sin((cir[i]->reta()+45)*(3.14/180))+cir[i]->retx())+25]=(char*)"\033[0;33mo\033[0m";
				}
						
				for (int i=0;i<ri;++i){
					a[19-(rec[i]->rety())][(rec[i]->retx())+25]=(char*)"\033[0;32m#\033[0m";
					a[(int)round(19-(rec[i]->reth())*sin(rec[i]->reta()*(3.14/180))-rec[i]->rety())][(int)round(rec[i]->reth()*cos(rec[i]->reta()*(3.14/180))+rec[i]->retx())+25]=(char*)"\033[0;32m#\033[0m";
					a[(int)round(19-(rec[i]->retw())*cos(rec[i]->reta()*(3.14/180))-rec[i]->rety())][(int)round((-1)*rec[i]->retw()*sin(rec[i]->reta()*(3.14/180))+rec[i]->retx())+25]=(char*)"\033[0;32m#\033[0m";
					a[(int)round(19-(rec[i]->reth())*sin(rec[i]->reta()*(3.14/180))-(rec[i]->retw()*cos(rec[i]->reta()*(3.14/180)))-rec[i]->rety())][(int)round(rec[i]->reth()*cos(rec[i]->reta()*(3.14/180))-(rec[i]->retw()*sin(rec[i]->reta()*(3.14/180)))+rec[i]->retx())+25]=(char*)"\033[0;32m#\033[0m";	
				}
				
				for (int i=0;i<si;++i){
					a[19-(squ[i]->rety())][(squ[i]->retx())+25]=(char*)"\033[1;31m#\033[0m";
					a[(int)round(19-(squ[i]->reth())*sin(squ[i]->reta()*(3.14/180))-squ[i]->rety())][(int)round(squ[i]->reth()*cos(squ[i]->reta()*(3.14/180))+squ[i]->retx())+25]=(char*)"\033[1;31m#\033[0m";
					a[(int)round(19-(squ[i]->reth())*cos(squ[i]->reta()*(3.14/180))-squ[i]->rety())][(int)round((-1)*squ[i]->reth()*sin(squ[i]->reta()*(3.14/180))+squ[i]->retx())+25]=(char*)"\033[1;31m#\033[0m";
					a[(int)round(19-(squ[i]->reth())*sin(squ[i]->reta()*(3.14/180))-(squ[i]->reth()*cos(squ[i]->reta()*(3.14/180)))-squ[i]->rety())][(int)round(squ[i]->reth()*cos(squ[i]->reta()*(3.14/180))-(squ[i]->reth()*sin(squ[i]->reta()*(3.14/180)))+squ[i]->retx())+25]=(char*)"\033[1;31m#\033[0m";
				}
				
				for (int i=0;i<30;++i){
					for(int j=0;j<100;++j)
						printf("%s",a[i][j]);
					printf("\n");
				}
				
				break;
			default:
				std::cout<<"Ошибка кода операции!\n"<<std::endl;
				break;
		}
				
		std::cout<<"\033[1;34mМЕНЮ: Создать - 1 | Удалить - 2 |Изменить - 3 | Нарисовать - 4 | Выйти - 0\033[0m"<<std::endl;
		scanf("%d",&f);	
		
	}
	
	return 0;
}
