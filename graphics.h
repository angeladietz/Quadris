#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "observer.h"

class Graphics: public Observer {
    public:
        Graphics();
        ~Graphics();
        void update();
};

#endif
