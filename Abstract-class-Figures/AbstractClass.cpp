#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>


struct{
	long mtype;
	char data[256];
	} Message;
	
int msgid;

class GeometryFigure{
	int x,y;
	char* name;
public:
	static int kol;
	GeometryFigure(int a0, int b0,const char* nam="Noname"){x=a0; y=b0; name=new char[strlen(nam)+1]; strcpy(name,nam); ++kol;}
	GeometryFigure(const GeometryFigure & c){x=c.x; y=c.y; name=new char[strlen(c.name)+1]; strcpy(name,c.name); ++kol;}
	
	virtual GeometryFigure & operator =(GeometryFigure & c)=0;
	
	virtual void print()=0;
	
	friend std::ostream & operator<<(std::ostream & out,const GeometryFigure & s);
	
	virtual ~GeometryFigure(){delete [] name; --kol;}
	
	void move(int x1, int y1){x=x1;y=y1;Message.mtype=3;print();}
	virtual void change(int a,int b)=0;
	
	void setx(int x0){x=x0;}
	void sety(int y0){y=y0;}
	int getx()const{return x;}
	int gety()const{return y;}
	void setn(const char* n0){delete [] name; name=new char[strlen(n0)+1]; strcpy(name,n0);}
	char* getn()const{return name;}
};

int GeometryFigure::kol=0;
std::ostream & operator<<(std::ostream & out,const GeometryFigure & s){out<<"Фигура \""<<s.name<<"\". Координаты: "<<s.x<<","<<s.y<<"\n"; return out;}

class Ellipse: public GeometryFigure{
	int a,b;
public:
	Ellipse(int a0=1,int b0=1,int x1=0, int y1=0,const char* n="Noname"):GeometryFigure(x1,y1,n) {a=a0;b=b0;
	std::cout<<"Создан Эллипс с осями: "<<a0<<","<<b0<<". Коородинаты центра: ("<<x1<<" , "<<y1<<")."<<"Название: "<<n<<std::endl;}
	
	Ellipse(const Ellipse & c):GeometryFigure(c.getx(),c.gety(),c.getn()){a=c.a;b=c.b;}
	
	virtual void change(int a0, int b0){a=a0;b=b0;Message.mtype=4;print();}
	
	virtual GeometryFigure & operator =(GeometryFigure & c){Ellipse & d = dynamic_cast<Ellipse&>(c); a=d.a;b=d.b;setx(d.getx());sety(d.gety());setn(d.getn());return *this;}
	
	virtual void print(){
		sprintf(Message.data,"%s %d %d %d %d",getn(),getx(),gety(),a,b);
		msgsnd(msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1,0);
		}
	
};

class Rectangle: public GeometryFigure{
	int h,w;
public:
	Rectangle(int a=1, int b=1,int x1=0,int y1=0,const char* n="Noname"):GeometryFigure(x1,y1,n){h=a; w=b;
		std::cout<<"Создан ПРЯМОУГОЛЬНИК со сторонами: "<<a<<" и "<<b<<". Коородинаты центра: ("<<x1<<" , "<<y1<<")."<<"Название: "<<n<<std::endl;}
		
	Rectangle(const Rectangle & c):GeometryFigure(c.getx(),c.gety(),c.getn()){h=c.h;w=c.w;}
	
	virtual void change(int a,int b){h=a;w=b;Message.mtype=5;print();}
	
	virtual GeometryFigure & operator =(GeometryFigure & c){Rectangle & d = dynamic_cast<Rectangle&>(c); h=d.h;w=d.w;setx(d.getx());sety(d.gety());setn(d.getn());return *this;}
	
	virtual void print(){
		sprintf(Message.data,"%s %d %d %d %d",getn(),getx(),gety(),h,w);
		msgsnd(msgid, (struct msgbuf*) (&Message), strlen(Message.data)+1,0);
		}
};

