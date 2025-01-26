#ifndef KATA_KATAFRAMEWORK_H
#define KATA_KATAFRAMEWORK_H

#include <any>
#include <vector>
#include <functional>
#include <iostream>

struct TestCase {
    std::vector<std::any> inputs;
    std::any expected;
    std::function<bool(const std::any&, const std::any&)> comparator;
};

class IKata {
public:
    std::string name;
    virtual ~IKata() = default;
    virtual std::any Solve(const std::vector<std::any>& args) = 0;
    virtual std::vector<TestCase> GetTestCases() = 0;
};

template<typename... Args>
std::vector<std::any> MakeInputs(Args&&... args) {
    return { std::forward<Args>(args)... };
}

template<typename T>
TestCase MakeTestCase(std::vector<std::any> inputs, T expected) {
    return { inputs, std::any(expected), [](const std::any& a, const std::any& b) {
        return std::any_cast<T>(a) == std::any_cast<T>(b);
    }};
}

void RunKata(IKata& kata) {
    std::cout << "Running kata: " << kata.name << "\n";
    for (const auto& testCase : kata.GetTestCases()) {
        try {
            std::any result = kata.Solve(testCase.inputs);
            if (testCase.comparator(result, testCase.expected)) {
                std::cout << "Test passed!\n";
            } else {
                std::cout << "Test failed: wrong result\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Test failed: " << e.what() << "\n";
        }
    }
}

#endif //KATA_KATAFRAMEWORK_H
