#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//paso 3: creacion de la funcion del hilo
void * fibonacci(void * arg){
  int n = *((int*)arg);
  int a=0,b=1,c=0;
  while(c<=n){
      c=a+b;
      printf("\n%d",c);
      a=b;
      b=c;
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int value[argc-1];
    pthread_t thread[argc-1];

    //paso 0 : recepcion de numero de hilos a crear
    if(argc > 1){
        for(int i=1;i<argc-1;i++){
            value[i]=atoi(argv[i]);
        }
    }else{
        printf("ingresar el numero de hilos\n");
    }
   

    //paso 1: creacion de los hilos 
    for(int i=0; i<argc-2; i++){
        pthread_create(&thread[i], NULL, fibonacci, (void*) &value[i]);
    }

    //paso 2: el padre espera a que los hijos terminen su ejecucion 
    for(int i=0; i< argc-2; i++){
        pthread_join(thread[i], NULL);
    }
    exit(0);
}

//gcc acr.c -o hilos -lpthread
