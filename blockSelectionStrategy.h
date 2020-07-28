#ifndef _BLOCKSELECTIONSTRATEGY_
#define _BLOCKSELECTIONSTRATEGY_

#include <string>
#include "quadris.h"
#include "block.h"
#include "blockFactory.h"

struct PImpl_bs{
    std::map<BlockType, int> blockProbabilities_;
};

class BlockSelectionStrategy {
	public:
		//TODO: DECIDE WHAT TO DO WITH DEFAULT CONSTRUCTOR
		BlockSelectionStrategy();
		//////////////////////////

		BlockSelectionStrategy(BlockFactory*);
        ~BlockSelectionStrategy();
		virtual Block* getNextBlock()=0;
	protected:
		BlockType getBlockType(char);

		BlockFactory* blockFactory_;
		bool areBlocksHeavy_;
};

#endif
