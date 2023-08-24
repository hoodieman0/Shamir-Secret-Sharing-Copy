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
   return out << "(" << coord.getX() << ", " << coord.getY() << ")";
}

struct Fraction {
    private:
        int numerator;
        int denominator;

    public:
        Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
        int getNumerator() { return numerator; }
        int getDenominator() { return denominator; }
};

inline ostream& operator<<(ostream& out, Fraction& frac) {
   return out << frac.getNumerator() << " / " << frac.getDenominator();
}