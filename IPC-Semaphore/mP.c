#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>


int main(void){
	
	printf("МОДУЛЬ А+В\n");
	struct sembuf arr[3];
	int c=0;
	
	key_t key=ftok("abc",'s');
	int semid=semget(key,4,0666| IPC_CREAT);
	
	arr[0].sem_num=0;
	arr[1].sem_num=1;
	arr[2].sem_num=3;
	
	arr[0].sem_flg=0;
	arr[1].sem_flg=0;
	arr[2].sem_flg=0;
	
	while(1){
		
		arr[0].sem_op=-1;
		arr[1].sem_op=-1;
		arr[2].sem_op=1;
		
		semop(semid,arr,3);
		
		printf("\r%d",++c);
		fflush(stdout);
		sleep(1);
		
	}
		
	return 0;
}
