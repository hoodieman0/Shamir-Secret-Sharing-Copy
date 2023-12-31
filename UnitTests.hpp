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
#define PRIME 524287 // 7th Mersenne Prime, optional argument

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
        cout << "The ShamirSecret class was created" << endl;
    } 
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
}

/**
 * @brief check if the ShamirSecret class doesn't construct if secret > prime
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_CreateImproperClass() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES, SECRET - 1);
        cout << "The ShamirSecret class was created" << endl;
    } 
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 0; }

    return 1;
}

/**
 * @brief check if the ShamirSecret class doesn't construct minShares > maxShares
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_SwitchMaxMinShares() {
    try {
        ShamirSecret handler(SECRET, MAXSHARES, MINSHARES);
        cout << "The ShamirSecret class was created" << endl;
    } 
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 0; }

    return 1;
}

/**
 * @brief check if the ShamirSecret class doesn't construct if minShares < 1
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_WrongMinShare() {
    try {
        ShamirSecret handler(SECRET, 0, MAXSHARES);
        cout << "The ShamirSecret class was created" << endl;
    } 
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 0; }

    return 1;
}

/**
 * @brief check if the ShamirSecret class doesn't construct if maxShares < 1
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_WrongMaxShare() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, 0);
        cout << "The ShamirSecret class was created" << endl;
    } 
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 0; }

    return 1;
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

        if (shares.empty()) throw EmptyShareSetException();

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

        cout << "The size of shares is: " << shares.size() << endl;
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

        cout << "The final reconstruction is: " << reconstruction << endl;

        if (reconstruction != SECRET) throw SecretDoesNotMatchException();
    } 
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }
    
    return 0;
}

/**
 * @brief using the ShamirSecret class, test if secretReconstruct() succeeds 10,000 times with random valid shares
 * 
 * @return int 0 on pass, 1 on fail 
 */
int UnitTest_ReconstructSeveral(){
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();
        vector<Coordinate2D> copy = shares;

        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> distMAX(0, shares.size());
        
        cout << "Running ShamirSecret.reconstructShares() 10,000 times..." << endl;

        for(int j = 0; j < 10000; j++) {
            // remove enough elements to meet the minumum
            for (int i = 0; i < (MAXSHARES - MINSHARES); i++){
                copy.erase(copy.begin()+(distMAX(rng) % copy.size()));
            }

            int result;
            result = handler.secretReconstruct(copy);

            if (result != SECRET) throw SecretDoesNotMatchException();

            copy = shares;
        }
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
        
        int result = handler.secretReconstruct(shares);
        cout << "The final reconstruction is: " << result << endl;
    }
    catch(GeneralException& e) { cout << e << endl; return 0; }
    catch(exception& e) { cout << e.what() << endl; return 0; }
    catch(...) { return 1; }

    return 1;
}

/**
 * @brief using the ShamirSecret class, call inputShare() and deteremine if it takes minShare keys to get the secret
 * 
 * @return int 0 on pass, 1 on fail  
 */
int UnitTest_InputShares() {
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();

        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> distMAX(0, shares.size());

        // remove enough elements to meet the minumum
        for (int i = 0; i < (MAXSHARES - MINSHARES); i++){
            shares.erase(shares.begin()+(distMAX(rng) % shares.size()));
        }

        int result;
        for (int i = 0; i < MINSHARES; i++){
            result = handler.inputShare(shares[i]);
            cout << "Result of pass " << i+1 << ": " << result << endl;
        }

        if (result != SECRET) throw SecretDoesNotMatchException();
    }
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }
    
    return 0;
}

// could be more exhaustive
/**
 * @brief using the ShamirSecret class, test if the secret is not given if there are wrong inputs 
 * 
 * @return int 0 on pass, 1 on fail  
 */
int UnitTest_BadInputs(){
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();
        
        vector<Coordinate2D> badShares;
        for (int i = 0; i < MINSHARES; i++){
            badShares.push_back(Coordinate2D(i, i)); // assuming that (1,1), (2,2), ... are not valid
        }
        
        int result = handler.secretReconstruct(badShares);
        cout << "The final reconstruction is: " << result << endl;
        if (result != -1) throw UnexpectedResultException(-1, result);
    }
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
}

