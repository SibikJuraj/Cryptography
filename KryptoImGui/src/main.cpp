#include <windows.h>
#include <debugapi.h>
#include <crtdbg.h>

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include <Text/TextLoader.h>
#include <Ciphers/Stream.h>
#include <Ciphers/Viegener.h>
#include <PwdAuth.h>
#include <random>
#include <bitset>

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

int256_t gcd(int256_t a, int256_t b)
{

    if ((a == 0) || (b == 0))
    {
        return 0;
    }

    int256_t q;
    int256_t r;

    do
    {
        q = a / b;
        r = a % b;

        a = b;
        b = r;
    } while (r != 0);

    return a;
}



uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    int64_t res = 0;

    while (a != 0) {
        if (a & 1) {

            res = (res + b) % m;
        }
        a >>= 1;
        b = (b << 1) % m;
    }
    return res;
}

uint64_t powMod(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t x = 1;

    a %= n;

    while (b > 0) {
        if (b % 2 == 1) {
            x = mulmod(x, a, n); // multiplying with base
        }
        a = mulmod(a, a, n); // squaring the base
        b >>= 1;
    }
    return x % n;
}

std::vector<int> first_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                                    31, 37, 41, 43, 47, 53, 59, 61, 67,
                                    71, 73, 79, 83, 89, 97, 101, 103,
                                    107, 109, 113, 127, 131, 137, 139,
                                    149, 151, 157, 163, 167, 173, 179,
                                    181, 191, 193, 197, 199, 211, 223,
                                    227, 229, 233, 239, 241, 251, 257,
                                    263, 269, 271, 277, 281, 283, 293,
                                    307, 311, 313, 317, 331, 337, 347, 349 };

// going through all 64 bits and placing randomly 0s and 1s
// setting first and last bit to 1 to get 64 odd number
uint64_t getRandom64() {
    // the value need to be 63 bits because you can not using 64 bit values do a^2 which is needed
    constexpr int bits = 63;
    std::bitset<bits> a;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<short> distr(0, 1);

    for (int i = 0; i < bits; i++) {
        a[i] = distr(gen);
    }

    a[0] = 1;
    a[bits - 1] = 1;

    return a.to_ullong();
}

uint64_t getLowLevelPrime() {
    while (true) {
        uint64_t candidate = getRandom64();
        bool is_prime = true;
        for (int i = 0; i < first_primes.size(); i++) {
            if (candidate == first_primes[i])
                return candidate;

            if (candidate % first_primes[i] == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            return candidate;
    }
}

bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
    if (powMod(a, evenC, to_test) == 1)
        return false;

    for (int i = 0; i < max_div_2; i++) {
        uint64_t temp = static_cast<uint64_t>(1) << i;
        if (powMod(a, temp * evenC, to_test) == to_test - 1)
            return false;
    }

    return true;
}

bool MillerRabinTest(uint64_t to_test) {
    constexpr int accuracy = 20;

    int max_div_2 = 0;
    uint64_t evenC = to_test - 1;
    while (evenC % 2 == 0) {
        evenC >>= 1;
        max_div_2++;
    }

    // random numbers init
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> distr(2, to_test);

    for (int i = 0; i < accuracy; i++) {
        uint64_t a = distr(gen);

        if (trialComposite(a, evenC, to_test, max_div_2)) {
            return false;
        }
    }

    return true;
}

uint64_t getBigPrime() {
    while (true) {
        uint64_t candidate = getLowLevelPrime();
        if (MillerRabinTest(candidate))
            return candidate;
    }
}

bool isSquare(int1024_t x)
{
    // Find floating point value of
    // square root of x.
    if (x >= 0) {

        int1024_t sr = sqrt(x);

        // if product of square root
        //is equal, then
        // return T/F
        return (sr * sr == x);
    }
    // else return false if n<0
    return false;
}

int1024_t xGCD(int1024_t a, int1024_t b, int1024_t& x, int1024_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int1024_t x1, y1;
    int1024_t gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int1024_t modInverse(int1024_t a, int1024_t n)
{
    int1024_t u, v;
    if (xGCD(a, n, u, v) == 1)
        return u % n;
    return 0;
}

std::pair<int1024_t, int1024_t> findAB(int1024_t offset, int1024_t n, int1024_t a, bool& terminate)
{
    int1024_t b;
    const int iter{ 10'000'000 };
    a += offset * iter;
    for (int i{ 0 }; i < iter;++i)
    {
        if (terminate)
            break;
        auto b2 = a * a - n;
        if (isSquare(b2))
        {
            b = sqrt(b2);
            return {a, b};
        }
        ++a;
    }
    return {0, 0};
}

int1024_t modulo(int1024_t a, int1024_t b, int1024_t n) {
    int1024_t x = 1, y = a;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y) % n; // multiplying with base
        }
        y = (y * y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    /*auto textVigenere{ TextLoader::loadText("texts/vigenere/text1_enc.txt") };
    auto decryptedTextVigenere{ Viegener().decrypt(textVigenere) };
    TextLoader::saveText("texts/vigenere/decoded/text1_dec.txt", decryptedTextVigenere);

    auto textStream{ TextLoader::loadText("texts/stream/text1_enc.txt") };
    auto decryptedTextStream{ Stream().decrypt(textStream) };
    TextLoader::saveText("texts/stream/decoded/text1_dec.txt", decryptedTextStream); */
    
    /* auto input{ TextLoader::loadText("texts/hill/text1_enc.txt") };
    arma::Mat<int> matA{ {3, 7, 20}, {17, 24, 17}, {0, 9, 0 } };*/
    
    /*TextLoader::saveText("texts/md5/decoded/shadow4_pwd.txt", 
        PwdAuth::decrypt(TextLoader::loadText("texts/md5/shadow4.txt")));*/

    /*int1024_t p{ getBigPrime() };
    int1024_t q{ getBigPrime() };
    int1024_t e{ 65'537 };

    int1024_t n{ p * q };
    int1024_t phi_n{ (p - 1) * (q - 1) };

    std::cout << p << " * " << q << " = " << n << '\n';
    std::cout << "GCD is " << gcd(e, phi_n) << '\n';*/

    std::deque<std::future<std::pair<int1024_t, int1024_t>>> fSL(50'000);

    int offset{ 0 };
    bool termL{ false };
    int1024_t n{ "16812615098258879" };
    int1024_t e{ 65537 };
    int1024_t y{ "1990249581724467" };

    int1024_t a = (int1024_t)sqrt(n) + 1;
    for (int i = offset; i < offset + fSL.size(); ++i)
    {
        fSL[i - offset] = std::async(std::launch::async, findAB, i, n, a, std::ref(termL));
    }
    std::pair<int1024_t, int1024_t> ab;
    while (fSL.size() > 0)
    {
        ab = fSL[0].get();
        if (ab.first != 0 && ab.second != 0)
        {
            termL = true;
            break;
        }
        fSL.pop_front();
    }
    fSL.clear();

    int1024_t p = ab.first + ab.second;
    int1024_t q = ab.first - ab.second;

    if (p*q == n)
        std::cout << p << " * " << q << " = " << n << '\n';

    int1024_t phi_n{ (p - 1) * (q - 1) };
    int1024_t d = modInverse(e, phi_n);
    std::cout << "Private key is: " << d << '\n';

    auto x{ modulo(y, d, n)};
    
    std::cout << "Message is: " << x;
    return 0;
}
