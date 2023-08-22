#include "SSS.hpp"

int ShamirSecret::
solvePolynomialAtX(int x) {
    int result = 0;
    int exponent = 0;
    int var = 0;

    for (int coeff : polyCoefficients) {
        var = int(pow(x, exponent));
        exponent++;
        result += coeff * var;
    }

    return result;
}

void ShamirSecret::
makeSecretShares() {

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist100(1,100);

    // input the degree 0 polynomial
    polyCoefficients.push_back(secret);

    for (int i = 0; i < minShares - 1; i++) {
        polyCoefficients.push_back(dist100(rng));
    }

    for (int x = 1; x <= maxShares; x++) {
        shares.push_back(Coordinate2D (x, solvePolynomialAtX(x)));
        
    }

    for (Coordinate2D pair : shares) {
        cout << pair << endl;
    }
    
}