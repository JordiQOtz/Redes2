/*
* PROGRAMA DONDE REALIZA N PROCEDIMIENTOS DE LA SERIE FIBONACCI 
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
void fibonacci_algo(int num_hilo,int tope);
void *funcion_hilo(void * parametro);
int *num_top;
int main(int argc, char*argv[])
{
	
	int x;
	pthread_t *hilos;
	int *arreglo;
	num_top=(int*)malloc(sizeof(int)*argc);
	arreglo=(int*)malloc(sizeof(int)*argc);
	hilos=(pthread_t*)malloc(sizeof(pthread_t)*argc);
	if(argc >=2)
	{
      //cant_hilos = atoi(argv[1]);
   	for(x=1;x<argc;x++)
   		num_top[x]=atoi(argv[x]);
   }
   else
   {
      printf("ingresar numeros\n");
    	return 0;
   }
   for(x=1;x<argc;x++)
   	printf("%d\n",num_top[x]);
   for(x=0;x<argc;x++)
	{
	    arreglo[x]=x;
	    pthread_create(&hilos[x],NULL, funcion_hilo,(void*)&arreglo[x]);
	    //direccion de arreglo de identificadores,constante,funcion del hilo,se le asigna numero de hilo por atributo
	  //sleep(1);		
	}
   for(x=0;x<argc;x++)
	{
	    pthread_join(hilos[x],(void**)hilos);
	}
}

void fibonacci_algo(int num_hilo,int tope)
{
   int x,y=0,z=1,acum=0;
	
	for(x=0; acum<tope-2;x++)
	{
		acum=y+z;
		printf("fibonacci_hilo %d resultado %d\n",num_hilo,acum);
		y=z;
		z=acum;
	}
}

void *funcion_hilo(void * parametro)
{
  int variable = *((int*)parametro);
  fibonacci_algo(variable,num_top[variable]);
  pthread_exit(NULL);
}
