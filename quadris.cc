#include "quadris.h"
#include "controller.h"
#include "blockSelectionStrategy.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "textDisplay.h"
#include "GUI.h"
#include "observer.h"
#include <vector>
#include <gtkmm.h> 
#include <cairomm/cairomm.h> 

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
            delete quadris_->views_[i];
        }
        if (quadris_->controller_ != nullptr){
            delete quadris_->controller_;
        }
        if (quadris_->board_ != nullptr){
            delete quadris_->board_;
        }
        if (quadris_->gui_ != nullptr){
            delete quadris_->gui_;
        }
        delete quadris_;
    }
}

void Quadris::playGame(int argc, char* argv[]){
    quadris_->board_ = new Board(this, quadris_->level_, quadris_->scriptFile_);

    quadris_->controller_ = new Controller(quadris_->board_);

    quadris_->views_.push_back(new TextDisplay(quadris_->board_, quadris_->controller_));

    /* if (!quadris_->textOnly_){ */
    /*     quadris_->views_.push_back(new Graphics()); */
    /* } */
    if(!quadris_->textOnly_){
        Gtk::Main app(argc, argv);
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("GUI.glade");
        //GUI *gui = nullptr;
        builder->get_widget_derived("mainWindow", quadris_->gui_, quadris_->controller_, quadris_->board_);
        Gtk::Main::run(*quadris_->gui_);
        //delete gui;
    }

    quadris_->board_->subscribe(quadris_->views_[0]);
    //quadris_->board_->subscribe(quadris_->views_[1]);

    //cerr<<"end of game"<<endl;
    // TODO: FINISH THIS

    quadris_->board_->notifyObservers();
    quadris_->views_[0]->poll();
}

void Quadris::restartGame(){
    for (auto view: quadris_->views_){
        quadris_->board_->unsubscribe(view);
        delete view;
    }
	quadris_->views_.clear();
    delete quadris_->controller_;
    delete quadris_->board_;
    delete quadris_->gui_;
    resetQuadrisParams();
    char* quadris[0];
    playGame(1, quadris);
}

void Quadris::resetQuadrisParams(){
    quadris_->textOnly_ = false;
    quadris_->level_ = 0;
    quadris_->scriptFile_ = "sequence.txt";
}
