#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include <vector>

#include "tile.h"

// Forward declaration of board class
class Board;

enum BlockType {IBlock,JBlock,LBlock,SBlock,ZBlock,OBlock,TBlock,TILE_BLOCK,INVALID_BLOCK};

class Block {

    public:
        Block(BlockType, Board*);
        ~Block();

        // Public methods to rotate a given block
        // Rotation is dependent on the kind of block so it is defined as a virtual method
        virtual void rotateClockwise(Board*) = 0;
        virtual void rotateCounterClockwise(Board*) = 0;
        
        // Public methods to move block around - same for each block so non-virtual
        void moveLeft(Board*);
        void moveRight(Board*);
        void moveDown(Board*);
        void dropBlock();

        BlockType getBlockType() const;
        bool getTilePositions() const;
        bool isHeavy();
        char getType();
        int getGenLevel();

    protected:

        // Private helper methods - do not need to be exposed to the client (i.e. Board)
        bool canMove(Board*, std::vector<int>);
        bool canMoveLeft(Board*);
        bool canMoveRight(Board*);
        bool canMoveDown(Board*);

        // Private virtual methods to check if a block can be rotated
        // Do not need to be exposed to client programmer but are dependent on the kind of block
        // Thus are required to be virtual
        bool canRotateClockwise(Board*);
        bool canRotateCounterClockwise(Board*);

        std::vector<int> getEndCoordinates();

        // Member variables
        std::vector<Tile*> tiles_;
        char type;

};

#endif
