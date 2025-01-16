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


static volatile int keepRunning = 1:

void intHandler(int dummy) {
  if (dummy == SIGINT){
    keepRunning = 0;
  }
  if (dummy = SIGPIPE){
    keepRunning = 0;
  }
}

char * randomizecard(char * suit, char * number){
  char card[4];
  srand(time(NULL));   // Initialization, should only be called once.
  int r = rand();
  strcat(card, suit[r%4]);
  strcat(card, number[r%9]);
  return card;
}

void host(){
  //
  char roomname[100];
  char username[100];
  char buffer[100];
  //
  int start = 0;
  int toclientarr[3];
  int fromclientarr[3];
  int players = 0;
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
    strcat(roomname, "A");

    mkfifo("/tmp/To_p1");
    mkfifo("/tmp/To_p2");
    mkfifo("/tmp/To_p3");

    int to_player_1=0;
    int to_player_2=0;
    int to_player_3=0;

    int from_player_1=0;
    int from_player_2=0;
    int from_player_3=0;


    while(start == 0){

      signal(SIGINT, intHandler);

      printf("waiting for people to join\n");
      mkfifo(strcat("/tmp/", roomname), 666);
      int toclient;
      toclient = open(strcat("/tmp/", roomname), O_WRONLY);
      remove(strcat("/tmp/", roomname));

      if(players == 0){
        strcpy(buffer, "/tmp/To_p1");
        write(toclient, buffer);
        players++;
        from_player_1 = open("/tmp/To_p1", O_RDONLY);
        read(from_player_1, 100, buffer);
        to_player_1 = open(buffer, O_WRONLY);
        remove("/tmp/To_p1");
      }
      else if(players == 1){
        strcpy(buffer, "/tmp/To_p2");
        write(toclient, buffer);
        players++;
        from_player_3 = open("/tmp/To_p3", O_RDONLY);
        read(from_player_1, 100, buffer);
        to_player_1 = open(buffer, O_WRONLY);
        remove("/tmp/To_p2");
      }
      else if(players == 2){
        strcpy(buffer, "/tmp/To_p3");
        write(toclient, buffer);
        players++;
        from_player_3 = open("/tmp/To_p3", O_RDONLY);
        read(from_player_1, 100, buffer);
        to_player_1 = open(buffer, O_WRONLY);
        remove("/tmp/To_p3");
      }
      else{
        printf("Starting!\n");
        close(toclient);
        start = 1;
      }
      printf("would you like to start? players joined: %d (y/n)\n", players);
      if (input[0] == 'Y'|| input[0] == 'y'){
        close(toclient);
        start = 1;
      }
      close(toclient);
    }

    toclientarr[0] = to_player_1;
    toclientarr[1] = to_player_2;
    toclientarr[2] = to_player_3;

    fromclientarr[0] = from_player_1;
    fromclientarr[1] = from_player_2;
    fromclientarr[2] = from_player_3;

    int player0cards = 0;
    int player1cards = 0;
    int player2cards = 0;
    int player4cards = 0;

    char * p0cards[100];
    char * p1cards[100];
    char * p2cards[100];
    char * p3cards[100];

    int gamerunning = 1;
    int currplayer = 0;
    char currcard[4];
    char winner[100];


    char * suit[4];
    strcpy(suit[0], "s");
    strcpy(suit[1], "c");
    strcpy(suit[2], "h");
    strcpy(suit[3], "d");

    char * value[9];
    for (int i = 0; i < 9; i ++){
      char num[2]
      snprintf(num, 2, "%d", i+1);
      strcpy(value[i], num);
    }

    for (int k = 0; k < 7; k ++){
      strcpy(p0cards[k], randomizecard(suit, value));
      player0cards ++;
    }
    for (int k = 0; k < 7; k ++){
      strcpy(p1cards[k], randomizecard(suit, value));
      player1cards ++;
    }
    for (int k = 0; k < 7; k ++){
      strcpy(p2cards[k], randomizecard(suit, value));
      player2cards ++;
    }
    for (int k = 0; k < 7; k ++){
      strcpy(p3cards[k], randomizecard(suit, value));
      player3cards ++;
    }

    strcpy(currcard, randomizecard(suit, value));

    while(gamerunning == 1){
      //send each player the gamestate
      if (players == 3){

      }
      else if(players == 2){

      }
      else if(players == 1){

      }



      if (currplayer == 0){

      }


    }
    printf("%s WON!!!!\n", winner);
  }
  printf("Someone disconnected (bruh moment)\n");
  for (int i = 0; i < 3; i ++ ){
    if(i < players-1){
      char exit[100];
      strcpy(exit, "e");
      write(toclientarr[i], exit, 100);
    }
  }
  exit(0);
}
