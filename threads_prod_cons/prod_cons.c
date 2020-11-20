#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/shm.h>
#include<sys/ipc.h>

typedef struct{
    int fila;
    int ult_fila;
}Datos;

void *thread_function(void *arg){

    return NULL;
}

int main(int argc,char *argv[]){
    int i,j,each,aux;
    int num_threads;
    pthread_t *threads;
    Datos *datos;
    sem_t *sem_prod1;
    //srand(time(NULL));

    //VERIFICAR NÚMERO DE ARGUMENTOS
    if(argc==2){
        num_threads=2*atoi(argv[1]);
        threads=(pthread_t*)malloc(sizeof(pthread_t)*num_threads);
        datos=(Datos*)malloc(sizeof(Datos)*num_threads);
    }
    else{
        printf("Debe añadir el número de tuplas productor-consumidor como argumento.");
        return 0;
    }

    //COMPROBAR SI SE CREARON CORRECTAMENTE LOS HILOS
    if(threads==NULL){
        printf("\nNo se pudo modificar la memoria dinámicamente.");
        return 1;
    }

    //FILAS A TRABAJAR POR CADA HILO
    aux=0;

    //CREACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        pthread_create(&threads[i],NULL,thread_function,&datos[i]);
        //printf("\n\t\tHilo #%d creado.",i);
    }

    //ESPERA TERMINACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        pthread_join(threads[i],NULL);
    }

    //ELIMINA LOS SEMÁFOROS

    //LIBERA MEMORIA DINÁMICA
    free(threads);
    return 0;
}