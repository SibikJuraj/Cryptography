#pragma once

#include <Ciphers/Cipher.h>

#include <string>
#include <string_view>
#include <vector>
#include <future>
#include <Ciphers/Class MD5/md5.h>
#include <Text/TextLoader.h>
#include <deque>

const std::string c_Lower = "abcdefghijklmnopqrstuvwxyz";
const std::string c_Alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

struct PwdAuthKey
{};


class PwdAuth : public Cipher<PwdAuthKey>
{
public:
    PwdAuth();
    virtual std::string encrypt(const std::string_view input) override;
    virtual std::string decrypt(const std::string_view input) override;
    virtual std::string update(const std::string_view input) override;
    virtual const char* getName() override;
protected:
    virtual char encryptingFormula(char letter) override;
    virtual char decryptingFormula(char letter) override;

private:
    struct User
    {
        std::vector<std::string> data;
    };

    static std::string crypt(const std::string& passwd, const std::string& salt)
    {
        return MD5(passwd + salt).tostring();
    }

    static std::string genRandom(int length, bool lower)
    {
        std::string tmp_s;
        tmp_s.reserve(length);

        for (int i = 0; i < length; ++i) {
            if (lower)
                tmp_s += c_Lower[rand() % (c_Lower.size())];
            else
                tmp_s += c_Alphanum[rand() % (c_Alphanum.size())];
        }

        return tmp_s;
    }

    static std::string randomRun(const std::vector<User>& users, int seed, bool lower, bool& terminate)
    {
        srand(time(NULL));
        for (int i{ 0 }; i < 2'000; ++i)
        {
            if (terminate)
                break;
            std::string pwd7{ lower ? genRandom(7, lower) : genRandom(5, lower) };
            std::string pwd6{ pwd7.substr(0, pwd7.size() - 1) };
            for (User u : users)
            {
                auto c7{ crypt(pwd7, u.data[1]) };
                auto c6{ crypt(pwd6, u.data[1]) };
                if (u.data[2] == c6)
                {
                    return "User: " + u.data[0] + " | Password: " + pwd6 +
                        " | Generator seed: " + std::to_string(seed) + '\n';
                }
                if (u.data[2] == c7)
                {
                    return "User: " + u.data[0] + " | Password: " + pwd7 +
                        " | Generator seed: " + std::to_string(seed) + '\n';
                }
            }
        }
        return {};
    }

    
};

inline PwdAuth::PwdAuth()
    : Cipher(PwdAuthKey())
{
}

inline std::string PwdAuth::update(const std::string_view input)
{
    return m_CipherMode == MODE_DECRYPT ? decrypt(input) : encrypt(input);
}

inline std::string PwdAuth::encrypt(const std::string_view input)
{
    throw std::logic_error("Not implemented");
}

inline std::string PwdAuth::decrypt(const std::string_view input)
{
    std::vector<std::string> values(3);
    int valIdx{ 0 };
    std::vector<User> users;
    for (char letter : input)
    {
        if (letter == ':')
        {
            ++valIdx;
            continue;
        }
        if (letter == '\n')
        {
            values[valIdx].pop_back();
            User user{ values };
            users.push_back(user);
            for (auto& vals : values)
                vals.clear();
            valIdx = 0;
            continue;
        }
        values[valIdx] += letter;
    }
    User user{ values };
    users.push_back(user);

    auto sk_names{ TextLoader::loadText("texts/md5/sk_names.txt") };
    std::vector<std::string> names{};
    size_t pos = 0;
    while ((pos = sk_names.find(',')) != std::string::npos) {
        names.push_back(sk_names.substr(0, pos));
        sk_names.erase(0, pos + 1);
    }
    //MENA
    std::string output{};

    for (User u : users)
    {
        for (int i{ 0 }; i <= 10; ++i)
        {
            for (auto& pwd : names)
            {
                auto c{ crypt(pwd, u.data[1]) };
                if (u.data[2] == c)
                {
                    output += "User: " + u.data[0] + " | Password: " + pwd + '\n';
                }
                if (i < pwd.size())
                {
                    pwd[i] = toupper(pwd[i]);
                    if (i > 0)
                        pwd[i - 1] = tolower(pwd[i - 1]);
                }
                if (i == pwd.size())
                    pwd[i - 1] = tolower(pwd[i - 1]);
            }
        }
    }

    std::string pwd{ "aaaaaaa" };
    std::string lastPwd{ "aaaaaaa" };

    std::deque<std::future<std::string>> fSL(10'000);
    //std::deque<std::future<std::string>> fSA(10'000);

    int offset{ 50'000 };
    bool termL{ false };
    bool termA{ false };
    for (int i = offset; i < offset + fSL.size(); ++i)
    {
        fSL[i - offset] = std::async(std::launch::async, randomRun, users, i, true, std::ref(termL));
        //fSA[i - offset] = std::async(std::launch::async, randomRun, users, i, false, std::ref(termA));
    }
    while (fSL.size() > 0 /*|| fSA.size() > 0*/)
    {
        std::string o;

        if (fSL.size() > 0)
        {
            o = fSL[0].get();
            if (o != "")
            {
                output += o;
                termL = true;

            }
            fSL.pop_front();
        }
        /*if (fSA.size() > 0)
        {
            o = fSA[0].get();
            if (o != "")
            {
                output += o;
                termA = true;
            }
            fSA.pop_front();
        }*/
    }
    return output;
}

inline char PwdAuth::encryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline char PwdAuth::decryptingFormula(char letter)
{
    throw std::logic_error("Not implemented");
}

inline const char* PwdAuth::getName()
{
    return "md5";
}
