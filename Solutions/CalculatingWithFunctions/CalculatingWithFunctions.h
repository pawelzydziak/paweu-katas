#ifndef KATA_CALCULATINGWITHFUNCTIONS_H
#define KATA_CALCULATINGWITHFUNCTIONS_H
#include "../../lib/KataFramework.h"

class CalculatingWithFunctions : public IKata{
public:
    CalculatingWithFunctions(){
        name = "Calculating With Functions";
    }

    std::any Solve(const std::vector<std::any>& args) override {
        if (args.size() != 1) {
            throw std::invalid_argument("Invalid number of arguments");
        }
        return std::any_cast<int>(args[0]);
    }

    std::vector<TestCase> GetTestCases() override {
        std::vector<TestCase> testCases;
        testCases.push_back(MakeTestCase(MakeInputs(seven(times(five()))), 35));
        testCases.push_back(MakeTestCase(MakeInputs(four(plus(nine()))), 13));
        testCases.push_back(MakeTestCase(MakeInputs(eight(minus(three()))), 5));
        testCases.push_back(MakeTestCase(MakeInputs(six(divided_by(two()))), 3));
        testCases.push_back(MakeTestCase(MakeInputs(eight(divided_by(three()))), 2));
        return testCases;
    }

private:
    template<typename T>
    static std::function<bool(const std::any&, const std::any&)> CreateComparator() {
        return [](const std::any &a, const std::any &b) {
            return std::any_cast<T>(a) == std::any_cast<T>(b);
        };
    }


    auto zero(const std::function<int(int)>& fun = nullptr) -> int {
        return fun ? fun(0) : 0;
    }
    auto one(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(1) : 1;
    }
    auto two(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(2) : 2;
    }
    auto three(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(3) : 3;
    }
    auto four(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(4) : 4;
    }
    auto five(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(5) : 5;
    }
    auto six(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(6) : 6;
    }
    auto seven(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(7) : 7;
    }
    auto eight(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(8) : 8;
    }
    auto nine(const std::function<int(int)>& fun = nullptr) -> int  {
        return fun ? fun(9) : 9;
    }

    auto plus(int num) -> std::function<int(int)> {
        return [num](int x) { return x + num; };
    }
    auto minus(int num) -> std::function<int(int)> {
        return [num](int x) { return x - num; };
    }
    auto times(int num) -> std::function<int(int)> {
        return [num](int x) { return x * num; };
    }
    auto divided_by(int num) -> std::function<int(int)> {
        return [num](int x) { return x / num; };
    }
};
#endif //KATA_CALCULATINGWITHFUNCTIONS_H