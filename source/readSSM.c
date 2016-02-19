#include "../lib/readSSM.h"
#define TAMANHO_BUFFER_AUXILIAR 1024

int readln(int fd, char *buffer)
{
  static char bufferAuxiliar[TAMANHO_BUFFER_AUXILIAR];
  static int posBufferAuxiliar = 0;
  static int nCaracteresLerdoBuffer = 0;
  int posBuffer = 0;

  if (nCaracteresLerdoBuffer == 0 || posBufferAuxiliar == (sizeof(bufferAuxiliar))) {
    nCaracteresLerdoBuffer = read(fd, bufferAuxiliar, sizeof(bufferAuxiliar));
    posBufferAuxiliar = 0;
  }
  while (nCaracteresLerdoBuffer > 0 && bufferAuxiliar[posBufferAuxiliar] != '\n') {
    buffer[posBuffer] = bufferAuxiliar[posBufferAuxiliar];
    if (posBufferAuxiliar == (sizeof(bufferAuxiliar) - 1)) {
      nCaracteresLerdoBuffer = read(fd, bufferAuxiliar, sizeof(bufferAuxiliar));
      posBufferAuxiliar = 0;
    } else {
      posBufferAuxiliar++;
      nCaracteresLerdoBuffer--;
    }
    posBuffer++;
  }
  if (bufferAuxiliar[posBufferAuxiliar] == '\n') {
    posBufferAuxiliar++;
    nCaracteresLerdoBuffer--;
  }
  buffer[posBuffer] = '\0';
  return posBuffer > 0 ? posBuffer : -1;
}

int readfreq (int fd, char* buffer, int* frequency_table){
   static unsigned char bufferAuxiliar[TAMANHO_BUFFER_AUXILIAR];
  static int posBufferAuxiliar = 0;
  static int nCaracteresLerdoBuffer = 0;
  int posBuffer = 0;

  if (nCaracteresLerdoBuffer == 0 || posBufferAuxiliar == (sizeof(bufferAuxiliar))) {
    nCaracteresLerdoBuffer = read(fd, bufferAuxiliar, sizeof(bufferAuxiliar));
    posBufferAuxiliar = 0;
  }
  while (nCaracteresLerdoBuffer > 0 ) {
    buffer[posBuffer] = bufferAuxiliar[posBufferAuxiliar];
    if (posBufferAuxiliar == (sizeof(bufferAuxiliar) - 1)) {
      nCaracteresLerdoBuffer = read(fd, bufferAuxiliar, sizeof(bufferAuxiliar));
      posBufferAuxiliar = 0;
    } else {
      posBufferAuxiliar++;
      nCaracteresLerdoBuffer--;
    }

    int pos = buffer[posBuffer];
    frequency_table[pos]++;
    printf("%d %d %d \t", buffer[posBuffer], pos, frequency_table[pos]);
    posBuffer++;
  }
  buffer[posBuffer] = '\0';
  return posBuffer > 0 ? posBuffer : -1;
}
