#ifndef _BLOCKFACTORY_
#define _BLOCKFACTORY_

#include "block.h"
#include <map>

class BlockFactory {
public:
  BlockFactory();
  BlockFactory(Board *);
  ~BlockFactory();
  Block *createBlock(BlockType, bool);

protected:
  Board *board_;

private:
  virtual Block *create(Board *, bool);
  std::map<BlockType, BlockFactory *> factories_;
};

#endif
