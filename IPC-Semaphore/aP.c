#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>


int main(void){
	
	printf("ДЕТАЛИ А\n");
	
	struct sembuf arr[1];
	int c=0;
	
	key_t key=ftok("abc",'s');
	int semid=semget(key,4,0666| IPC_CREAT);
	
	arr[0].sem_num=0;
	arr[0].sem_flg=0;
	
	while(1){
		
		arr[0].sem_op=1;
		semop(semid,arr,1);
		printf("\r%d",++c);
		fflush(stdout);
		sleep(2);
		
	}
	
	return 0;
}
