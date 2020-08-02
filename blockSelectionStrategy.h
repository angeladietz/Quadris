#ifndef _BLOCKSELECTIONSTRATEGY_
#define _BLOCKSELECTIONSTRATEGY_

#include <string>
#include <map>
#include <queue>
#include "block.h"
#include "blockFactory.h"

struct PImpl_bs{
    std::map<BlockType, int> blockProbabilities_;
	std::vector<BlockType> blockList_;
	int blockIndex_;
	BlockFactory* blockFactory_;
	bool areBlocksHeavy_;
	bool isRandom_;
	std::string sequenceFile_;
};

class BlockSelectionStrategy {
	public:
		//TODO: DECIDE WHAT TO DO WITH DEFAULT CONSTRUCTOR
		BlockSelectionStrategy(){}
		//////////////////////////

		//BlockSelectionStrategy(BlockFactory*);
        virtual ~BlockSelectionStrategy();
		virtual Block* getNextBlock()=0;
		virtual Block* getBlockOfType(BlockType)=0;
		virtual void setRandom(bool);
		virtual void setSequenceFile(std::string);

	protected:
		BlockType getBlockType(char);
};

#endif
