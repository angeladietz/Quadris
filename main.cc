#include <iostream>
#include <cstdlib>
#include <time.h>
#include "quadris.h"

int main(int argc, char* argv[]) {

    bool didSetSeed = false;

    // Define default Quadris parameters
    bool textOnly = false;
    int startLevel = 0;
    std::string scriptFile = "sequence.txt";

	if (argc > 1){
        for (int i = 1; i < argc; i++){
            if ("-text" == argv[i]){
                textOnly = true;
            }
            else if ("-seed" == argv[i] && i < argc-1){
                int seed = std::stoi(argv[++i]);
                std::srand(seed);
                didSetSeed = true;
            }
            else if ("-scriptfile" == argv[i] && i < argc-1){
                scriptFile = argv[++i];
            }
            else if ("-startlevel" == argv[i] && i < argc-1){
                startLevel = std::stoi(argv[++i]);
            }
        }
	}

    if (!didSetSeed){
        std::srand(time(NULL));
    }
    
    Quadris* quadris = new Quadris(textOnly, startLevel, scriptFile);
    quadris->playGame();
    delete quadris;

    return 0;
}