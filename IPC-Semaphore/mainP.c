#include <stdio.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>


int main(void){
	
	printf("ПРОИЗВОДСТВО %d\n",getpid());
	struct sembuf arr[2];
	int a=0;
	key_t key=ftok("abc",'s');
	int semid=semget(key,4,0666| IPC_CREAT);
	
	arr[0].sem_num=2;
	arr[1].sem_num=3;
	
	arr[0].sem_flg=0;
	arr[1].sem_flg=0;
	
	while(1){
		
		arr[0].sem_op=-1;
		arr[1].sem_op=-1;
		semop(semid,arr,2);
		
		printf("Произведенно: %d дет.\n",++a);
		sleep(1);
	}
	
	return 0;
}
