/*******************************************************************************
File: creatures.h
*******************************************************************************/
#ifndef CREATURES_H
#define CREATURES_H

#include "random.h"
#include "coords.h"

class Creature {
      public:
           Creature();
           Creature(Coords Position);
           Coords Position() const {return position;}
           virtual void Move(Creature*** AdjacentTiles);
           virtual int Breed(Creature*** AdjacentTiles);
           virtual bool Die() { return false; }
           virtual char Species(){ return 'C';}
      protected:
           Coords position;
           int gestation;
           int nextChild;
};
class Hunter: public Creature {
      public:
           Hunter();
           Hunter(Coords Position);
           virtual void Move(Creature*** AdjacentTiles);
           virtual int Breed(Creature*** AdjacentTiles);
           virtual bool Die();
           virtual char Species() { return 'H'; }
      private:
           int hunger;
};
class Prey: public Creature {
      public:
           Prey();
           Prey(Coords Position);
           virtual void Move(Creature*** AdjacentTiles);
           virtual int Breed(Creature*** AdjacentTiles);
           virtual bool Die() { return false; }
           virtual char Species() { return 'P'; }
      private:
           
};

#endif
