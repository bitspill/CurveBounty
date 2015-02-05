#include <iostream>
#include <cmath>
#include "uint256_t.h"

#define square(x) ((x)*(x))

using namespace std;

// https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse/

/* This function return the gcd of a and b followed by
    the pair x and y of equation ax + by = gcd(a,b)*/
uint256_t extendedEuclid_modified_onlyReturn_xLast(uint256_t a, uint256_t b) {
    uint256_t x = 1;
    uint256_t xLast = 0;
    uint256_t q, r, m;
    while (a != 0) {
        q = b / a;
        r = b % a;
        m = xLast - q * x;
        xLast = x;
        x = m;
        b = a, a = r;
    }
    return xLast;
}

uint256_t modInverse(uint256_t a, uint256_t m) {
    return (extendedEuclid_modified_onlyReturn_xLast(a, m) + m) % m;
}

// http://stackoverflow.com/questions/15224911/unsigned-long-long-int-pow
uint256_t ipow(uint256_t base, int exp) {
    uint256_t result = 1ULL;
    while (exp) {
        if (exp & 1) {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

int main() {

    // it's always 9
    uint256_t x0 = 9;
    // arbitrary 'a' - I took the constant from curve25519 for shits and giggles
    uint256_t a = 486662;
    // G chosen so result is found after 10240 tries
    // G = 83402281777707715381485212681368749158073214888176003645002923212220704930560 (broken down into chunks)
    uint256_t G = uint256_t(uint128_t(13286750047005568362ULL,13643317624181719600ULL),uint128_t(16667744255084313316ULL,3197251940288477952ULL));
    uint256_t m = ipow(2, 255) - 19; // prime used in curve25519

    uint256_t _i = 0;
    uint8_t statusCounter = 0;
    uint256_t x = x0;

    while (x != G) {
        // new_x = (x²-1)² / (4*x*(x²+a*x+1))
        x = square((square(x) - 1)) * modInverse(x * 4 * (square(x) + a * x + 1), m);
        ++_i;

        ++statusCounter;
        if (statusCounter == 0) {
            //cout << "x: " << x << endl;
            cout << "_i: " << _i << endl;
        }
    }

    cout << "-----------------------" << endl;
    cout << "Found Goal!" << endl;
    cout << "x: " << x << endl;
    cout << "_i: " << _i << endl;

    return 0;
}