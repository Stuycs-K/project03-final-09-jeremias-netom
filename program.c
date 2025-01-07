#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define clrscr() printf("\e[1;1H\e[2J")

#define NETWORKING_H
#define WKP "/mario"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000
#define MAX_CLIENTS 100

#define SYN 0
#define SYN_ACK 1
#define ACK 2
#define MESSAGE 3
#define EXIT 4

int main(int argc, char const *argv[]) {
  clrscr();
  printf("HOST(h) OR JOIN(j) GAME?\n");

  return 0;
}
