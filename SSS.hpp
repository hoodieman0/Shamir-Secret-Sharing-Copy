/**
 * @file SSS.hpp
 * @author James Mok (jmok780@gmail.com)
 * @brief The header file for the ShamirSecret class
 * @version 1.0.0
 * @date 2023-08-24
 */

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

        /// @brief solves the polynomial using the polyCoefficients vector
        /// @param x the number used to evaluate the polynomial
        /// @return int the given y value for the polynomial evaluated at x
        int solvePolynomialAtX(int x);

    public:
        /// @brief constructor for ShamirSecret
        /// @param secret the desired int to be hidden 
        /// @param min minimum number of keys to decode secret
        /// @param max maxmimum number of keys to generate
        ShamirSecret(int secret, int min, int max) : secret(secret), minShares(min), maxShares(max) {} ;
        
        /// @brief fills the polyCoefficients vector and shares vector with their needed values 
        void makeSecretShares();

        /// @brief takes the inputted keys and attempts to reconstruct the secret
        /// @param shareID a vector of Coordinate2Ds that represent the id (x) and the given key (y)
        /// @return bool true on successful reconstruction, false if unsuccessful
        bool secretReconstruct(const vector<Coordinate2D> shareID) const;

        /// @return Coordinate2D vector where the id is x and the given key is y
        vector<Coordinate2D> getShares() const { return shares; }
};

#endif SSS_HPP