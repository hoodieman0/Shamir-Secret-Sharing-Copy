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
        cout << pair << endl; // TODO remove debugging statements
    }
}

bool ShamirSecret::
secretReconstruct() {
    vector<Coordinate2D> sharesToUse; // TODO remove testing values
    vector<Fraction> piFracs;

    Fraction fracProduct (1, 1);
    Fraction sum (0, 1);

    int reconstruction;

    // testing values
    // TODO add inputs to function
    for (int i = 0; i < minShares; i++) {
        sharesToUse.push_back(shares[i]);
        cout << shares[i] << endl; // TODO remove debugging statements
    }

    // https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing#Computationally_efficient_approach
    // this page does not explain how it simplifies the equation, but it is still used here
    // accessed 24 Aug 2023
    for (int i = 0; i < minShares; i++) {
        for (int j = 0; j < minShares; j++) {

            // setup the fractions for multiplication, without 0/0 from x_i - x_i
            if (sharesToUse[i].getX() != sharesToUse[j].getX()){
                piFracs.push_back(Fraction(sharesToUse[j].getX(), sharesToUse[j].getX() - sharesToUse[i].getX()));
            }
        }
        // multiply the series of fractions
        for ( Fraction f : piFracs) {
            fracProduct = fracProduct * f;
        }

        // multiply y_i by fracProduct, add it to the sum, and repeat for all i
        sum = sum + (fracProduct * sharesToUse[i].getY());

        // clear for new values
        piFracs.clear();
        fracProduct = Fraction(1, 1);
    }
    
    reconstruction = sum.getNumerator() / sum.getDenominator();

    if (reconstruction == secret) return true;
    return false;
}