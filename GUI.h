#ifndef GRAPHICAL_DISPLAY
#define GRAPHICAL_DISPLAY

#include <gtkmm.h> 
#include <cairomm/cairomm.h> 
#include <string>
#include <vector>
#include "observer.h"

using std::string;
using std::vector;

class GUI: public Gtk::Window, public observer {

public:
    GUI(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, GameController* controller, GameBoard* board);
    ~GUI();
    void draw() override;
	
	// "quit" action handler.
	void OnQuit() { hide(); } 
	
private:
	
	//Gtk objects
    Glib::RefPtr<Gtk::Builder> _builder; 
	Gtk::Box *objectContainer;
	Gtk::Box *scoreBoard;
	Gtk::Box *controlBox;
	Gtk::Grid *gameGrid;
	Gtk::Label *levelLabel;
	Gtk::Label *scoreLabel;
	Gtk::Label *hiScoreLabel;
	Gtk::ToggleButton *startButton;
	Gtk::Label *nextLabel;
	Gtk::Grid *nextGrid;
	Gtk::Separator *controlSeparator;
	
	vector<vector<CDrawingArea*>> drawBlocks = vector<vector<CDrawingArea*>>( 18 , vector<CDrawingArea*> (11));
	vector<vector<CDrawingArea*>> nextBlock = vector<vector<CDrawingArea*>>( 4 , vector<CDrawingArea*> (4));
	
	vector<vector<Gtk::Image*>> gameBlocks = vector<vector<Gtk::Image*>>( 18 , vector<Gtk::Image*> (11));
	vector<vector<Gtk::Image*>> nextBlock = vector<vector<Gtk::Image*>>( 3 , vector<Gtk::Image*> (4));
	vector< Glib::RefPtr< Gdk::Pixbuf > > blocks;     
	
	//OnClick handler for start button
	void startButtonClicked();
	
	//Helper function to clear the next block display
	void clearNextDisplay();
};

#endif
