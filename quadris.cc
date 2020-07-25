#include "quadris.h"
#include "controller.h"
#include "blockSelectionStrategy.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;

#define MIN_LEVEL 0
#define MAX_LEVEL 4

Quadris::Quadris(){
    quadris_ = new PImpl_Q;
    quadris_->level_ = 0;
    quadris_->score_ = 0;
    quadris_->blockSelectionStrategy_ = new Level0();
}

Quadris::~Quadris(){
    if (nullptr != quadris_){
        delete quadris_;
    }
}

void Quadris::startGame(){
    quadris_->board_ = new Board();
    // TODO: FINISH THIS
}

int Quadris::getScore() const{
    return quadris_->score_;
}

void Quadris::updateScore(int score) {
    quadris_->score_ = score;
}

void Quadris::restartGame(){
    // TODO
}

void Quadris::changeLevel(int newLevel){
    if (newLevel >= MIN_LEVEL && newLevel <= MAX_LEVEL && newLevel != quadris_->level_){
        delete quadris_->blockSelectionStrategy_;
    }

    if (0 == newLevel){
        quadris_->blockSelectionStrategy_ = new Level0();
    }
    else if (1 == newLevel){
        quadris_->blockSelectionStrategy_ = new Level1();
    }
    else if (2 == newLevel){
        quadris_->blockSelectionStrategy_ = new Level2();
    }
    else if (3 == newLevel){
        quadris_->blockSelectionStrategy_ = new Level3();
    }
    else{
        quadris_->blockSelectionStrategy_ = new Level4();
    }
}