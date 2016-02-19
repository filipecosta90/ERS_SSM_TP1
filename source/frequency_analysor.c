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

#include "../lib/readSSM.h"

int main(int argc, char *argv[])
{
  //setlocale(LC_ALL, "en_US.UTF-8");
  if (argc != 3) {
    perror("FATAL: invalid number of arguments");
    return EXIT_FAILURE;	/*1 */
  } else {
    char linha[1024]; /* 0 to 255 */ 
    int tabela_frequencias[256];
    int tamanho_lido;
    int descritor_ficheiro;
    if ( strcmp (argv[1] , "rb") == 0 ){
      descritor_ficheiro = open(argv[2], O_RDONLY );  // r for read, b for binary
    }
    else {
      if ( strcmp ( argv[1] , "rt" ) == 0 ) {
        descritor_ficheiro = open(argv[2], O_RDONLY );  // r for read, b for binary
      } 
      else {
        return EXIT_FAILURE;	/*1 */
      }
    }
    while ( ( tamanho_lido = readfreq (descritor_ficheiro, linha, tabela_frequencias )) > 0) {	//le o ficheiro temporario
    printf("tamanho lido%d", tamanho_lido );
    }
    printf("Tabela de Frequências\n");
    for ( int pos = 0; pos <256; pos++ ){
      printf( "%d\t%d\n", pos, tabela_frequencias[pos]);
    }
    close(descritor_ficheiro);
    return EXIT_SUCCESS;	/*0 */
  }
}

