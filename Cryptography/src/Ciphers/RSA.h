#pragma once
#include <bitset>
#include <random>
#include <future>
#include <deque>
#include <boost/integer/mod_inverse.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "Cipher.h"

using namespace boost::multiprecision;

struct RSAKey
{
    int1024_t priKey[2];
    int1024_t pubKey[2];
};

class RSA : public Cipher<RSAKey, std::string>
{
public:
	RSA();
    virtual std::string encrypt(const std::string& input) override;
    virtual std::string decrypt(const std::string& input) override;
    virtual std::string update(const std::string& input) override;
    virtual bool tryFindKey(const std::string& input) override
    {
        return false;
    }
    virtual const char* getName() override;
protected:
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;

private:
    int1024_t modulo(int1024_t a, int1024_t b, int1024_t n);
    static std::pair<int1024_t, int1024_t> findAB(int1024_t offset, int1024_t n, int1024_t a, bool& terminate);
    static bool isSquare(int1024_t x);
};

inline RSA::RSA()
	: Cipher(RSAKey())
{
}

inline std::string RSA::update(const std::string& input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string RSA::encrypt(const std::string& input)
{
	throw std::logic_error("Not implemented");
}

inline std::string RSA::decrypt(const std::string& input)
{
    m_CipherMode = MODE_DECRYPT;
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

    int valIdx{ 0 };
    std::vector<std::string> values(3);
    for (char letter : input)
    {
        if (letter == '\n')
        {
            break;
        }
        if (letter == ':')
        {
            ++valIdx;
            continue;
        }
        
        values[valIdx] += letter;
    }
    int1024_t n{ values[0] };
    int1024_t e{ values[1] };
    int1024_t y{ values[2] };

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

    std::string output{};
    output += "p = " + p.str() + '\n';
    output += "q = " + q.str() + '\n';

    int1024_t phi_n{ (p - 1) * (q - 1) };
    auto d = boost::integer::mod_inverse(e, phi_n);
    output += "Private key = " + d.str() + '\n';

    auto x{ modulo(y, d, n) };
    output += "Message = " + x.str() + '\n';

    return output;
}

inline char RSA::encryptingFormula(char letter)
{
	return 0;
}

inline char RSA::decryptingFormula(char letter)
{
	return 0;
}

inline const char* RSA::getName()
{
    return "RSA";
}

inline int1024_t RSA::modulo(int1024_t a, int1024_t b, int1024_t n) 
{
    int1024_t x = 1, y = a;
    while (b > 0) 
    {
        if (b % 2 == 1) 
        {
            x = (x * y) % n; // multiplying with base
        }
        y = (y * y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}

inline bool RSA::isSquare(int1024_t x)
{
    // Find floating point value of
    // square root of x.
    if (x >= 0) 
    {
        int1024_t sr = sqrt(x);

        // if product of square root
        //is equal, then
        // return T/F
        return (sr * sr == x);
    }
    // else return false if n<0
    return false;
}

inline std::pair<int1024_t, int1024_t> RSA::findAB(int1024_t offset, int1024_t n, int1024_t a, bool& terminate)
{
    int1024_t b;
    const int iter{ 10'000'000 };
    a += offset * iter;
    for (int i{ 0 }; i < iter; ++i)
    {
        if (terminate)
            break;
        auto b2 = a * a - n;
        if (isSquare(b2))
        {
            b = sqrt(b2);
            return { a, b };
        }
        ++a;
    }
    return { 0, 0 };
}

inline int256_t gcd(int256_t a, int256_t b)
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



inline uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
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

inline uint64_t powMod(uint64_t a, uint64_t b, uint64_t n) {
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

inline std::vector<int> first_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
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
inline uint64_t getRandom64() {
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

inline uint64_t getLowLevelPrime() {
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

inline bool trialComposite(uint64_t a, uint64_t evenC, uint64_t to_test, int max_div_2) {
    if (powMod(a, evenC, to_test) == 1)
        return false;

    for (int i = 0; i < max_div_2; i++) {
        uint64_t temp = static_cast<uint64_t>(1) << i;
        if (powMod(a, temp * evenC, to_test) == to_test - 1)
            return false;
    }

    return true;
}

inline bool MillerRabinTest(uint64_t to_test) {
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

inline uint64_t getBigPrime() {
    while (true) {
        uint64_t candidate = getLowLevelPrime();
        if (MillerRabinTest(candidate))
            return candidate;
    }
}