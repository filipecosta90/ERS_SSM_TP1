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
#ifndef stdioBiblio
#define stdioBiblio
#include <stdio.h>
#endif

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("FATAL: invalid number of arguments");
    return EXIT_FAILURE;	/*1 */
  } else {
    int tabela_frequencias[256];
    memset(tabela_frequencias , 0, 256 * sizeof (int));

    if ( strcmp ( argv[1] , "rt" ) == 0 ){
      FILE  *fp;
      fp = fopen(argv[2], "r" );  
      int  c;
      while((c = fgetc(fp)) != EOF) {
        tabela_frequencias[c]++;
      }
      fclose(fp);
    } 
    else {
      if ( strcmp (argv[1] , "rb") == 0 ) {
        int descritor_ficheiro;
        int c;
        memset(&c, 0, sizeof (int));
        descritor_ficheiro = open(argv[2], O_RDONLY );  // r for read, b for binary
        while( read(descritor_ficheiro, &c, 1) > 0 ){
          tabela_frequencias[c]++;
        }
      }
      else {
        return EXIT_FAILURE;	/*1 */
      }
    }
    printf("------------------\n");
    printf("Tabela Frequencias\n");
    printf("------------------\n");
    int total_caracteres = 0;
    int total_distinctos = 0;
    for (int pos = 0; pos < 256; pos++ ){
      printf("%d\t%d\n", pos, tabela_frequencias[pos]);
      total_caracteres += tabela_frequencias[pos];
      if ( tabela_frequencias[pos] > 0 ){
        total_distinctos++;
      }
    }
    printf("------------------\n");
    printf("total caracteres: %d\n", total_caracteres );
    printf("total caracteres distinctos: %d\n", total_distinctos );
    return EXIT_SUCCESS;
  }
}

