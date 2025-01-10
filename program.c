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
#include "host.h"
#include "client.h"

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
  //
  char buffer[100];
  //
  clrscr();
  //
  printf("HOST(h) OR JOIN(j) GAME?\n");
  while(fgets(buffer,100,stdin)!= 0){
    if (strcmp(buffer, "h\n")==0 || strcmp(buffer, "H\n")==0){
      host();
      break;
    }
    else if (strcmp(buffer, "j\n")==0 || strcmp(buffer, "J\n")==0){
      client();
      break;
    }
    else{
      printf("Invalid response, please use j / h.\n");
    }
  }
  printf("Thank you for playing!                                                               \n");
return 0;
}
