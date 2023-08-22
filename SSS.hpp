#include <vector>
#include "Coordiante2D.hpp"

using namespace std;



class ShamirSecret {
    private:
        int secret;
        int minimumShares;
        vector<int> polyCoefficients;

        // x is the id, y is the share
        vector<Coordinate2D> shares;

    public:
        ShamirSecret(int secret, int min) : secret(secret), minimumShares(min) {} ;

        // fills the shares vector with the 
        void MakeSecretShares();

        // find the y value at x = 0, i.e. the secret
        void LagrangeInterpolate();

        void SecretReconstruct();
    
};