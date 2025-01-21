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
  int r = rand();
  strcat(card, suit[r%4]);
  strcat(card, number[r%10]);
  return card;
}

void host(){
  //
  srand(time(NULL));
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
        mkfifo("/tmp/To_p1");
        strcpy(buffer, "/tmp/To_p1");
        write(toclient, buffer);
        players++;
        from_player_1 = open("/tmp/To_p1", O_RDONLY);
        read(from_player_1, 100, buffer);
        to_player_1 = open(buffer, O_WRONLY);
        remove("/tmp/To_p1");
      }
      else if(players == 1){
        mkfifo("/tmp/To_p2");
        strcpy(buffer, "/tmp/To_p2");
        write(toclient, buffer);
        players++;
        from_player_3 = open("/tmp/To_p3", O_RDONLY);
        read(from_player_1, 100, buffer);
        to_player_1 = open(buffer, O_WRONLY);
        remove("/tmp/To_p2");
      }
      else if(players == 2){
        mkfifo("/tmp/To_p3");
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
    int player3cards = 0;

    char * p0cards[100];
    char * p1cards[100];
    char * p2cards[100];
    char * p3cards[100];

    char p0name[100];
    strcpy(p0name, username);
    char p1name[100];
    char p2name[100];
    char p3name[100];

    read(fromclientarr[0], p1name, 100);
    read(fromclientarr[1], p2name, 100);
    read(fromclientarr[2], p3name, 100);

    int gamerunning = 1;
    int currplayer = 0;
    char currcard[100];
    char winner[100];


    char * suit[4];
    strcpy(suit[0], "s");
    strcpy(suit[1], "c");
    strcpy(suit[2], "h");
    strcpy(suit[3], "d");

    char * value[10];
    for (int i = 0; i < 10; i ++){
      char num[2]
      snprintf(num, 2, "%d", i);
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
      char * buffer2[100];
      if (players == 3){
        //player 3 info
        snprintf(buffer2, 100, "%d", p3cards);
        write(toclientarr[2], buffer2, 100);
        for (int o = 0; o < p3cards; o ++){
          strcpy(buffer2, player3cards[o]);
          write(toclientarr[2], buffer2, 100);
        }
        strcpy(buffer2, currcard, 100);
        write(toclientarr[2], buffer2, 100);
        //snd playr amount
        snprintf(buffer2, 100, "%d", players);
        write(toclientarr[2], buffer2, 100);
        //sending player info
        snprintf(buffer2, 100, "%d", player0cards);
        write(toclientarr[2], buffer2, 100);
        strcpy(buffer2, p0name, 100);
        write(toclientarr[2], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player1cards);
        write(toclientarr[2], buffer2, 100);
        strcpy(buffer2, p1name, 100);
        write(toclientarr[2], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player2cards);
        write(toclientarr[2], buffer2, 100);
        strcpy(buffer2, p2name, 100);
        write(toclientarr[2], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player3cards);
        write(toclientarr[2], buffer2, 100);
        strcpy(buffer2, p3name, 100);
        write(toclientarr[2], buffer2, 100);
        //
      }
      if(players >= 2){
        snprintf(buffer2, 100, "%d", p2cards);
        write(toclientarr[1], buffer2, 100);
        for (int o = 0; o < p2cards; o ++){
          strcpy(buffer2, player2cards[o]);
          write(toclientarr[1], buffer2, 100);
        }
        strcpy(buffer2, currcard, 100);
        write(toclientarr[1], buffer2, 100);
        //snd playr amount
        snprintf(buffer2, 100, "%d", players);
        write(toclientarr[1], buffer2, 100);
        //sending player info
        snprintf(buffer2, 100, "%d", player0cards);
        write(toclientarr[1], buffer2, 100);
        strcpy(buffer2, p0name, 100);
        write(toclientarr[1], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player1cards);
        write(toclientarr[1], buffer2, 100);
        strcpy(buffer2, p1name, 100);
        write(toclientarr[1], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player2cards);
        write(toclientarr[1], buffer2, 100);
        strcpy(buffer2, p2name, 100);
        write(toclientarr[1], buffer2, 100);
        //
        if  (players == 3){
          snprintf(buffer2, 100, "%d", player3cards);
          write(toclientarr[1], buffer2, 100);
          strcpy(buffer2, p3name, 100);
          write(toclientarr[1], buffer2, 100);
          //
        }
      }
      if(players >= 1){
        snprintf(buffer2, 100, "%d", p1cards);
        write(toclientarr[0], buffer2, 100);
        for (int o = 0; o < p1cards; o ++){
          strcpy(buffer2, player1cards[o]);
          write(toclientarr[0], buffer2, 100);
        }
        strcpy(buffer2, currcard, 100);
        write(toclientarr[0], buffer2, 100);
        //snd playr amount
        snprintf(buffer2, 100, "%d", players);
        write(toclientarr[0], buffer2, 100);
        //sending player info
        snprintf(buffer2, 100, "%d", player0cards);
        write(toclientarr[0], buffer2, 100);
        strcpy(buffer2, p0name, 100);
        write(toclientarr[0], buffer2, 100);
        //
        snprintf(buffer2, 100, "%d", player1cards);
        write(toclientarr[0], buffer2, 100);
        strcpy(buffer2, p1name, 100);
        write(toclientarr[0], buffer2, 100);
        //
        if(players == 2){
          snprintf(buffer2, 100, "%d", player2cards);
          write(toclientarr[0], buffer2, 100);
          strcpy(buffer2, p2name, 100);
          write(toclientarr[0], buffer2, 100);
        }
        //
        if  (players == 3){
          snprintf(buffer2, 100, "%d", player3cards);
          write(toclientarr[0], buffer2, 100);
          strcpy(buffer2, p3name, 100);
          write(toclientarr[0], buffer2, 100);
          //
        }
      }

//game loop time

      if (currplayer == 0){
        printf("\e[1;1H\e[2J");
        printf("current card\n" );
        printf("%s\n", currcard);
        printf("your card(s)\n" );
        for(int p = 0; p < p0cards; p++){
          printf("%s ", player0cards[p]);
          if(p % 10 == 0){
            printf("\n");
          }
        }
        printf("other players cards\n");
        printf("%s: %d\n", p0name, p0cards);
        printf("%s: %d\n", p0name, p0cards);
        if (players >=2){
          printf("%s: %d\n", p0name, p0cards);
        }
        if (players==3){
          printf("%s: %d\n", p0name, p0cards);
        }
        int cardvalid = 0;
        while(cardvalid == 0){
          printf("Enter the card you want to play or d for draw\n");
          char buffer3[100];
          strcpy(buffer3, "n");
          write(toclientarr[0], buffer3, 100);
          write(toclientarr[1], buffer3, 100);
          write(toclientarr[2], buffer3, 100);
          fgets(buffer3,100,stdin);
          if(strlen(buffer3) == 3){
            if(currcard[0] == buffer3[0] ||currcard[1] == buffer3[1] ||currcard[1] == '8' ||'8' == buffer3[1]){
              buffer3[2]='\0';
              for(int t = 0; t < p0cards; t++){
                if(strcmp(buffer3, player0cards[p0cards]) == 0){
                  for(int y = t; y < p0cards; y ++){
                    strcpy(player0cards[y], player0cards[y+1]);
                  }
                  p0cards--;
                  cardvalid = 1;
                  break;
                }
              }
            }
          }
          else if(strcmp(buffer3, "d\n") == 0){
            player0cards[p0cards] = randomizecard(suit, value);
            p0cards ++;
            cardvalid = 1;
            break;
          }
          else{
            printf("invalid entry (bruh)\n");
          }
        }
      }
      else if(currplayer == 1){
        char buffer3[100];
        int cardvalid = 0;
        strcpy(buffer3, "u");
        write(toclientarr[0], buffer3, 100);
        strcpy(buffer3, "n");
        write(toclientarr[1], buffer3, 100);
        write(toclientarr[2], buffer3, 100);
        while(cardvalid == 0){
          read(fromclientarr[0], buffer3, 100);
          if(strlen(buffer3) == 3){
            if(currcard[0] == buffer3[0] ||currcard[1] == buffer3[1] ||currcard[1] == '8' ||'8' == buffer3[1]){
              buffer3[2]='\0';
              for(int t = 0; t < p1cards; t++){
                if(strcmp(buffer3, player1cards[p1cards]) == 0){
                  for(int y = t; y < p1cards; y ++){
                    strcpy(player1cards[y], player1cards[y+1]);
                  }
                  p1cards--;
                  strcpy(buffer3, "g");
                  write(toclientarr[0], buffer3, 100);
                  cardvalid = 1;
                  break;
                }
              }
            }
          }
          else if(strcmp(buffer3, "d\n") == 0){
            player1cards[p1cards] = randomizecard(suit, value);
            p1cards ++;
            strcpy(buffer3, "g");
            write(toclientarr[0], buffer3, 100);
            cardvalid = 1;
            break;
          }
          strcpy(buffer3, "b");
          write(toclientarr[0], buffer3, 100);
        }
      }
      else if(currplayer == 2){
        char buffer3[100];
        int cardvalid = 0;
        strcpy(buffer3, "u");
        write(toclientarr[1], buffer3, 100);
        strcpy(buffer3, "n");
        write(toclientarr[0], buffer3, 100);
        write(toclientarr[2], buffer3, 100);
        while(cardvalid == 0){
          read(fromclientarr[1], buffer3, 100);
          if(strlen(buffer3) == 3){
            if(currcard[0] == buffer3[0] ||currcard[1] == buffer3[1] ||currcard[1] == '8' ||'8' == buffer3[1]){
              buffer3[2]='\0';
              for(int t = 0; t < p2cards; t++){
                if(strcmp(buffer3, player2cards[p1cards]) == 0){
                  for(int y = t; y < p2cards; y ++){
                    strcpy(player2cards[y], player2cards[y+1]);
                  }
                  p2cards--;
                  strcpy(buffer3, "g");
                  write(toclientarr[1], buffer3, 100);
                  cardvalid = 1;
                  break;
                }
              }
            }
          }
          else if(strcmp(buffer3, "d\n") == 0){
            player2cards[p2cards] = randomizecard(suit, value);
            p2cards ++;
            strcpy(buffer3, "g");
            write(toclientarr[1], buffer3, 100);
            cardvalid = 1;
            break;
          }
          strcpy(buffer3, "b");
          write(toclientarr[1], buffer3, 100);
        }
      }
      else if(currplayer == 3){
        char buffer3[100];
        int cardvalid = 0;
        strcpy(buffer3, "u");
        write(toclientarr[2], buffer3, 100);
        strcpy(buffer3, "n");
        write(toclientarr[0], buffer3, 100);
        write(toclientarr[1], buffer3, 100);
        while(cardvalid == 0){
          read(fromclientarr[2], buffer3, 100);
          if(strlen(buffer3) == 3){
            if(currcard[0] == buffer3[0] ||currcard[1] == buffer3[1] ||currcard[1] == '8' ||'8' == buffer3[1]){
              buffer3[2]='\0';
              for(int t = 0; t < p3cards; t++){
                if(strcmp(buffer3, player3cards[p1cards]) == 0){
                  for(int y = t; y < p3cards; y ++){
                    strcpy(player3cards[y], player3cards[y+1]);
                  }
                  p3cards--;
                  strcpy(buffer3, "g");
                  write(toclientarr[2], buffer3, 100);
                  cardvalid = 1;
                  break;
                }
              }
            }
          }
          else if(strcmp(buffer3, "d\n") == 0){
            player3cards[p3cards] = randomizecard(suit, value);
            p3cards ++;
            strcpy(buffer3, "g");
            write(toclientarr[2], buffer3, 100);
            cardvalid = 1;
            break;
          }
          strcpy(buffer3, "b");
          write(toclientarr[2], buffer3, 100);
        }
      }
      if(p0cards == 0){
        strcpy(winner, p0name);
        gamerunning = 0;
      }
      if(p1cards == 0){
        strcpy(winner, p1name);
        gamerunning = 0;
      }
      if(p2cards == 0){
        strcpy(winner, p2name);
        gamerunning = 0;
      }
      if(p3cards == 0){
        strcpy(winner, p3name);
        gamerunning = 0;
      }
      if(currplayer == 3){
        currplayer = 0;
      }
      curplayer++;
      if(players == 1 && currplayer == 2){
        currplayer = 0;
      }
      if(players == 2 && currplayer == 3){
        currplayer = 0;
      }
    }
    if(players == 3){
      write(toclientarr[2], winner, 100);
    }
    if(players>= 2){
      write(toclientarr[1], winner, 100);
    }
    write(toclientarr[0], winner, 100);
    printf("%s WON!!!!\n", winner);
    exit(0);
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
