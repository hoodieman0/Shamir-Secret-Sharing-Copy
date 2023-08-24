#ifndef UTEST_HPP
#define UTEST_HPP

#include <iostream>
#include <vector>
#include "SSS.hpp"
#include "MathNotation.hpp"

#define SECRET 1337
#define MINSHARES 3
#define MAXSHARES 5

using namespace std;

int UnitTest_ClassCreation() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
    } catch(...) { return 1; }

    return 0;
}

int UnitTest_MakeSecretShares(){
    try { 
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        handler.makeSecretShares();
    } catch (...) { return 1; }

    return 0;
}

int UnitTest_ReconstructSecret() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        handler.makeSecretShares();

        vector<Coordinate2D> handlerShares = handler.getShares();


        bool isSuccess = handler.secretReconstruct(handlerShares);

        if (!isSuccess) throw "Secret Failed to reconstruct";
    } catch (...) { return 1; }
    
    return 0;
}

int UnitTest_RunAll(){
    int passed = 0;
    int failed = 0;

    cout << "Running all unit tests for Shamir Secret Sharing class" << endl;
    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - ClassCreation..." << endl;
    if (UnitTest_ClassCreation()) { cout << "Unit Test - Class Creation -> Failed Test" << endl; failed++;}
    else { cout << "Unit Test - Class Creation -> Passed Test" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - MakeSecretShares..." << endl;
    if (UnitTest_MakeSecretShares()) { cout << "Unit Test - MakeSecretShares -> Failed Test" << endl; failed++; }
    else { cout << "Unit Test - MakeSecretShares -> Passed Test" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - ReconstructSecret..." << endl;
    if (UnitTest_ReconstructSecret()) { cout << "Unit Test - ReconstructSecret -> Failed Test" << endl; failed++; }
    else { cout << "Unit Test - ReconstructSecret -> Passed Test" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    cout << "Finished running all tests" << endl;
    cout << "Passed Tests: " << passed << endl;
    cout << "Failed Tests: " << failed << endl;

    return 0;
}

#endif UTEST_HPP