/**
 * @brief  using the ShamirSecret class, test if the secret is not given if the same input is given 
 * 
 * @return int 0 on pass, 1 on fail   
 */
int UnitTest_SameInputs(){
    try {
        ShamirSecret handler(SECRET, MINSHARES, MAXSHARES);
        vector<Coordinate2D> shares = handler.makeSecretShares();
            
        int result;
        for (int i = 0; i < MINSHARES; i++){
            result = handler.inputShare(shares[0]);
            cout << "Result of pass " << i+1 << ": " << result << endl;
        }
        if (result != -1) throw UnexpectedResultException(-1, result);
    }
    catch(GeneralException& e) { cout << e << endl; return 1; }
    catch(exception& e) { cout << e.what() << endl; return 1; }
    catch(...) { return 1; }

    return 0;
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
    cout << "Testing Secret: " << SECRET << endl;
    cout << "Minimum Amount of Shares To Unlock: " << MINSHARES << endl;
    cout << "Maximum Amount of Shares to Generate: " << MAXSHARES << endl;
    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - ClassCreation..." << endl;
    if (UnitTest_ClassCreation()) { cout << "Unit Test - ClassCreation -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - ClassCreation -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - CreateImproperClass..." << endl;
    if (UnitTest_CreateImproperClass()) { cout << "Unit Test - CreateImproperClass -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - CreateImproperClass -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - WrongMaxShare..." << endl;
    if (UnitTest_WrongMaxShare()) { cout << "Unit Test - WrongMaxShare -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - WrongMaxShare -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - WrongMinShare..." << endl;
    if (UnitTest_WrongMinShare()) { cout << "Unit Test - WrongMinShare -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - WrongMinShare -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - SwitchMaxMinShares..." << endl;
    if (UnitTest_SwitchMaxMinShares()) { cout << "Unit Test - SwitchMaxMinShares -> Failed Test \u274c" << endl; failed++;}
    else { cout << "Unit Test - SwitchMaxMinShares -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - MakeSecretShares..." << endl;
    if (UnitTest_MakeSecretShares()) { cout << "Unit Test - MakeSecretShares -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - MakeSecretShares -> Passed Test \u2713" << endl; passed++; }

     cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - GenerateSharesTwice..." << endl;
    if (UnitTest_GenerateSharesTwice()) { cout << "Unit Test - GenerateSharesTwice -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - GenerateSharesTwice -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - ReconstructSecret..." << endl;
    if (UnitTest_ReconstructSecret()) { cout << "Unit Test - ReconstructSecret -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - ReconstructSecret -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - ReconstructSeveral..." << endl;
    if (UnitTest_ReconstructSeveral()) { cout << "Unit Test - ReconstructSeveral -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - ReconstructSeveral -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    
    cout << "Running Unit Test - ReconstructWithTooFewKeys..." << endl;
    if (UnitTest_ReconstructWithTooFewKeys()) { cout << "Unit Test - ReconstructWithTooFewKeys -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - ReconstructWithTooFewKeys -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - InputShares..." << endl;
    if (UnitTest_InputShares()) { cout << "Unit Test - InputShares -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - InputShares -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - BadInputs..." << endl;
    if (UnitTest_BadInputs()) { cout << "Unit Test - BadInputs -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - BadInputs -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;

    cout << "Running Unit Test - SameInputs..." << endl;
    if (UnitTest_SameInputs()) { cout << "Unit Test - SameInputs -> Failed Test \u274c" << endl; failed++; }
    else { cout << "Unit Test - SameInputs -> Passed Test \u2713" << endl; passed++; }

    cout << "------------------------------------------------------" << endl;
    cout << "Finished running all tests" << endl;
    cout << "\u2713 Passed Tests: " << passed << endl;
    cout << "\u274c Failed Tests: " << failed << endl;

    return 0;
}

#endif UTEST_HPP