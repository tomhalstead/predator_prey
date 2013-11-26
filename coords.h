/*******************************************************************************
File: coords.h
*******************************************************************************/
#ifndef COORDS_H
#define COORDS_H

#define DEFAULT_SIZE 20



class Coords {
      public:
           Coords(); /* Sets the width/height of coordinate to DEFAULT_SIZE */
           Coords(int Width, int Height);
           bool Move(int X, int Y); /* Sets the coord to (X,Y) */
           Coords Move(int direction); /* 0:up 1:left 2:right 3:down */
           int X() const{return x;} /* Return the X position */
           int Y() const{return y;} /* Return Y position */
           int Convert1D() const; /* Returns 1D array index of [X,Y] */
           Coords Convert2D(int index) const;/* returns coord(X,Y) */
           bool operator ==(const Coords& RHS); 
                /* True if x==x,y==y (Ignores height and width */
      private:
           int x;
           int y;
           int width;
           int height;
};

#endif
