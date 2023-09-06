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

        int gcd(int a, int b) {
            if (a == 0) return b;
            else if (b == 0) return a;
            int q, r;

            while (b != 0){
                q = a / b;
                r = a % b;
                
                a = b;
                b = r;
            }

            return a;
        }

    public:
        Fraction(int numerator, int denominator) : numerator(numerator) { if (denominator == 0) throw "Denominator can't be 0!"; else this->denominator = denominator; }
        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }

        void reduce() {
            if (numerator == 0) return;
            if (numerator == denominator) {
                numerator = 1;
                denominator = 1;
            }
            if (numerator < 0 && denominator < 0){
                numerator *= -1;
                denominator *= -1;
            }

            int divisor = gcd(numerator, denominator);

            numerator /= divisor;
            denominator /= divisor;
        }

        Fraction operator+ (Fraction f) {
            Fraction temp((numerator * f.getDenominator()) + (denominator * f.getNumerator()), denominator * f.getDenominator());
            temp.reduce();
            return temp;
        }

        Fraction operator* (Fraction f) {
            Fraction temp(numerator * f.getNumerator(), denominator * f.getDenominator());
            temp.reduce();
            return temp;
        }

        Fraction operator* (int x) {
            Fraction temp(numerator * x, denominator);
            temp.reduce();
            return temp;
        }

};

inline ostream& operator<<(ostream& out, Fraction& frac) {
   return out << frac.getNumerator() << " / " << frac.getDenominator();
}

#endif MATHNOT_HPP