#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#define clrscr() printf("\e[1;1H\e[2J")
#include <time.h>
//DONT DISPLAY ROOMS THAT DONT HAVE AN "A" AT THE END
void client(){
  //
  srand(time(NULL));
  //
  char roomname[100];
  char username[100];
  char buffer[100];
  //
  int toHost = 0;
  int fromHost = 0;
  //
  int done_asking = 0;
  char input[100];
  while(keepRunning== 1 ){

    while (done_asking == 0){
      printf("\nWhat is ur username?\n" );
      if(fgets(input,100,stdin) == 0){
        done_asking = 1;
      }
      strcpy(username, input);
      printf("\nWhat is the roomname you wish to join?\n" );
      if(fgets(input,100,stdin) == 0){
        done_asking = 1;
      }
      strcpy(roomname, input);
      printf("\nAre you ok with these responses? (y/n)\nusername: %sroomname to join: %s", username, roomname);
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
    if (roomname[strlen(roomname)-1] == '\n'){
      roomname[strlen -1 ] = '\0';
    }

}
