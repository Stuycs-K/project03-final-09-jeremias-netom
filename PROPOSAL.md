# Final Project Proposal

## Group Members:

Manoel Jeremias-Neto
       
# Intentions:

2-4 player crazy 8s
    
# Intended usage:

everyone will run the program.
whoever the host is will select "host" when starting, and then decide how many players to play, select starting card amount, their "room" name, and their own personal username.
all the other players will select "join" and will then join a room, then select their username.
they will then play crazy 8s (starting with random player)
  
# Technical Details:

one program with 2 modes:
       "host side":
              1. "host" sets up room settings ("client" (player) count, starting chips, "room" name, personal username)
              2. "host" creates WKP (O_WRONLY)
              3. "client" connects to WKP, "host" removes WKP
              4. "host" creates a PP for "client" to connect to (O_RDONLY)
              5. "host" waits for "client" to send its own PP
              6. "host" connects to "client" PP. (O_WRONLY)
              7. repeat 2-6 for specified number of "clients"
              8. "host" runs crazy 8s game, sending "client"s info about their hand
              9. "host" waits for "client" response on what player is doing
              10. "host" acts on information.
             EXTRA:
              if "host" disconects, (ctrl + c) send a message to all "client"s that "host" stopped, stops them as well.
       "client side":
              1. "client" chooses its own username
              2. "client" searches for WKP (O_RDONLY)
              3. "client" connects to PP from "host" (O_WRONLY)
              4. "client" creates its own PP, sends it to "host" (O_RDONLY)
              5. "client" recieves information on gamestate from "host"
              6. "client" sends "host" player reaction to gamestate
             EXTRA:
              if "client" disconects (ctrl + c), sends a message to "host" to remove only them from the game, and game continues as normal (unless no more clients connected, in which case game over.) 
   
Topics Covered in Class:
       Allocating memory (obv)
       Working with files (client searching for WKP)
       Pipes (connecting "client" and "host" together")
       Signals (alerting program, if player leaves)
     
Who is responisble:
       ME
  
Data Structures
       idk yet, will figure out as it becomes neccessary. :3
    
# Intended pacing:

mon 6 : start
mon 13 : have clients and hosts connecting to each other
sat 19 : have poker game working
tues 21 : bug fixing done
