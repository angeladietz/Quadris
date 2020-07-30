#ifndef _BLOCKSELECTIONSTRATEGY_
#define _BLOCKSELECTIONSTRATEGY_

#include <string>
#include <map>
#include "quadris.h"
#include "block.h"
#include "blockFactory.h"

struct PImpl_bs{
    std::map<BlockType, int> blockProbabilities_;
	BlockFactory* blockFactory_;
	bool areBlocksHeavy_;
	bool isRandom_;
	std::string sequenceFile_;
};

class BlockSelectionStrategy {
	public:
		//TODO: DECIDE WHAT TO DO WITH DEFAULT CONSTRUCTOR
		BlockSelectionStrategy();
		//////////////////////////

		BlockSelectionStrategy(BlockFactory*);
        ~BlockSelectionStrategy();
		virtual Block* getNextBlock()=0;
		virtual void setRandom(bool);
		virtual void setSequenceFile(std::string);

	protected:
		BlockType getBlockType(char);
};

#endif
