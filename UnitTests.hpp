/**
 * @file UnitTests.hpp
 * @author James Mok (jmok780@gmail.com)
 * @brief A file to hold all unit tests
 * @version 1.0.0
 * @date 2023-08-24
 */

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

/*
\u2713 is a check mark
\u274c is a cross mark
\u2bd1 is a question mark
*/

/**
 * @brief check if the ShamirSecret class constructs properly
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_ClassCreation() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
    } 
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
}

/**
 * @brief using the ShamirSecret class, test if makeSecretShares() runs without error
 * 
 * @return int 0 on pass, 1 on fail
 */
int UnitTest_MakeSecretShares(){
    try { 
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();

        cout << "Generated Shares: " << endl;
        for (Coordinate2D s : shares) {
            cout << s << endl;
        }
    }  
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
}

/**
 * @brief using the ShamirSecret class, test if makeSecretShares only returns values on first run
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_GenerateSharesTwice() {
        try { 
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        // first call
        vector<Coordinate2D> shares = handler.makeSecretShares();
        if (shares.empty()) throw EmptyShareSetException();

        // second call
        shares = handler.makeSecretShares();
        if (!shares.empty()) throw GenerateTwoShareSetsException();
    }  
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
}

/**
 * @brief using the ShamirSecret class, test if secretReconstruct() succeeds
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_ReconstructSecret() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();

        int reconstruction = handler.secretReconstruct(shares);

        if (reconstruction != SECRET) throw SecretDoesNotMatchException();
    } 
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }
    
    return 0;
}

/**
 * @brief using the ShamirSecret class, call secretReconstruct() with less than MINSHARES keys
 * @details if an exception is thrown, the test passes
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_ReconstructWithTooFewKeys() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();
        
        // remove all but one share
        for (int i = 0; i < MAXSHARES - 1; i++) shares.pop_back();
        
        handler.secretReconstruct(shares);
    }
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 1; }

    return 1;
}

/**
 * @brief run all possible unit tests
 * 
 * @return int 0 on finish 
 */
int UnitTest_RunAll(){
    int passed = 0;
    int failed = 0;

    cout << "Running all unit tests for Shamir Secret Sharing class" << endl;
    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - ClassCreation..." << endl;
    if (UnitTest_ClassCreation()) { cout << "Unit Test - Class Creation -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - Class Creation -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - MakeSecretShares..." << endl;
    if (UnitTest_MakeSecretShares()) { cout << "Unit Test - MakeSecretShares -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - MakeSecretShares -> Passed Test \u2713" << endl; passed++; }

     cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - GenerateSharesTwice()..." << endl;
    if (UnitTest_GenerateSharesTwice()) { cout << "Unit Test - GenerateSharesTwice -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - GenerateSharesTwice -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - ReconstructSecret..." << endl;
    if (UnitTest_ReconstructSecret()) { cout << "Unit Test - ReconstructSecret -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - ReconstructSecret -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - ReconstructWithTooFewKeys..." << endl;
    if (UnitTest_ReconstructWithTooFewKeys()) { cout << "Unit Test - ReconstructWithTooFewKeys -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - ReconstructWithTooFewKeys -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    cout << "Finished running all tests" << endl;
    cout << "\u2713 Passed Tests: " << passed << endl;
    cout << "\u274c Failed Tests: " << failed << endl;

    return 0;
}

#endif UTEST_HPP