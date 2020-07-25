#ifndef _BLOCKSELECTIONSTRATEGY_
#define _BLOCKSELECTIONSTRATEGY_

#include <string>
#include "quadris.h"
#include "block.h"

class BlockSelectionStrategy {
	public:
		BlockSelectionStrategy();
        ~BlockSelectionStrategy();
		virtual Block* getNextBlock()=0;
};

#endif
