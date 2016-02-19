#ifndef unistdBiblio
#define unistdBiblio
#include <unistd.h>		/* fork, pipe, primitivas IO(read, write, close,etc) */
#endif

#ifndef stringBiblio
#define stringBiblio
#include <string.h>		/* strstr, strlen, etc */
#endif

#ifndef stdlibBiblio
#define stdlibBiblio
#include <stdlib.h>		/* malloc, free, rand */
#endif

#ifndef fcntlibBiblio
#define fcntlibBiblio
#include <fcntl.h>		/* manipular descritores ficheiros */
#endif

#include <stdio.h>

#define READ 0
#define WRITE 1
#define STDIN 0
#define STDOUT 1

#include "../lib/readLine.h"

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("FATAL: invalid number of arguments");
    return EXIT_FAILURE;	/*1 */
  } else {
    char linha[1024];
    int tamanhoLido;
    FILE *fp;
    int descritor_ficheiro;
if ( strcmp (argv[1] , "rb") == 0 ){
    fp = fopen(argv[2],"rb");  // r for read, b for binary
}
    else {
    if ( strcmp ( argv[1] , "rt" ) == 0 ) {
    fp = fopen(argv[2],"r");  // r for read, b for binary
} 
else {
    return EXIT_FAILURE;	/*1 */
}
}
descritor_ficheiro = fileno( fp );
while ((tamanhoLido = readln(descritor_ficheiro, linha)) > 0) {	//le o ficheiro temporario
      printf( "%s\n",linha );
      //write(STDOUT, linha, 10 );
    }
    close(descritor_ficheiro);
    return EXIT_SUCCESS;	/*0 */
  }
}

