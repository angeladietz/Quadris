#include "quadris.h"
#include "GUI.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

int highScore;

void printUsage() {

	cout << endl <<
  "CS 247 Project - Quadris \n"
  "Help: ./quadris [args]\n\n"
  
	// TODO: Add the text only mode when GUI is complete
  "Possible Arguments:\n"
  "  -seed [seed]             Set the random number generator's seed\n" 
  "  -scriptfile [file]       Use [file] instead of the default sequence.txt (only applies to level 0)\n"
  "  -startlevel [n]          Start game in level [n]\n"
  "  -h  or  --help           Display this help message\n"
  
  "In-game commands:\n"
  "  left                     Move Current Block Left\n"
  "  right                    Move Current Block Right\n"
  "  down                     Move Current Block Down\n"
  "  clockwise                Rotate Block Clockwise\n"
  "  counterclockwise         Rotate Block Counter Clockwise\n"
  "  drop                     Drop the current block - required to move to the next block\n"
  "  levelup                  Move up a level\n"
  "  leveldown                Move down a level\n"
  "  norandom [file]          Use [file] as a sequene of blocks\n"
  "  random                   Make levels 3 and 4 random (true by default)\n"
  "  sequence [file]          Change sequence file\n"
  "  I, J, L ...              Replace current block with specified block\n"
  "  restart                  Restart from Level 0\n"
  "  hint                     Display possible location to drop current block\n"
  
  << endl;

  exit(1);
}

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
						else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
                printUsage();
            }
            else {
                cout << "Invalid Input " << argv[i] << endl;
                printUsage();
            }
        }
	}

    if (!didSetSeed){
        std::srand(time(NULL));
    }

    Quadris* quadris = new Quadris(textOnly, startLevel, scriptFile);
    quadris->playGame(argc, argv);
    cout << "delete quadris"<<endl;
    delete quadris;

    return 0;
}
