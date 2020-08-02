#ifndef _BLOCKFACTORY_
#define _BLOCKFACTORY_

#include <map>
#include "block.h"

class BlockFactory{
    public:
        BlockFactory();
        BlockFactory(Board*);
        ~BlockFactory();
        Block* createBlock(BlockType, bool);
    protected:
        Board* board_;
    private:
        virtual Block* create(Board*, bool);
        std::map<BlockType, BlockFactory*> factories_;
};

#endif
