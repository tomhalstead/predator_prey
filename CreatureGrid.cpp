/*******************************************************************************
File: CreatureGrid.cpp
*******************************************************************************/

#include "CreatureGrid.h"

Grid::Grid() {
     width = DEFAULT_SIZE;
     height = DEFAULT_SIZE;
     size = height * width;
     allocWorld();
     initWorld();
}
Grid::Grid(int Size) {
     width = Size;
     height = Size;
     size = height * width;
     allocWorld();
     initWorld();
}
Grid::Grid(int Width, int Height) {
     width = Width;
     height = Height;
     size = height * width;
     allocWorld();
     initWorld();
}
Grid::Grid(const Grid& copyThis) {
     copyGrid(copyThis);
}
Grid::~Grid() {
     deleteWorld();
}
Grid& Grid::operator =(const Grid& Right) {
      if(&Right != this) {
           deleteWorld();
           copyGrid(Right);
      }
      return *this;
}
char* Grid::Snapshot() {
      char* resultWalker = snapshot;
      Creature*** walker = world;
      Creature** type;
      for(int i = 0; i < height; i++) {
            type = *walker++;
            for(int j = 0; j < width; j++) {
                 if(*type == NULL)
                      *resultWalker++ = '0';
                 else
                      *resultWalker++ = (*type)->Species();
                 type++;
            }
            if(i == height -1)
                 *resultWalker++ = 0;
            else
                 *resultWalker++ = '\n';
      }
      return snapshot;
}
bool Grid::AddHunter() {
     Coords position(width,height);
     do {
          position.Move(Random::Get(width-1),Random::Get(height-1));
     }while(*Tile(position) != NULL);
     Creature* add = new Hunter(position);
     *Tile(position) = add;
     return true;
}
bool Grid::AddPrey() {
     Coords position(width,height);
     do {
          position.Move(Random::Get(width-1),Random::Get(height-1));
     }while(*Tile(position) != NULL);
     Creature* add = new Prey(position);
     *Tile(position) = add;
     return true;
}
void Grid::Populate(int numHunters, int numPrey) {
     if( (numHunters + numPrey) > (height * width) )
          return;
     deleteWorld();
     allocWorld();
     initWorld();
     for(int i = 0; i < numHunters; i++)
          AddHunter();
     for(int j = 0; j < numPrey; j++)
          AddPrey();
}

void Grid::clearMoved(bool value) {
     for(int i = 0; i < size; i++)
          moved[i] = value;
}
void Grid::shuffleMoves() {
     int index;
     for(int i = 0; i < size; i++) {
          index = Random::Get(size-1);
          while(!moved[index]) {
               if(index > 0)
                    index--;
               else
                    index = size-1;
          }
          moves[i] = index;
          moved[i] = false;
     }
}

void Grid::Move() {
     int tileIndex, spawn;
     shuffleMoves();
     Coords tile(width,height);
     
     int tiles[size];
     for(int i = 0; i < size; i++)
          tiles[i] = i;
     for(int i = 0; i < size; i++) {
          tileIndex = tiles[i];
          if(!moved[tileIndex]) {
               moved[tileIndex] = true;
               tile = tile.Convert2D(tileIndex);
               Creature* creature = *Tile(tile);
               if(creature != NULL) {
                    Creature*** adjacent = AdjacentTiles(creature->Position());
                    creature->Move(adjacent);
                    moved[creature->Position().Convert1D()] = true;
                    delete[] adjacent;
                    adjacent = AdjacentTiles(creature->Position());
                    spawn = creature->Breed(adjacent);
                    if(spawn > -1)
                         moved[spawn] = true;
                    if( creature->Die() ) {
                         delete creature;
              
                         *adjacent[4] = NULL;
                    }
                    
                    delete[] adjacent;
               }
          }
     }
}

Creature** Grid::Tile(const Coords& location) {
     int x = location.X();
     int y = location.Y();
     if(x >= 0 && x < width)
          if(y >=0 && y < height)
               return &world[y][x];
     return NULL;
}
Creature*** Grid::AdjacentTiles(Coords location) {
     Creature*** temp = new Creature**[5];
     int x = location.X();
     int y = location.Y();
     if(y > 0)
          temp[0] = &world[y-1][x];
     else
          temp[0] = &world[height-1][x];
     if(x > 0)
          temp[1] = &world[y][x-1];
     else
          temp[1] = &world[y][width-1];
     if(x < width -1)
          temp[2] = &world[y][x+1];
     else
          temp[2] = &world[y][0];
     if(y < height -1)
          temp[3] = &world[y+1][x];
     else
          temp[3] = &world[0][x];
     temp[4] = &world[y][x];
     return temp;
     
}
void Grid::allocWorld() {
     snapshot = new char[size + height];
     moves = new int[size];
     moved = new bool[size];
     
     world = new Creature**[height];
     Creature*** walker = world;
     for(int i = 0; i < height; i++)
          *walker++ = new Creature*[width];
}
void Grid::initWorld() {
     initMoves();
     Creature*** walker = world;
     Creature**  init;
     for(int i = 0; i < height; i++) {
          init = *walker++;
          for(int j = 0; j < width; j++) {
               *init++ = NULL;
          }
     }
}
void Grid::initMoves() {
     for(int i = 0; i < size; i++) {
          moves[i] = i;
          moved[i] = true;
     }
}
void Grid::deleteWorld() {
     Creature*** walker = world;
     Creature**  tiles;
     for(int i = 0; i < height; i++) {
          tiles = *walker;
          for(int j = 0; j < width; j++)
               delete[] *tiles++;
          delete[] *walker++;
     }
     delete[] moved;
     delete[] moves;
     delete[] world;
     delete[] snapshot;
}
void Grid::copyGrid(const Grid& Right) {
     height = Right.height;
     width = Right.width;
     size = Right.size;
     allocWorld();
     for(int i = 0; i < size; i++) {
          moves[i] = Right.moves[i];
          moved[i] = Right.moved[i];
     }
     Creature*** leftIWalker = world;
     Creature*** rightIWalker = Right.world;
     Creature**  leftJWalker;
     Creature**  rightJWalker;
     for(int i = 0; i < height; i++) {
          leftJWalker = *leftIWalker++;
          rightJWalker = *rightIWalker++;
          for(int j = 0; j < width; j++)
               *leftJWalker++ = *rightJWalker++;
     }
}
