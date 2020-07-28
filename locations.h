#ifndef __LOCATION__
#define __LOCATION__

class Location {

    public:
        int x_;
        int y_;

    private:
        Location();
        ~Location();
        int getX();
        int getY();
        void setX(int);
        void setY(int);

};

#endif
