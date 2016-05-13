//Benchmark realizado para la asignatura de ISE, la idea es probar que sistema de archivos es mas rapido para realizar tareas en disco en diferentes SO.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void copiarFichero(FILE *fich1, FILE *fich2)
{
   volatile char aux;
  //Situamos el cursor al inicio para empezar a copiar
  fseek(fich1,SEEK_SET,0);
  while (!feof(fich1))
  {
    aux=getc(fich1);
    putc(aux ,fich2);
  }
}

int main(int args, char* argv[])
{

  printf("Comienza Prueba\n");
  printf("CentOS media 20 minutos, Ubuntu 10 minutos\n");
  FILE * fich1;
  FILE * fich2;
  FILE * resultados;
  volatile char nombre[20]="destino.txt";
//  char aux;
  clock_t t_inicial, t_final;
  volatile double seg;
  volatile int i=0;
  volatile int vuelta=0;
  //Creamos un fichero de de gran tamaño
  fich1=fopen("origen.txt","w+");
  resultados=fopen("Resultado.txt","a");
  printf("\nCreando un fichero grande para realizar la prueba\n");
  while(i<1000000000)
  {
    putc('a',fich1);
    i++;
  }
  printf("\nFichero grande creado\n");
  printf("\nVa a comenzar la prueba de rendimiento");

  while (vuelta<15)
  {
    fich2=fopen("destino.txt","w");
    printf("\nVuelta %d\n",vuelta);
    t_inicial=clock();
    //Copiamos el primer fichero
    copiarFichero(fich1,fich2);

    //Ahora borramos todos los ficheros
    remove ("destino.txt");
    t_final=clock();
    seg = (double)(t_final - t_inicial) / CLOCKS_PER_SEC;
    printf("%.16g segundos\n", seg);
    //Exportamos los resultados
    fprintf(resultados,"%.16f\n", seg);
    vuelta++;
  }
  remove("origen.txt");
  fclose(fich1);
  fclose(fich2);
  fclose(resultados);
  return 0;
}
