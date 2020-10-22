#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define M 3
#define K 3
#define N 3

int A[M][K],B[K][N],C[M][N];

typedef struct{
    int fila;
    int ult_fila;
}Datos;

void *thread_function(void *arg){
    Datos *p_str = (Datos*)arg;
    printf("\nRango: %d - %d.",p_str->fila,p_str->ult_fila);
    //printf("\nThread #%d: ¡Hola, mundo!",*(int *)arg);
    return NULL;
}

int main(int argc,char *argv[]){
    int i,j;
    int num_threads;
    pthread_t *threads;
    Datos *datos;
    srand(time(NULL));

    //VERIFICAR NÚMERO DE ARGUMENTOS
    if(argc==2){
        num_threads=atoi(argv[1]);
        threads=(pthread_t*)malloc(sizeof(pthread_t)*num_threads);
        datos=(Datos*)malloc(sizeof(Datos)*num_threads);
    }
    else{
        printf("Debe ingresar el número de hillos.");
        return 0;
    }

    //COMPROBAR SI SE CREARON CORRECTAMENTE LOS HILOS
    if(threads==NULL){
        printf("\nNo se pudo modificar la memoria dinámicamente.");
        return 1;
    }

    //LLENADO DE MATRIZ A
    printf("\n\nMatriz A\n");
    for (i = 0; i < M; i++){
        for(j=0;j<K;j++){
            A[i][j]=rand()%10;
            printf("  %d",A[i][j]);
        }
        printf("\n");
    }
    //LLENADO DE MATRIZ B
    printf("\n\nMatriz B\n");
    for (i = 0; i < K; i++){
        for(j=0;j<N;j++){
            B[i][j]=rand()%10;
            printf("  %d",B[i][j]);
        }
        printf("\n");
    }

    //CREACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        datos[i].fila=i;
        datos[i].ult_fila=i+1;
        pthread_create(&threads[i],NULL,thread_function,&datos[i]);
        //printf("\n\t\tHilo #%d creado.",i);
    }
    //ESPERA TERMINACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        pthread_join(threads[i],NULL);
    }
    //LIBERA MEMORIA DINÁMICA
    free(threads);
    return 0;
}