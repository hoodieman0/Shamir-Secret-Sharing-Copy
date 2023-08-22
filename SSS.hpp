#include <vector>

using namespace std;

struct Coordinate2D {
    private:
        int x;
        int y;

    public:
        Coordinate2D(int x, int y) : x(x), y(y) {}
        int getX() { return x; }
        int getY() { return y; }
};

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