#ifndef __LOCATION__
#define __LOCATION__

class Location {

    public:
        Location(int, int);
        ~Location() {};
        int getX();
        int getY();
        void setX(int);
        void setY(int);

    private:
        int x_;
        int y_;

};

#endif
