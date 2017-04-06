
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "fileutil.h"

int main(int argc, char **argv){


  	DIR *dir;


  	dir = opendir(argv[1]);

	// Comprobamos que se pudo abrir el directorio.
  	if (dir == NULL){

		printf("No se puede abrir el directorio especificado.\n");
  		return 1;
	}

	// Numero de archivos y el tamano total de los archivos del directorio,
	// un contador para aceder al arreglo y la posicion de la mitad del arreglo.
    int n = 0, tamanoTotal = 0, contador = 0, mitad = 0;

    // Arreglo de cadena de caracteres donde se guardan los nombres de los archivos.
	char **arreglo = listarArchivos(dir, &n,argv[1]);

	// Asignamos a la variable el valor de la mitad del arreglo.
	mitad = ((n / 2) + 1);


	int canal[2];


	pipe(canal);
	int pid = fork();
	// Creacion de proceso hijo.
	if(pid){

		// Total de bytes contados por el proceso hijo.
		int tamanoTotalH = 0;
		close(canal[1]);

		// Calcular el tamaño en bytes de cada archivo encontrado.
		while(mitad--){

			tamanoTotal += filesize(arreglo[contador]);
			contador++;
		}

		// Esperarndo el total de bytes contados por el hijo.
		read(canal[0], &tamanoTotalH, sizeof(tamanoTotalH));
		printf("Estudiante_1: 201529176\nEstudiante_2: 201529177\nTotal archivos: %i\nTotal bytes : %i\n",n,(tamanoTotal + tamanoTotalH));
	}

	else {

		// Reasigna los valores para el proceso hijo.
		close(canal[0]);
		contador = mitad ;
		mitad = (n - mitad );

		// Calcular el tamaño en bytes de cada archivo encontrado.
		while(mitad--){

			tamanoTotal += filesize(arreglo[contador]);
			contador++;
		}

		// Envia el total de bytes contados al proceso padre.
		write(canal[1], &tamanoTotal, sizeof(tamanoTotal));
	}

  	return 0;
}
