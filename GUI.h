#ifndef GRAPHICAL_DISPLAY
#define GRAPHICAL_DISPLAY

#include <gtkmm.h> 
#include <cairomm/cairomm.h> 
#include <string>
#include <vector>
#include "observer.h"

#define BOARD_WIDTH 11
#define BOARD_HEIGHT 18
#define PREVIEW_SIZE 4

using namespace std;

//forward declaration of Quadris
class Quadris;

class GUI: public Gtk::Window, public Observer {

public:
    GUI(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder, Controller* controller, Board* board, Quadris* quadris);
    ~GUI();
	void update() override;
	
	// "quit" action handler.
	void OnQuit();

	/** Subclass for drawing area. */ 
	class CDrawingArea: public Gtk::DrawingArea { 
	public: 
		typedef enum { IBLOCK, JBLOCK, LBLOCK, OBLOCK, SBLOCK, ZBLOCK, TBLOCK, HINTBLOCK, STARBLOCK, EMPTYBLOCK } shape_t; 
	private: 
		Board* board_;
		Controller* controller_;
		shape_t _curBlock = EMPTYBLOCK; 

		/** Drawing event handler. */ 
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) { 
			switch (_curBlock) { 
				case IBLOCK: 
					cr->rectangle(0, 0, 40, 40); 
					cr->set_source_rgb(0, 0.9, 0); // light green 
					cr->fill_preserve(); 
					break; 
				case JBLOCK: 
					cr->rectangle(0, 0, 40, 40); 
					cr->set_source_rgb(0.8, 0, 0); // red
					cr->fill_preserve(); 
					break;  
				case LBLOCK: 
					cr->rectangle(0, 0, 40, 40);  
					cr->set_source_rgb(0, 0, 0.8); //dark blue
					cr->fill_preserve(); 
					break; 
				case OBLOCK: 
					cr->rectangle(0, 0, 40, 40); 
					cr->set_source_rgb(0, 0.8, 1); // light blue
					cr->fill_preserve(); 
					break; 
				case SBLOCK: 
					cr->rectangle(0, 0, 40, 40);  
					cr->set_source_rgb(0, 0.3, 0); // dark green 
					cr->fill_preserve(); 
					break; 
				case ZBLOCK: 
					cr->rectangle(0, 0, 40, 40);  
					cr->set_source_rgb(0.8, 0, 0.8); //pink
					cr->fill_preserve(); 
					break; 
				case TBLOCK: 
					cr->rectangle(0, 0, 40, 40);  
					cr->set_source_rgb(0.8, 0.8, 0.8); // grey
					cr->fill_preserve(); 
					break;  	
				case HINTBLOCK: 
					cr->rectangle(0, 0, 40, 40);  
					cr->set_source_rgb(0.3, 0, 0); // brown
					cr->fill_preserve(); 
					break; 
				case STARBLOCK: 
					cr->rectangle(0, 0, 40, 40); 
					cr->set_source_rgb(0.4, 0.8, 0.2); // black
					cr->fill_preserve(); 
					break;  
				case EMPTYBLOCK: 
					cr->rectangle(0, 0, 40, 40); 
					cr->set_source_rgb(0, 0, 0); // white
					cr->fill_preserve(); 
					break;  																			
				} 
				cr->set_line_width(3); 
				cr->set_source_rgb(0, 0, 0); 
				cr->stroke(); 
				return true; 
			} 
	public: 
		CDrawingArea(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
			: Gtk::DrawingArea(cobject) {} 

		void SetBlock(shape_t block) { 
			if (_curBlock != block) { 
				_curBlock = block; 
				queue_draw(); // Request re-drawing. 
			} 
		} 
	}; 
	
private:
	Board* board_;
	Controller* controller_;
	Quadris* quadris_;

	//Gtk objects
    Glib::RefPtr<Gtk::Builder> _builder; 
	Gtk::Box *objectContainer;
	Gtk::Box *scoreBoard;
	Gtk::Box *controlBox;
	Gtk::Grid *gameBoard;
	Gtk::Label *levelLabel;
	Gtk::Label *scoreLabel;
	Gtk::Label *hiScoreLabel;
	Gtk::ToggleButton *startButton;
	Gtk::Label *nextLabel;
	Gtk::Grid *nextGrid;
	Gtk::Separator *controlSeparator;
	
	vector<vector<CDrawingArea*>> drawBlocks = vector<vector<CDrawingArea*>>( 18 , vector<CDrawingArea*> (11));
	vector<vector<CDrawingArea*>> nextBlock = vector<vector<CDrawingArea*>>( 4 , vector<CDrawingArea*> (4));

	//OnClick handler for start button
	void startButtonClicked();
};

#endif
