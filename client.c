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
#include <sys/signalfd.h>
#define clrscr() printf("\e[1;1H\e[2J")
static volatile int keepRunning = 1:

void isexit(char * in){
  if (strcmp(in, "e") == 0){
    keepRunning = 0:
  }
}
void intHandler(int dummy) {
  if (dummy == SIGINT){
    keepRunning = 0;
  }
  if (dummy = SIGPIPE){
    keepRunning = 0;
  }
}

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
        if(fgets(input,100,stdin) == NULL){
          done_asking = 1;
        }
        strcpy(username, input);
        printf("\nWhat is the roomname you wish to join?\n" );
        if(fgets(input,100,stdin) == NULL){
          done_asking = 1;
        }
        strcpy(roomname, input);
        printf("\nAre you ok with these responses? (y/n)\nusername: %sroomname to join: %s", username, roomname);
        if(fgets(input,100,stdin) == NULL){
          done_asking = 1;
        }
        if (strcmp(input, "y\n")==0 || strcmp(input, "Y\n")==0){
          if (roomname[strlen(roomname)-1] == '\n'){
            roomname[strlen -1 ] = '\0';
          }
          fromHost = open(strcat("/tmp/", roomname), O_RDONLY);
          if(fromHost != -1){
            done_asking = 2;
          }
          printf("invalid room\n");
        }
      }
      if (done_asking == 1){
        exit(0)
        //end
      }
      char buffer[100];
      read(fromHost, buffer, 100);
      toHost = open(buffer, O_WRONLY);
      pid_t pid = getpid();
      snprintf(buffer, 100, "%d", pid);
      char tmp = "/tmp/";
      strcat(tmp, buffer);
      strcpy(buffer, tmp);
      mkfifo(buffer, 666);
      write(toHost, buffer,100);
      remove(buffer);
      write(toHost, username, 100);
      int gamerunning = 1;
      while (gamerunning == 1) {
        read(fromHost, buffer,100);
        isexit(buffer);
        clrscr();
        printf("your card(s)\n" );
        for(int i = 0; i < atoi(buffer); i ++){
          read(fromHost,buffer, 100);
          isexit(buffer);
          printf("%s ", buffer);
          if(p % 10 == 0){
            printf("\n");
          }
        }
        printf("current card\n" );
        read(fromHost,buffer, 100);
        isexit(buffer);
        printf("%s\n", buffer);
        read(fromHost,buffer, 100);
        isexit(buffer);
        for(int k = 0; k < atoi(buffer), k++){
          char tmp2[100];
          read(fromHost, tmp2, 100);
          isexit(tmp2);
          read(fromHost,buffer, 100);
          isexit(buffer);
          printf("%s: %s cards \n", buffer, tmp2);
        }
        read(fromHost,buffer, 100);
        isexit(buffer);
        if(strcmp(buffer, "u") == 0){
          int valid = 0;
          while (valid == 0) {
            printf("Enter the card you want to play or d for draw\n");
            fgets(buffer,100,stdin);
            write(toHost, buffer, 100);
            read(fromHost, buffer, 100);
            isexit(buffer);
            if(strcmp(buffer,"g")==0){
              valid = 1;
            }
            printf("invalid entry\n");
          }
        }
        else if(strcmp(buffer, "n") != 0){
          gamerunning = 0;
        }
        //not ur turn
      }
      printf("%s WON!!!!\n", buffer);
      exit(0);
    }
    printf("Someone disconnected (bruh moment)\n");
    exit(0);
  }
}
