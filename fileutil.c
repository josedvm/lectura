#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <assert.h>

int filesize(char *filename) {
        // Definicion e inicializacion de variables
        FILE *fp;
        int count = 0;

        // Se abre el archivo y se contara caracter por caracter el numero
        // de bytes del archivo
        fp = fopen(filename,"r");
        if (fp == NULL) {
                perror("filesize - No se pudo abrir archivo\n");
                return -1;
        }
        while (fgetc(fp) != EOF) {
                count++;
        }
        fclose(fp);
        return count;
}
char **listarArchivos(DIR *dir, int* n,char* ruta){
	char **arreglo = (char **)malloc(sizeof(char *));
	int contador = 0;

		// En *entrada habra informacion sobre los archivos en el directorio (dirent son entradas al directorio).
	  	struct dirent *entrada;

	  	// Leeemos los archivos del directorio iterativamente hasta el ultimo.
	  	while((entrada = readdir(dir)) != NULL){

	     	// no tenemos en cuaneta "." y ".."
	      	if ((strcmp(entrada->d_name, ".") != 0) && (strcmp(entrada->d_name, "..") != 0)){

	  			// Comprobamos que sea un archivo valido lo que encontramos, si es asi lo guardamos.
	      		if(entrada->d_type == DT_REG){

					// Redimencionamos el tamaño de memoria asiganado al apuntador "arreglo".
	  				arreglo = (char **)realloc(arreglo, (sizeof(char *) * (contador + 1)));
					// Asignamos la memoria necesaria para almacenar el nombre del archivo.
	            	arreglo[contador] = (char *)malloc(sizeof(entrada->d_name) * sizeof(char));
					// Guardamos el nombre del archivo.
				strcpy(arreglo[contador],ruta);
				strcat(arreglo[contador],"/");
				strcat(arreglo[contador],entrada->d_name);
	                contador++;
	    		}


			}
	    }

	    // Cerramos el directorio.
		closedir (dir);

		// Guardamos la cantidad de archivos encontrados.
	    *n = contador;

	    return arreglo;
}
/* Devuelve "true" si "path" es un archivo regular */

