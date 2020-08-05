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
        Block();
        virtual ~Block();

        // Public methods to rotate a given block
        // Rotation is dependent on the kind of block so it is defined as a virtual method
        virtual void rotateClockwise(Board*);
        virtual void rotateCounterClockwise(Board*);
        
        // Public methods to move block around - same for each block so non-virtual
        void moveLeft(Board*);
        void moveRight(Board*);
        void moveDown(Board*);
        void dropBlock(Board*);

        std::vector<std::vector<int>> getBlockHint(Board*);
        BlockType getBlockType() const;
        bool isHeavy();
        int getGenLevel();
        int getNumTiles();
        void removeTile(Tile*);
        void moveTileDown(Tile*, Board*);

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

        void resetToLocations(Board*, std::vector<std::vector<int>>, bool=false);
        std::vector<std::vector<int>> getCurrentCoordinates();
        std::vector<int> getEndCoordinates();
        bool canCreateBlock(std::vector<std::vector<int>>, Board*);
        void createBlock(std::vector<std::vector<int>>, Board*);

        // Member variables
        std::vector<Tile*> tiles_;
        char type;
        BlockType blocktype;
        bool isHeavy_;
        int levelGen_;
};

#endif
