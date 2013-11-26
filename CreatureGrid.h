/*******************************************************************************
File: CreatureGrid.h
*******************************************************************************/
#ifndef CREATURE_GRID_H
#define CREATURE_GRID_H

#include "creatures.h"
class Grid {
      public:
           Grid();
           Grid(int Size);
           Grid(int Width, int Height);
           Grid(const Grid& copyThis);
           ~Grid();
           Grid& operator =(const Grid& Right);
           char* Snapshot(); 
               /* Returns 1D char array representing the grid. Line breaks 
               represent new rows and '0' represents a blank tile. Other
               characters are determined by the creature's Type() function */
           bool AddHunter(); /* Adds a hunter to a random blank tile */
           bool AddPrey(); /* Adds a prey to a random blank tile */
           void Populate(int numHunters, int numPrey);
               /* Fills the grid with the specified number of creatures. This
                  deletes existing creatures on the grid */
           void Move(); /* Instructs each creature on the grid to move, bread
                           and check for death condition, in random order */
           Creature** Tile(const Coords& location);
               /* Returns the address of the tile at the specified coords */
           Creature*** AdjacentTiles(Coords location);
               /* Returns an array of the tiles surrounding the specified
                  location.  Their indices correspond to cases in Coords::Move()
                  and index 4 is the center tile (Passed location) */
      private:
           void allocWorld(); /* Allocates class arrays for managing the grid */
           void initWorld(); /* Initializes class arrays to default values */
           void deleteWorld(); /* Deletes all dynamic arrays within the class */
           void copyGrid(const Grid& copyThis);
           void shuffleMoves();
           void initMoves(); /* Fills the moves array sequentially */
           void clearMoved(bool value = false); /* Resets the moved array */
           
           int width;
           int height;
           int size;
           int* moves;
           bool* moved;
           char* snapshot;
           Creature*** world;
};
#endif
