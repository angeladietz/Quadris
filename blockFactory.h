#ifndef _BLOCKFACTORY_
#define _BLOCKFACTORY_

#include <map>
#include "block.h"

class BlockFactory{
    public:
        BlockFactory();
        ~BlockFactory();
        Block* createBlock(BlockType, bool);

    private:
        std::map<BlockType, BlockFactory*> factories_;
};

#endif
