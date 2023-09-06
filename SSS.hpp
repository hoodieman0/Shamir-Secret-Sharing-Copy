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
        int prime;

        bool hasShares = false;

        vector<Coordinate2D> inputtedShares;

        /// @brief solves the polynomial using the polyCoefficients vector
        /// @param x the number used to evaluate the polynomial
        /// @param polyCoefficients the vector containing the polynomial coefficients from least to greatest degree (ex: 5 + 7x + 10x^2)
        /// @return int the given y value for the polynomial evaluated at x
        int solvePolynomialAtX(const int x, const vector<int> polyCoefficients) const;

        /// @brief cacluates the modular inverse of a number
        /// @param number the number to find the inverse of
        /// @param modulo the modulo factor to use for the inverse
        /// @return int the modular inverse of number using modulo 
        int modularInverse(const int number, const int modulo) const;

    public:
        /// @brief constructor for ShamirSecret
        /// @param secret the desired int to be hidden, must be positive 
        /// @param min minimum number of keys to decode secret
        /// @param max maxmimum number of keys to generate
        /// @param prime finite field to use, default is 2^19 - 1 (7th Mersenne Prime)
        ShamirSecret(int secret, int min, int max, int prime=((int) pow(2, 19)) - 1) : secret(secret), minShares(min), maxShares(max), prime(prime) {
            if (secret > prime) throw IncalculableSecretException();
            if (min < 1 || max < 1 || max < min) throw InvalidParameterException();
        } 
        

        /// @brief creates the secret shares to be used in secretReconstruct(), can be run only once
        /// @details the caller must ensure that these secret shares are secure, as they cannot be regenerated
        /// @return a vector of Coordiante2Ds, where x is the id and y is the random polynomial at x. Returns empty vector if already run before
        vector<Coordinate2D> makeSecretShares();

        /// @brief takes the inputted keys and attempts to reconstruct the secret
        /// @param shareID a vector of Coordinate2Ds that represent the id (x) and the given key (y)
        /// @return int return reconstruction of secret on success, return -1 on fail
        int secretReconstruct(const vector<Coordinate2D> shareID) const;

        /// @brief allows the class to wait for minShares inputs before running secretReconstruct (is not validated)
        /// @param id a Coordinate2D of a share made from makeSecretShares
        /// @return int -1 on incomplete number of shares or return secretReconstruct()
        int inputShare(const Coordinate2D id);
};

#endif SSS_HPP