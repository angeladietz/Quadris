#include "quadris.h"
#include "GUI.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <gtkmm.h> 
#include <cairomm/cairomm.h> 

using namespace std;

int highScore;

int main(int argc, char* argv[]) {

    bool didSetSeed = false;

    // Define default Quadris parameters
    bool textOnly = false;
    int startLevel = 0;
    std::string scriptFile = "sequence.txt";

	if (argc > 1){
        for (int i = 1; i < argc; i++){
            if (!strcmp(argv[i], "-text")){
                textOnly = true;
            }
            else if (!strcmp(argv[i], "-seed") && i < argc-1){
                int seed = std::stoi(argv[++i]);
                std::srand(seed);
                didSetSeed = true;
            }
            else if (!strcmp(argv[i], "-scriptfile") && i < argc-1){
                scriptFile = argv[++i];
            }
            else if (!strcmp(argv[i], "-startlevel") && i < argc-1){
                startLevel = std::stoi(argv[++i]);
            }
        }
	}

    if (!didSetSeed){
        std::srand(time(NULL));
    }

    cerr << "Initializing quadris" << endl;
    if(textOnly){
        Quadris* quadris = new Quadris(textOnly, startLevel, scriptFile);
        quadris->playGame();
        cerr << "Finished game"<<endl;
        delete Quadris;
    } else {
        Gtk::Main app(argc, argv);
        Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("quadrisGUI.glade");
        GUI *gui = nullptr;
        builder->get_widget_derived("topWindow", gui, Controller, Board);
        Gtk::Main::run(*gui);
        delete gui;
    }

    return 0;
}
