#include "blockFactory.h"
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "oBlock.h"
#include "sBlock.h"
#include "tBlock.h"
#include "tileBlock.h"
#include "zBlock.h"

using namespace std;

BlockFactory::BlockFactory() {}

BlockFactory::BlockFactory(Board *board) {
  factories_[IBlock] = new IBlock::IBlockFactory;
  factories_[JBlock] = new JBlock::JBlockFactory;
  factories_[LBlock] = new LBlock::LBlockFactory;
  factories_[SBlock] = new SBlock::SBlockFactory;
  factories_[ZBlock] = new ZBlock::ZBlockFactory;
  factories_[OBlock] = new OBlock::OBlockFactory;
  factories_[TBlock] = new TBlock::TBlockFactory;
  factories_[TILE_BLOCK] = new TileBlock::TileBlockFactory;
  board_ = board;
}

BlockFactory::~BlockFactory() {
  for (auto const &it : factories_) {
    if (it.second != nullptr) {
      delete it.second;
    }
  }
}

Block *BlockFactory::createBlock(BlockType bType, bool isHeavy) {
  if (factories_.count(bType) > 0) {
    return factories_[bType]->create(board_, isHeavy);
  }
  return nullptr;
}

Block *BlockFactory::create(Board *, bool) {}
