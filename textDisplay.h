#ifndef _TEXTDISPLAY_
#define _TEXTDISPLAY_

#include "observer.h"

class TextDisplay: public Observer {
    public:
        TextDisplay();
        ~TextDisplay();
        void update();
};

#endif
