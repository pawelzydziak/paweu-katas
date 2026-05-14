#ifndef KATA_STALINSORT_H
#define KATA_STALINSORT_H

#include "../../lib/KataFramework.h"

class StalinSort : public IKata {
public:
    StalinSort() {
        name = "Stalin Sort Kata";
    }

    std::any Solve(const std::vector<std::any> &args) override {
        auto arr = std::any_cast<std::vector<int>>(args.at(0));

        if (arr.empty()) {
            return arr;
        }

        int prev = arr[0];
        for (size_t i = 1; i < arr.size(); ) {
            if (prev > arr[i]) {
                arr.erase(arr.begin() + i);
            } else {
                prev = arr[i];
                ++i;
            }
        }

        return arr;
    }

    std::vector<TestCase> GetTestCases() override {
        std::vector<TestCase> testCases;

        testCases.push_back(MakeEqualityTestCase(
            MakeInputs(std::vector<int>{1, 2, 3, 5, 4}),
            std::vector<int>{1, 2, 3, 5}
            ));

        testCases.push_back(MakeEqualityTestCase(
            MakeInputs(std::vector<int>{}),
            std::vector<int>{}
        ));

        testCases.push_back(MakeEqualityTestCase(
            MakeInputs(std::vector<int>{1}),
            std::vector<int>{1}
        ));

        return testCases;
    }
};

#endif //KATA_STALINSORT_H