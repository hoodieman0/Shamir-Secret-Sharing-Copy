/**
 * @file Exceptions.hpp
 * @author James Mok (jmok780@gmail.com)
 * @brief Definitions of all custom exceptions
 * @version 1.0.0
 * @date 2023-08-24
 */

#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <string>
#include <iostream>

using namespace std;

// look into stringstreams for use in std::exception::what()
class GeneralException : public exception {
    protected:
        string title = "General Exception";
        string detail = "A generic exception";
        int code = 100;

    public:
        GeneralException()=default;
        GeneralException(string detail) : detail(detail) {}
        virtual ostream& print(ostream& out) const;
};

inline ostream& operator<<(ostream& out, const GeneralException& e) {
    return e.print(out);
}


class InsufficientKeysException : public GeneralException {
    protected:
        string title = "Insufficient Keys Exception";
        string detail = "An incorrect amount of keys was inputted to satisfy reconstruction";
        int code = 101;
        int input, min = 0;

    public:
        InsufficientKeysException()=default;
        InsufficientKeysException(int input, int min) : input(input), min(min) {}
        virtual ostream& print(ostream& out) const;
};

class SecretDoesNotMatchException : public GeneralException {
    protected:
        string title = "Calculated Secret Does Not Match Exception";
        string detail = "ShamirSecret.secretReconstruct() failed to calculate the original secret";
        int code = 102;

    public:
        SecretDoesNotMatchException()=default;
        virtual ostream& print(ostream& out) const;
};

class GenerateTwoShareSetsException : public GeneralException {
    protected:
        string title = "Generated Two Sets of Shares";
        string detail = "ShamirSecret.makeSecretShares() was run more than once";
        int code = 103;

    public:
        GenerateTwoShareSetsException()=default;
        virtual ostream& print(ostream& out) const;
};


#endif EXCEPT_HPP