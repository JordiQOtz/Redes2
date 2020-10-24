#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define M 1500
#define K 1500
#define N 1500

int A[M][K],B[K][N],C[M][N];

typedef struct{
    int fila;
    int ult_fila;
}Datos;

void *thread_function(void *arg){
    Datos *p_str = (Datos*)arg;
    int inicio=p_str->fila,fin=p_str->ult_fila,aux;
    /* printf("\nRango: %d - %d.",inicio,fin);
    printf(" Total: %d.",fin-inicio); */
    for(int i=inicio;i<fin;i++){
        //printf("\n");
        for(int j=0;j<N;j++){
            C[i][j]=0;
            for(int k=0;k<K;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
            //printf("\t%d",C[i][j]);
        }
    }
    return NULL;
}

int main(int argc,char *argv[]){
    int i,j,each,aux;
    int num_threads;
    pthread_t *threads;
    Datos *datos;
    //srand(time(NULL));

    //VERIFICAR NÚMERO DE ARGUMENTOS
    if(argc==2){
        num_threads=atoi(argv[1]);
        threads=(pthread_t*)malloc(sizeof(pthread_t)*num_threads);
        datos=(Datos*)malloc(sizeof(Datos)*num_threads);
    }
    else{
        printf("Debe ingresar el número de hilos.");
        return 0;
    }

    //VERIFICA SI HAY MÁS HILOS QUE FILAS
    if(num_threads>M) return 1;

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

    //FILAS A TRABAJAR POR CADA HILO
    aux=0;
    each=(M/num_threads);
    for(i=0;i<num_threads;i++){
        datos[i].fila=aux;
        aux+=each;
        if(i<(M%num_threads))
            aux++;
        datos[i].ult_fila=aux;
    }

    //CREACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        pthread_create(&threads[i],NULL,thread_function,&datos[i]);
        //printf("\n\t\tHilo #%d creado.",i);
    }

    //ESPERA TERMINACIÓN DE HILOS
    for(i=0;i<num_threads;i++){
        pthread_join(threads[i],NULL);
    }

    //IMPRIME MATRIZ RESULTANTE
    printf("\n\nMatriz R\n");
    for (i = 0; i < M; i++){
        for(j=0;j<N;j++){
            printf("\t%d",C[i][j]);
        }
        printf("\n");
    }

    //LIBERA MEMORIA DINÁMICA
    free(threads);
    return 0;
}