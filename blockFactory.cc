#include "blockFactory.h"
#include "block.h"
#include "iBlock.h"
#include "jBlock.h"
#include "lBlock.h"
#include "sBlock.h"
#include "zBlock.h"
#include "oBlock.h"
#include "tBlock.h"

using namespace std;

BlockFactory::BlockFactory(){
    factories_[IBlock] = new IBlock::IBlockFactory;
    factories_[JBlock] = new JBlock::JBlockFactory;
    factories_[LBlock] = new LBlock::LBlockFactory;
    factories_[SBlock] = new SBlock::SBlockFactory;
    factories_[ZBlock] = new ZBlock::ZBlockFactory;
    factories_[OBlock] = new OBlock::OBlockFactory;
    factories_[TBlock] = new TBlock::TBlockFactory;
}

BlockFactory::~BlockFactory(){
    for (auto const& it : factories_)
    {
        if (it.second != nullptr){
            delete it.second;
        }
    }
}

Block* BlockFactory::createBlock(BlockType bType, bool isHeavy){
    if (factories_.count(bType) > 0){
        return factories_[bType]->create(isHeavy);
    }
    return nullptr;
}