int main(){
	
	key_t key;
	int f,nf,d,r1,r2,cx,cy,k;
	char str[30];
	key=ftok("abc",'r');
	
	msgid=msgget(key,0666);
	
	
	
	GeometryFigure** figures=0;
	
	std::cout<<"\033[1;34mМЕНЮ: Создать - 1 | Удалить - 2 | Изменить - 3 | Выйти - 0\033[0m"<<std::endl;
	scanf("%d",&f);
	while(f!=0){
		
		switch(f){
			case 1: 
				std::cout<<"Режим создания фигуры:\n    1 - Эллипс\n    2 - Прямоугольник\n";
				scanf("%d",&nf);
				switch(nf){
					case 1:
					
						std::cout<<"Введите первую полуось: ";
						std::cin>>r1;
						std::cout<<"Введите вторую полуось: ";
						std::cin>>r2;
						std::cout<<"Введите 'x' центра: ";
						std::cin>>cx;
						std::cout<<"Введите 'y' центра: ";
						std::cin>>cy;
						std::cout<<"Введите название эллипса: ";
						scanf("%s",str);
						
						figures=(GeometryFigure**)realloc(figures,(GeometryFigure::kol+1)*sizeof(GeometryFigure*));
						k=GeometryFigure::kol;
						figures[k]=new Ellipse(r1,r2,cx,cy,str);
						Message.mtype=1;
						figures[k]->print();
						break;
					case 2:
					
						std::cout<<"Введите первую сторону: ";
						std::cin>>r1;
						std::cout<<"Введите вторую сторону: ";
						std::cin>>r2;
						std::cout<<"Введите 'x' центра: ";
						std::cin>>cx;
						std::cout<<"Введите 'y' центра: ";
						std::cin>>cy;
						std::cout<<"Введите название прямоугольника: ";
						scanf("%s",str);
						
						figures=(GeometryFigure**)realloc(figures,(GeometryFigure::kol+1)*sizeof(GeometryFigure*));
						k=GeometryFigure::kol;
						figures[k]=new Rectangle(r1,r2,cx,cy,str);
						Message.mtype=2;
						figures[k]->print();
						break;	
					default:
						std::cout<<"Ошибка кода операции!\n"<<std::endl;
						break;
				}
				break;
			case 2:
				std::cout<<"Режим удаления фигуры: Введите номер фигуры:\n";
				
				for(int i=0;i<GeometryFigure::kol;++i){
					if(strcmp(typeid(*(figures[i])).name(),"7Ellipse"))
						strcpy(str,"Прямоугольник");
					else
						strcpy(str,"Эллипс");
					printf("  %d  -  %s (%s)\n",i+1,figures[i]->getn(),str);
				}
				
				if(GeometryFigure::kol==0){
					printf("Нет фирур!\n");
					break;
				}
				
				scanf("%d",&nf);
				Message.mtype=6;
				figures[nf-1]->print();
				if (nf>GeometryFigure::kol){
					std::cout<<"Ошибка!\n"<<std::endl;
					break;
				}
				
				delete figures[nf-1];
							for(int i=nf-1;i<GeometryFigure::kol;++i)
								figures[i]=figures[i+1];
							figures=(GeometryFigure**)realloc(figures,(GeometryFigure::kol)*sizeof(GeometryFigure*));
				break;
			case 3:
				std::cout<<"Режим изменения фигуры: Введите номер фигуры:\n";
				
				for(int i=0;i<GeometryFigure::kol;++i){
					if(strcmp(typeid(*(figures[i])).name(),"7Ellipse"))
						strcpy(str,"Прямоугольник");
					else
						strcpy(str,"Эллипс");
					printf("  %d  -  %s (%s)\n",i+1,figures[i]->getn(),str);
				}
				
				scanf("%d",&nf);
				if (nf>GeometryFigure::kol){
					std::cout<<"Ошибка!\n"<<std::endl;
					break;
				}
				
				std::cout<<"Выберите действие:\n   1 - Переместить\n   2 - Изменить размер\n";
				std::cin>>d;
						switch(d){
							case 1: 
								int x1,y1;
								std::cout<<"Введите x: ";
								std::cin>>x1;
								std::cout<<"Введите y: ";
								std::cin>>y1;								
								figures[nf-1]->move(x1,y1);
								break;
							case 2:
								int a1,a2;
								std::cout<<"Введите первый рамер: ";
								std::cin>>a1;
								std::cout<<"Введите второй рамер: ";
								std::cin>>a2;
								figures[nf-1]->change(a1,a2);
								break;	
							default:
								std::cout<<"Ошибка кода действия!\n"<<std::endl;
								break;
						}	
				break;
			default:
				std::cout<<"Ошибка кода операции!\n"<<std::endl;
				break;
		}
		system("clear") ;
		std::cout<<"\033[1;34mМЕНЮ: Создать - 1 | Удалить - 2 | Изменить - 3 | Выйти - 0\033[0m"<<std::endl;
		scanf("%d",&f);	
		
	}
	return 0;
}
