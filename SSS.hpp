#ifndef SSS_HPP
#define SSS_HPP

#include <vector>
#include <random>
#include <iostream>
#include <cmath>

#include "MathNotation.hpp"
#include "Exceptions.hpp"

using namespace std;



class ShamirSecret {
    private:
        int secret;
        int minShares;
        int maxShares;

        // starts with degree 0, ends with degree minShares
        vector<int> polyCoefficients;

        // x is the id, y is the share
        vector<Coordinate2D> shares;

        int solvePolynomialAtX(int x);

    public:
        ShamirSecret(int secret, int min, int max) : secret(secret), minShares(min), maxShares(max) {} ;

        // fills the polyCoefficients vector and shares vector with their needed values 
        void makeSecretShares();

        // find the y value at x = 0, i.e. the secret
        bool secretReconstruct(const vector<Coordinate2D> shareID) const;

        vector<Coordinate2D> getShares() const { return shares; }
};

#endif SSS_HPP