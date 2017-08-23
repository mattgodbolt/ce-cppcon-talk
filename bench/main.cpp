#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>

using namespace std;

static vector<int> makeTest() {
    vector<int> testVec;
    for (auto i = 0; i < 1000; ++i) testVec.emplace_back(i);
    return testVec;
}

static void BM_sum1(benchmark::State &state) {
    auto v = makeTest();
    while (state.KeepRunning()) {
        int result = 0;
        for (size_t i = 0; i < v.size(); ++i)
            result += v[i];
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_sum1);

static void BM_sum2(benchmark::State &state) {
    auto v = makeTest();
    while (state.KeepRunning()) {
        int result = 0;
        for (int x : v) result += x;
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_sum2);

BENCHMARK_MAIN();
