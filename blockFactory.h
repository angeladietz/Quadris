#ifndef _BLOCKFACTORY_
#define _BLOCKFACTORY_

#include <map>
#include "block.h"
#include "tile.h"

class BlockFactory{
    public:
        BlockFactory();
        BlockFactory(Board*);
        ~BlockFactory();
        Board* getBoard();
        Block* createBlock(BlockType, bool);
        bool canCreateBlock(BlockType, Board*);
    protected:
        Board* board_;
    private:
        virtual Block* create(Board*, bool);
        virtual bool canCreate(Board*);
        std::map<BlockType, BlockFactory*> factories_;
};

#endif
