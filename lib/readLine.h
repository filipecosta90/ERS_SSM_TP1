#ifndef readLine_h
#define readLine_h

#ifndef unistdBiblio
#define unistdBiblio
#include <unistd.h>     /* fork, pipe, primitivas IO(read, write, close,etc) */
#endif
#ifndef stdlibBiblio
#define stdlibBiblio
#include <stdlib.h>     /* malloc, free, rand */
#endif
#ifndef stringBiblio
#define stringBiblio
#include <string.h>     /* strstr, strlen, etc */
#endif

int readln( int fd, char *buffer);

#endif
