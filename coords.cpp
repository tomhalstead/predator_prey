/*******************************************************************************
File: coords.cpp
*******************************************************************************/
#include "Coords.h"

Coords::Coords(){
     width = DEFAULT_SIZE;
     height = DEFAULT_SIZE;
     x = 0;
     y = 0; 
}
Coords::Coords(int Width, int Height) {
     width = Width;
     height = Height;
     x = 0;
     y = 0; 
}

bool Coords::Move(int X, int Y) {
     if(X < width && X > 0) {
          if(Y < height && Y > 0) {
               x = X;
               y = Y;
               return true;
          }
     }
     return false;
}

Coords Coords::Move(int direction) {
/*******************************************************************************
Name: Coords::Move()
Purpose: Determines the new (X,Y) position
Arguments:     int direction       The direction to move
Return Value:  Coords              A coords class representing the new position
                                   (The original class is not modified)
*******************************************************************************/
     Coords result = *this;
     switch(direction) {
     case 0: // up
          if(y > 0)
               result.y -= 1;
          else
               result.y = height - 1;
          break;
     case 1: // left
          if(x > 0)
               result.x -= 1;
          else
               result.x = width - 1;
          break;
     case 2: // right
          if(x < width -1)
               result.x += 1;
          else
               result.x = 0;
          break;
     case 3: // down
          if(y < height -1)
               result.y += 1;
          else
               result.y = 0;
          break;
     }
     return result;
}      
int Coords::Convert1D() const {
     int result = y * width;
     result += x;
     return result;
}
Coords Coords::Convert2D(int index) const {
     Coords result(width,height);
     result.y = index / width;
     result.x = index - (result.y * width);
     return result;
}

bool Coords::operator ==(const Coords& RHS) {
     bool result;
     result =  (x == RHS.x);
     result &= (y == RHS.y);
     return result;
}
