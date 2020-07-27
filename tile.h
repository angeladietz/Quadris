#ifndef _TILE_
#define _TILE_

#include <iostream>
#include <ostream>

class Tile {
    public:
        Tile(char);
        ~Tile() {};

        bool isFilled() const;
        char getTileValue() const;

        friend std::ostream& operator<< (std::ostream&, Tile&);

    private:
        char tile_;
        bool isFilled_ = false;
};

char Tile::getTileValue() const {
    return tile_;
}

bool Tile::isFilled() const {
    return isFilled_;
}

Tile::Tile(char tile) {
   tile_ = tile; 
}

friend std::ostream& operator<< (std::ostream& out, Tile& t) {

    out << t.getTileValue();

}

#endif
