#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
int filesize(char *filename);
char **listarArchivos(DIR *dir, int* n,char* ruta);

