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
#include "observer.h"
#include <vector>

using namespace std;

Quadris::Quadris(bool textOnly, int startLevel, string scriptFile){
    quadris_ = new PImpl_Q;
    quadris_->textOnly_ = textOnly;
    quadris_->level_ = startLevel <= 4 && startLevel >= 0 ? startLevel : 0;
    quadris_->scriptFile_ = scriptFile;
    highScore = 0;
}

Quadris::~Quadris(){
    if (nullptr != quadris_){
        for (int i = 0; i < quadris_->views_.size(); i++){
            cerr<<"deleting view"<<endl;
            delete quadris_->views_[i];
        }
        if (quadris_->controller_ != nullptr){
            cerr<<"deleting controller"<<endl;
            delete quadris_->controller_;
        }
        if (quadris_->board_ != nullptr){
            cerr<<"deleting board"<<endl;
            delete quadris_->board_;
        }
        delete quadris_;
    }
}

void Quadris::playGame(){
    cerr<<"Starting game"<<endl;
    //TODO: MOVE MOST OF THIS TO THE CONSTRUCTOR!!
    quadris_->board_ = new Board(this, quadris_->level_, quadris_->scriptFile_);
    cerr<< "Board made" << endl;
    cout<< "Enter cmd: ";
    td->poll();
    cout << *quadris_->board_;

    quadris_->controller_ = new Controller(quadris_->board_);

    quadris_->views_.push_back(new TextDisplay(quadris_->board_, quadris_->controller_));

    /* if (!quadris_->textOnly_){ */
    /*     quadris_->views_.push_back(new Graphics()); */
    /* } */

    quadris_->board_->subscribe(quadris_->views_[0]);
    //quadris_->board_->subscribe(quadris_->views_[1]);

    for (auto view: quadris_->views_) {
        view->poll();
    }
    cerr<<"end of game"<<endl;
    // TODO: FINISH THIS
}

void Quadris::restartGame(){
    for (auto view: quadris_->views_){
        quadris_->board_->unsubscribe(view);
        delete view;
    }
    delete quadris_->controller_;
    delete quadris_->board_;
    resetQuadrisParams();
    playGame();
}

void Quadris::resetQuadrisParams(){
    quadris_->textOnly_ = false;
    quadris_->level_ = 0;
    quadris_->scriptFile_ = "sequence.txt";
}
