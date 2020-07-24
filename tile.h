#ifndef _TILE_
#define _TILE_

#include <iostream>

class Tile {
    public:
        Tile();
        ~Tile();

        bool isFilled() const;
        char getTileValue() const;

        friend std::ostream& operator<< (std::ostream&, Tile&);
};

#endif