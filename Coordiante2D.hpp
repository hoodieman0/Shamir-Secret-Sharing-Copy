#include <iostream>

using namespace std;

struct Coordinate2D {
    private:
        int x;
        int y;

    public:
        Coordinate2D(int x, int y) : x(x), y(y) {}
        int getX() { return x; }
        int getY() { return y; }
};

inline ostream& operator<<(ostream& out, Coordinate2D& coord) {
   return out << "(" << coord.getX() << ", " << coord.getY() << ")" << endl;
}