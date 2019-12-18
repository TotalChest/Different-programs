#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstring>


const double E=0.2;

struct{
	long mtype;
	char data[256];
	} Message;
	
struct Figure{
	int type;
	char name[20];
	int x;
	int y;
	int a;
	int b;
	};
	
struct list{
	Figure* f;
	list* next;
};

int main(){
	key_t key;
	int msgid;
	key=ftok("abc",'r');

	msgid=msgget(key,0666|IPC_CREAT);
	
	list* L=0,*q=0,*p=0;
	char * pch=0;
	
	char* (a[35][130]);
				
	for (int i=0;i<35;++i)
		for(int j=0;j<130;++j){
			if (i==25)
				a[i][j]=(char*)"\033[1;34m-\033[0m";
			else {
				if (j==40)
					a[i][j]=(char*)"\033[1;34m|\033[0m";
				else 
					a[i][j]=(char*)"\033[1;34m \033[0m";
			}
		}
	a[0][40]=(char*)"\033[1;34m^\033[0m";
	a[25][129]=(char*)"\033[1;34m>\033[0m";
	a[25][40]=(char*)"\033[1;34m+\033[0m";
	
	for (int i=0;i<35;++i){
		for(int j=0;j<130;++j)
			printf("%s",a[i][j]);
		printf("\n");
	}
	
	while(1){

	msgrcv(msgid,(struct msgbuf*) (&Message), 256,0,0);	
	switch(Message.mtype){
		case 1:
		
			q=new list;
			q->next=L;
			L=q;
			
			q->f=new Figure;
			q->f->type=1;
			pch = strtok (Message.data," ");
			strcpy(q->f->name,pch);
			pch = strtok (NULL, " ");
			q->f->x=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->y=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->a=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->b=atoi(pch);
		
			break;
		
		case 2:
		
			q=new list;
			q->next=L;
			L=q;
			
			q->f=new Figure;
			q->f->type=2;
			
			pch = strtok (Message.data," ");
			strcpy(q->f->name,pch);
			pch = strtok (NULL, " ");
			q->f->x=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->y=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->a=atoi(pch);
			pch = strtok (NULL, " ");
			q->f->b=atoi(pch);
			
			break;
			
		case 3:
			
			pch = strtok (Message.data," ");
			p=L;
			while (p!=0){
				if (!strcmp(p->f->name,pch)){
					pch = strtok (NULL, " ");
					p->f->x=atoi(pch);
					pch = strtok (NULL, " ");
					p->f->y=atoi(pch);
				}
				else
					p=p->next;
			}
		
			break;
			
		case 4:
		case 5:
		
			pch = strtok (Message.data," ");
			p=L;
			while (p!=0){
				if (!strcmp(p->f->name,pch)){
					pch = strtok (NULL, " ");
					pch = strtok (NULL, " ");
					pch = strtok (NULL, " ");
					p->f->a=atoi(pch);
					pch = strtok (NULL, " ");
					p->f->b=atoi(pch);
				}
				else
					p=p->next;
			}
		
			break;
			
		case 6:
			
			pch = strtok (Message.data," ");
			p=L;
			q=L;
			if (!strcmp(p->f->name,pch)){
				delete p->f;
				L=p->next;
				delete p;
				p=0;
			} 
			while (p!=0){
				if (!strcmp(p->f->name,pch)){
					delete p->f;
					q->next=p->next;
					delete p;
					p=0;
				}
				else{
					q=p;
					p=p->next;
				}
			}
			break;
	}
	
	for (int i=0;i<35;++i)
		for(int j=0;j<130;++j){
			if (i==25)
				a[i][j]=(char*)"\033[1;34m-\033[0m";
			else {
				if (j==40)
					a[i][j]=(char*)"\033[1;34m|\033[0m";
				else 
					a[i][j]=(char*)"\033[1;34m \033[0m";
			}
		}
	a[0][40]=(char*)"\033[1;34m^\033[0m";
	a[25][129]=(char*)"\033[1;34m>\033[0m";
	a[25][40]=(char*)"\033[1;34m+\033[0m";
	
	p=L;
	while(p!=0){
		if(p->f->type==1){
			for(int i=(-1)*p->f->b;i<=p->f->b;++i)
				for(int j=(-1)*p->f->a;j<=p->f->a;++j)
					if((((float)i*i)/(p->f->b*p->f->b)+((float)j*j)/(p->f->a*p->f->a))<1+E&&(((float)i*i)/(p->f->b*p->f->b)+((float)j*j)/(p->f->a*p->f->a))>1-E)
						a[25-i-p->f->y][40+j+p->f->x]=(char*)"\033[1;33mo\033[0m";
		}
		else{
			for(int i=0;i<p->f->b;++i)
				for(int j=0;j<p->f->a;++j)
					if((i==0)||(i==p->f->b-1)||(j==0)||(j==p->f->a-1))
						a[25-i-p->f->y][40+j+p->f->x]=(char*)"\033[1;36mo\033[0m";
		}
		p=p->next;
	}
	
	system("clear") ;
	
	for (int i=0;i<35;++i){
		for(int j=0;j<130;++j)
			printf("%s",a[i][j]);
		printf("\n");
	}
	sleep(1);
	
	}
	
	return 0;
}
