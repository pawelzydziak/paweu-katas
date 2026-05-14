#ifndef KATA_KATAFRAMEWORK_H
#define KATA_KATAFRAMEWORK_H

#include <any>
#include <vector>
#include <functional>
#include <iostream>
#include <format>

constexpr int g_debug = 0; //todo

struct TestCase {
    std::vector<std::any> inputs;
    std::function<bool(const std::any&)> validator;
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

// equality test, it should be equal to sth
template<typename T>
TestCase MakeEqualityTestCase(std::vector<std::any> inputs, T expected) {
    return {
        std::move(inputs),
        [expected](const std::any& result) {
            return std::any_cast<T>(result) == expected;
        }
    };
}

// predicate test, it should fulfill condition
template<typename T>
TestCase MakePredicateTestCase(std::vector<std::any> inputs, std::function<bool(const T&)> predicate) {
    return {
        std::move(inputs),
        [predicate](const std::any& result) {
            return predicate(std::any_cast<T>(result));
        }
    };
}

inline void RunKata(IKata& kata) {
    int passed = 0;
    std::cout << "Running kata: " << kata.name << "\n";
    for (const auto& testCase : kata.GetTestCases()) {
        try {
            std::any result = kata.Solve(testCase.inputs);
            if (testCase.validator(result)) {
                if(g_debug)
                    std::cout << "Test passed!\n";
                passed++;
            } else {
                if(g_debug)
                    std::cout << "Test failed: wrong result\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Test failed: " << e.what() << "\n";
        }
    }
    std::cout << std::format("Finished running kata: {} ({}/{})\n", kata.name, passed, kata.GetTestCases().size());
}

#endif //KATA_KATAFRAMEWORK_H
