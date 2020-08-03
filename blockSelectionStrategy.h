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
	BlockType nextBlockType_;
};

class BlockSelectionStrategy {
	public:
		BlockSelectionStrategy(){}
        virtual ~BlockSelectionStrategy();

		Block* getNextBlock();
		BlockType getNextBlockType();
		Block* getBlockOfType(BlockType);

		void setRandom(bool);
		void setSequenceFile(std::string);

	protected:
		BlockType getBlockType(char);
		virtual void setNextBlockType()=0;
		BlockType getNextRandBlockType();
		BlockType getNextNonRandBlockType();
		void updateBlockIndex();
		void readSequenceFile();
		PImpl_bs* level_;
};

#endif
