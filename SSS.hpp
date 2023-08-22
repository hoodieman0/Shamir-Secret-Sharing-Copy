#include <vector>
#include <random>
#include <iostream>
#include <cmath>

#include "Coordiante2D.hpp"

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

        // fills the shares vector with the 
        void makeSecretShares();

        // find the y value at x = 0, i.e. the secret
        void lagrangeInterpolate();

        void secretReconstruct();
};