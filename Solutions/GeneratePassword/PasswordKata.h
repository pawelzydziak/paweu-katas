#ifndef KATA_PASSWORDKATA_H
#define KATA_PASSWORDKATA_H

#include <ctime>
#include <random>
#include <vector>
#include "../../common/KataFramework.h"

class PasswordKata : public IKata {
public:
    std::any Solve(const std::vector<std::any> &args) override
    {
        // wylosowac dlugosc
        // po iterowac po tej dlugosci i wybrac jeden ze znakow normalnie alfabetu
        // jesli nie ma cyfry zmien w losowym miejscu
        // jesli nie ma duzej zamien losowa litere
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(6, 20);
        std::uniform_int_distribution<> alphabet('a', 'z');
        std::uniform_int_distribution<> digit(0, 9);
        std::uniform_int_distribution<> uppercase('A', 'Z');

        auto len = distr(gen);
        std::string pass;

        for (auto i = 0; i < len; i++)
        {
            // add random small letter
            pass += alphabet(gen);
        }

        std::uniform_int_distribution<> num_digits(1, len / 2);
        int digits_to_change = num_digits(gen);

        for (int i = 0; i < digits_to_change; i++)
        {
            pass[rand() % len] = '0' + digit(gen);
        }
        std::uniform_int_distribution<> num_uppercase(1, len / 2);
        int uppercase_to_change = num_uppercase(gen);
        for (int i = 0; i < uppercase_to_change; i++)
        {
            pass[rand() % len] = uppercase(gen);
        }
        return pass;
    }


    std::vector<TestCase> GetTestCases() override {
        std::vector<TestCase> testCases;

        for (int i = 0; i < 5; ++i)
        {
            testCases.push_back({
            {},  // no imp arg
            std::any(),  // exp val unused
            CreateComparator<std::string>()
            });
        }

        return testCases;
    }

private:
    template<typename T>
    static std::function<bool(const std::any&, const std::any&)> CreateComparator() {
        return [](const std::any &a, const std::any &b) {
            auto pass = std::any_cast<std::string>(a);
            return pass.size() >= 6 && pass.size() <= 20 &&
                   std::any_of(pass.begin(), pass.end(), isdigit) &&
                   std::any_of(pass.begin(), pass.end(), isupper) &&
                   std::any_of(pass.begin(), pass.end(), islower);
        };
    }
};


#endif //KATA_PASSWORDKATA_H
