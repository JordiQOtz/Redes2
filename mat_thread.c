#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define M 3
#define K 3
#define N 3


void *thread_function(void *arg){
    int v=*(int*)arg;
    printf("\nThread #%d: ¡Hola, mundo!",*(int *)arg);
    return NULL;
}

int main(int argc,char *argv[]){
    int i,j,num_threads=atoi(argv[1]);
    pthread_t *threads;
    int A[M][K],B[K][N],C[M][N];
    srand(time(NULL));
    printf("\n\nMatriz A\n");

    //LLENADO DE MATRIZ A
    for (i = 0; i < M; i++){
        for(j=0;j<K;j++){
            A[i][j]=rand()%10;
            printf("  %d",A[i][j]);
        }
        printf("\n");
    }
    printf("\n\nMatriz B\n");
    //LLENADO DE MATRIZ B
    for (i = 0; i < K; i++){
        for(j=0;j<N;j++){
            B[i][j]=rand()%10;
            printf("  %d",B[i][j]);
        }
        printf("\n");
    }
    

    if(argc==2){
        threads=(pthread_t*)malloc(sizeof(pthread_t)*num_threads);
    }
    else{
        printf("\nIngresa los argumentos correctamente");
        return 0;
    }

    if(threads==NULL){
        printf("\nNo se pudo modificar la memoria dinámicamente.");
        return 1;
    }

    for(i=0;i<num_threads;i++){
        pthread_create(&threads[i],NULL,thread_function,&i);
        printf("\n\t\tHilo #%d creado.",i);
    }
    for(i=0;i<num_threads;i++){
        pthread_join(threads[i],NULL);
    }
    free(threads);
    return 0;
}