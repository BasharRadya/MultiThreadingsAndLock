#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#define NUM_THREADS 20
static pthread_mutex_t mutex;
static int x=0;
void  threadTest1(void* vargp){
int counter=0;
while(1){
sleep(1);
	pthread_mutex_lock(&mutex);
x++;
	pthread_mutex_unlock(&mutex);
counter++;
if(counter==10){
	pthread_exit(NULL);
}
printf("%d\n",x);

}
}
void  threadTest2(void* vargp){
int counter=0;
while(1){
sleep(1);
	pthread_mutex_lock(&mutex);
x--;
	pthread_mutex_unlock(&mutex);
counter++;
if(counter==10){
	pthread_exit(NULL);
}
printf("%d\n",x);

}
}

int main(){
pthread_mutex_init(&mutex,NULL);
pthread_t all_thread[NUM_THREADS];
printf("before start\n");

for(int i=0;i<NUM_THREADS;i++){
void (*func_pointer)(void *)=(i%2==0) ? threadTest1 : threadTest2;
pthread_create(&all_thread[i],NULL,(void*(*)(void*))func_pointer,NULL);
}
printf("after starting\n");

for(int i=0;i<NUM_THREADS;i++){
pthread_join(all_thread[i],NULL);
}
pthread_mutex_destroy(&mutex);
exit(0);
}
