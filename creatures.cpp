/*******************************************************************************
File: creatures.cpp
*******************************************************************************/
#include "creatures.h"

Creature::Creature(): gestation(0) {
     Coords temp(0,0);
     temp.Move(0,0);
     position = temp;
}
Creature::Creature(Coords Position): position(Position),gestation(0) {}
Hunter::Hunter(): hunger(0) {
     nextChild = gestation = 8;
}
Hunter::Hunter(Coords Position): Creature(Position),hunger(0) {
     nextChild = gestation = 8;
}
Prey::Prey(Coords Position): Creature(Position){
     nextChild = gestation = 3;
}
Prey::Prey(){
     nextChild = gestation = 3;
}
void Creature::Move(Creature*** AdjacentTiles) {
/*******************************************************************************
Name: Creature::Move()
Purpose: Determines the valid moves available to the creature, then moves to one
         at random.
Arguments:     Creature*** AdjacentTiles     Array of grid tiles around creature
Return Value:  void
*******************************************************************************/
     int validMoves[4];
     int numValidMoves = 0;
     for(int i = 0; i < 4; i++)
          if(*(AdjacentTiles[i]) == NULL) {
               validMoves[numValidMoves] = i;
               numValidMoves++;
          }
     if(numValidMoves) {
          int location = Random::Get(numValidMoves -1);
          location = validMoves[location];
          position = position.Move(location);
          *(AdjacentTiles[location]) = this;
          *(AdjacentTiles[4]) = NULL;
     }
}
void Hunter::Move(Creature*** AdjacentTiles) {
/*******************************************************************************
Name: Hunter::Move()
Purpose: First determines if any prey are available to the hunter. If so, select
         one at random.  If not, follow the default creature move rules and add
         one to hunger.
*******************************************************************************/
     int victims[4];
     int victimCount = 0;
     for(int i = 0; i < 4; i++)
          if(*AdjacentTiles[i] != NULL) {
               if((*AdjacentTiles[i])->Species() == 'P') {
                    victims[victimCount] = i;
                    victimCount++;
               }
          }
     if(victimCount > 0) {
          int victimIndex = victims[Random::Get(victimCount-1)];
          Creature* victim = *AdjacentTiles[victimIndex];
          delete victim;
          hunger = 0;
          position = position.Move(victimIndex);
          *AdjacentTiles[victimIndex] = this;
          *AdjacentTiles[4] = NULL;
          return;
     }
     hunger += 1;
     Creature::Move(AdjacentTiles);
}

bool Hunter::Die() {
     if(hunger == 3)
          return true;
     return false;
}
int Hunter::Breed(Creature*** AdjacentTiles) {
/*******************************************************************************
Name: Hunter::Breed()
Purpose: If the gestation period was reached, checks which blank spaces exist 
adjacent to the hunter, then randomly selects one to create a new hunter in.
*******************************************************************************/
     int spawnIndex = -1;
     int empty[4];
     int emptyCount = 0;
     if(nextChild == 0) {
         for(int i = 0; i < 4; i++)
              if( *AdjacentTiles[i] == NULL) {
                   empty[emptyCount] = i;
                   emptyCount++;
              }
         if(emptyCount > 0) {
              spawnIndex = empty[Random::Get(emptyCount-1)];
              Creature* temp = new Hunter(position.Move(spawnIndex));
              *AdjacentTiles[spawnIndex] = temp;
              spawnIndex = temp->Position().Convert1D();
         }
         nextChild = gestation;
     }
     else
          nextChild--;
     return spawnIndex;
}
void Prey::Move(Creature*** AdjacentTiles) {
     Creature::Move(AdjacentTiles);
}
int Prey::Breed(Creature*** AdjacentTiles) {
/*******************************************************************************
Name: Prey::Breed()
Purpose: If the gestation period was reached, checks which blank spaces exist 
adjacent to the prey, then randomly selects one to create a new prey in.
*******************************************************************************/
     int spawnIndex = -1;
     int empty[4];
     int emptyCount = 0;
     if(nextChild == 0) {
         for(int i = 0; i < 4; i++)
              if( *AdjacentTiles[i] == NULL)
                   empty[emptyCount++] = i;
         if(emptyCount > 0) {
              spawnIndex = empty[Random::Get(emptyCount-1)];
              Creature* temp = new Prey(position.Move(spawnIndex));
              *AdjacentTiles[spawnIndex] = temp;
              spawnIndex = temp->Position().Convert1D();
         }
         nextChild = gestation;
     }
     else
          nextChild--;
     return spawnIndex;
}
int Creature::Breed(Creature*** AdjacentTiles) {
     return -1;
}
