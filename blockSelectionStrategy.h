#ifndef _BLOCKSELECTIONSTRATEGY_
#define _BLOCKSELECTIONSTRATEGY_

#include <string>
#include "quadris.h"
#include "block.h"
#include "blockFactory.h"

struct PImpl_BS{
	BlockFactory* blockFactory_;
};

class BlockSelectionStrategy {
	public:
		BlockSelectionStrategy();
        ~BlockSelectionStrategy();
		virtual Block* getNextBlock()=0;
	protected:
		BlockType getBlockType(char);
		PImpl_BS* blockSelectionStrategy_;
};

#endif
