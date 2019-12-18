#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>


int main(void){
	
	key_t key=ftok("abc",'s');
	int semid=semget(key,4,0666| IPC_CREAT);
	
	semctl(semid,0,SETVAL, (int) 0);
	semctl(semid,1,SETVAL, (int) 0);
	semctl(semid,2,SETVAL, (int) 0);
	semctl(semid,3,SETVAL, (int) 0);
	
	while(1){
		printf("СКЛАД:\n");
		printf("A  %d\n",semctl(semid,0,GETVAL, (int) 0));
		printf("B  %d\n",semctl(semid,1,GETVAL, (int) 0));
		printf("C  %d\n",semctl(semid,2,GETVAL, (int) 0));
		printf("M  %d\n",semctl(semid,3,GETVAL, (int) 0));
		
		printf("\033[2J");
		printf("\033[0;0f");
		sleep(1);
		
	}
		
	return 0;
}
