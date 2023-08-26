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
        vector<int> polyCoefficients; // TODO shoud this be stored in the class or function?

        // x is the id, y is the share
        vector<Coordinate2D> shares; // TODO should this be saved for privacy reasons? Or should each be stored by the user?

        vector<Coordinate2D> inputtedShares;

        /// @brief solves the polynomial using the polyCoefficients vector
        /// @param x the number used to evaluate the polynomial
        /// @return int the given y value for the polynomial evaluated at x
        int solvePolynomialAtX(int x);

    public:
        /// @brief constructor for ShamirSecret
        /// @param secret the desired int to be hidden, must be positive 
        /// @param min minimum number of keys to decode secret
        /// @param max maxmimum number of keys to generate
        ShamirSecret(int secret, int min, int max) : secret(secret), minShares(min), maxShares(max) {} ;
        
        /// @brief fills the polyCoefficients vector and shares vector with their needed values 
        void makeSecretShares();

        /// @brief takes the inputted keys and attempts to reconstruct the secret
        /// @param shareID a vector of Coordinate2Ds that represent the id (x) and the given key (y)
        /// @return int return reconstruction of secret on success, return -1 on fail
        int secretReconstruct(const vector<Coordinate2D> shareID) const;

        /// @brief allows the class to wait for minShares inputs before running secretReconstruct (is not validated)
        /// @param id a Coordinate2D of a share made from makeSecretShares
        /// @return int -1 on incomplete number of shares or return secretReconstruct()
        int inputShare(const Coordinate2D id);

        /// @return Coordinate2D vector where the id is x and the given key is y
        vector<Coordinate2D> getShares() const { return shares; } // TODO remove for security
};

#endif SSS_HPP