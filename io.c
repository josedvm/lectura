
#include "fileutil.h"


int main(int argc, char **argv)
{
	int i = 0;
	int j = 0;
	int totalBytes = 0;


  DIR *dir;

    	if(argc != 2){

      	printf("Has olvidado introducir la ruta del directorio.\n");
      	return 1;
      }

  dir = opendir(argv[1]);
char** s = listarArchivos(dir,&i,argv[1]);

for(j = 0; j < i; j++){
	 totalBytes += filesize(s[j]);

}
printf("Estudiante_1: 201529176\nEstudiante_2: 201529177\nTotal archivos: %i\nTotal bytes : %i\n",i,totalBytes);
}

