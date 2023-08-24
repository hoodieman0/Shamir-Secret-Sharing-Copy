#ifndef MATHNOT_HPP
#define MATHNOT_HPP

#include <iostream>

using namespace std;

struct Coordinate2D {
    private:
        int x;
        int y;

    public:
        Coordinate2D(int x, int y) : x(x), y(y) {}
        int getX() const { return x; }
        int getY() const { return y; }
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
        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }

        Fraction operator+ (Fraction f) {
            Fraction temp((numerator * f.getDenominator()) + (denominator * f.getNumerator()), denominator * f.getDenominator());
            return temp;
        }

        Fraction operator* (Fraction f) {
            Fraction temp(numerator * f.getNumerator(), denominator * f.getDenominator());
            return temp;
        }

        Fraction operator* (int x) {
            Fraction temp(numerator * x, denominator);
            return temp;
        }

};

inline ostream& operator<<(ostream& out, Fraction& frac) {
   return out << frac.getNumerator() << " / " << frac.getDenominator();
}

#endif MATHNOT_HPP