#include <windows.h>
#include <debugapi.h>
#include <crtdbg.h>

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <future>

#include <Text/TextLoader.h>
#include <Ciphers/Stream.h>
#include <Ciphers/Viegener.h>

#include "Ciphers/Class MD5/md5.h"
#include <deque>

struct User
{
    std::vector<std::string> data;
};

std::string crypt(const std::string& passwd, const std::string& salt)
{
    return MD5(passwd + salt).tostring();
}

std::string gen_random_lower(const int len) {
    static const char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alpha[rand() % (sizeof(alpha) - 1)];
    }

    return tmp_s;
}

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

std::string randomRun(const std::vector<User>& users, int seed, bool lower, bool& terminate)
{
    srand(seed);
    for (int i{ 0 }; i < 1'000; ++i)
    {
        if (terminate)
            break;
        std::string pwd7{ lower ? gen_random_lower(7) : gen_random(5)};
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


bool run(const std::vector<User>& users, std::string& pwd, std::string_view nextPwd, int idx)
{
    for (char c{ pwd[idx] }; c < 'a' + 26; ++c)
    {
        pwd[idx] = c;
        if (idx != 0)
            run(users, pwd, nextPwd, idx - 1);

        if (pwd == nextPwd)
            return true;

        for (User u : users)
        {
            auto tmpPwd7{ crypt(pwd, u.data[1]) };
            auto tmpPwd6{ crypt(pwd.substr(0, pwd.size() - 1), u.data[1]) };
            if (u.data[2] == tmpPwd6)
            {
                std::cout << "User: " + u.data[0] + " | Password: " + pwd.substr(0, pwd.size() - 1) + '\n';
                //TextLoader::saveText("texts/md5/passwd.txt", "User: " + u.data[0] + " Password: " + pwd.substr(0, pwd.size() - 1));
                return true;
            }
            if (u.data[2] == tmpPwd7)
            {
                std::cout << "User: " + u.data[0] + " | Password: " + pwd + '\n';
                //TextLoader::saveText("texts/md5/passwd.txt", "User: " + u.data[0] + " Password: " + pwd);
                return true;
            }
        }
    }
    pwd[idx] = 'a';
    return true;
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

    auto textMd5{ TextLoader::loadText("texts/md5/shadow4.txt") };

    std::vector<User> users{ };
    std::vector<std::string> values(3);
    int valIdx{ 0 };

    for (char letter: textMd5)
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
                    goto _end_;
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
    
_end_:

    std::string pwd{ "aaaaaaa" };
    std::string lastPwd{ "aaaaaaa" };

    std::deque<std::future<std::string>> fSL(5'000);
    std::deque<std::future<std::string>> fSA(5'000);

    int offset{ 0 };
    bool termL{ false };
    bool termA{ false };
    for (int i = offset; i < offset + fSL.size(); ++i)
    {
        fSL[i - offset] = std::async(std::launch::async, randomRun, users, i, true, std::ref(termL));
        fSA[i - offset] = std::async(std::launch::async, randomRun, users, i, false, std::ref(termA));
    }
    while (fSL.size() > 0 || fSA.size() > 0)
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
        if (fSA.size() > 0)
        {
            o = fSA[0].get();
            if (o != "")
            {
                output += o;
                termA = true;
            }
            fSA.pop_front();
        }
    }

    TextLoader::saveText("texts/md5/decoded/shadow4_pwd.txt", output);

    /*for (char c{ 'a' }; c <= 'z'; ++c)
        for (char b{ 'a' }; b <= 'z'; ++b)
            for (char a{ 'a' }; a <= 'z'; ++a)
            {
                lastPwd = pwd;
                pwd[4] = a;
                pwd[5] = b;
                pwd[6] = c;
                fS.push_back(std::async(std::launch::async, run, users, lastPwd, pwd, pwd.size() - 1));
            }*/

    return 0;
}
