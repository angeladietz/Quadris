#include "quadris.h"
#include "controller.h"
#include "blockSelectionStrategy.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "textDisplay.h"
#include "graphics.h"
#include <vector>

using namespace std;

Quadris::Quadris(bool textOnly, int startLevel, string scriptFile){
    quadris_ = new PImpl_Q;
    quadris_->textOnly_ = textOnly;
    quadris_->level_ = startLevel <= 4 && startLevel >= 0 ? startLevel : 0;
    quadris_->scriptFile_ = scriptFile;
    //quadris_->score_ = 0;
}

Quadris::~Quadris(){
    if (nullptr != quadris_){
        delete quadris_;
    }
}

void Quadris::playGame(){
    //TODO: MOVE MOST OF THIS TO THE CONSTRUCTOR!!
    quadris_->board_ = new Board(quadris_->level_, quadris_->scriptFile_);
    quadris_->controller_ = new Controller(quadris_->board_);

    quadris_->views_.push_back(new TextDisplay());

    if (!quadris_->textOnly_){
        quadris_->views_.push_back(new Graphics());
    }

    quadris_->board_->subscribe(quadris_->views_[0]);
    quadris_->board_->subscribe(quadris_->views_[1]);

    // TODO: FINISH THIS
}

int Quadris::getScore() const{
    //return quadris_->score_;
}

void Quadris::updateScore(int score) {
    //quadris_->score_ = score;
}

void Quadris::restartGame(){
    // TODO
}

// MOVE TO BOARD CLASS
// void Quadris::changeLevel(int newLevel){
//     if (newLevel >= MIN_LEVEL && newLevel <= MAX_LEVEL && newLevel != quadris_->level_){
//         delete quadris_->blockSelectionStrategy_;
//     }

//     if (0 == newLevel){
//         quadris_->blockSelectionStrategy_ = new Level0();
//     }
//     else if (1 == newLevel){
//         quadris_->blockSelectionStrategy_ = new Level1();
//     }
//     else if (2 == newLevel){
//         quadris_->blockSelectionStrategy_ = new Level2();
//     }
//     else if (3 == newLevel){
//         quadris_->blockSelectionStrategy_ = new Level3();
//     }
//     else{
//         quadris_->blockSelectionStrategy_ = new Level4();
//     }
// }
