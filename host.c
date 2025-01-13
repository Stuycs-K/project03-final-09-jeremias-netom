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

void host(){
  //
  char roomname[100];
  char username[100];
  //
  int start = 0;
  int toclientarr[3];
  int fromclientarr[3];
  int players = 0;
  //
  int done_asking = 0;
  char input[100];
  while (done_asking == 0){
    printf("\nWhat is ur username?\n" );
    if(fgets(input,100,stdin) == 0){
      done_asking = 1;
    }
    strcpy(username, input);
    printf("\nWhat is the roomname?\n" );
    if(fgets(input,100,stdin) == 0){
      done_asking = 1;
    }
    strcpy(roomname, input);
    printf("\nAre you ok with these responses? (y/n)\nusername: %sroomname: %s", username, roomname);
    if(fgets(input,100,stdin) == 0){
      done_asking = 1;
    }
    if (strcmp(input, "y\n")==0 || strcmp(input, "Y\n")==0){
      done_asking = 2;
    }
    printf("\n");
  }
  if (done_asking == 1){
    exit(0)
    //end
  }
  //continue
  if (roomname[strlen(roomname)-1] == '\n'){
    roomname[strlen -1 ] = '\0';
  }
  
  while(start == 0){
    printf("waiting for people to join\n");
    mkfifo(strcat("/tmp", roomname), 666);
    int fromclient;
    fromclient = open(strcat("/tmp", roomname), O_WRONLY);
    remove(strcat("/tmp", roomname));
    if(players == 0)
  }
}
