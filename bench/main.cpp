#include <benchmark/benchmark.h>
#include <vector>

extern int externalFunc(int);

using namespace std;

static vector<int> makeTest() {
  vector<int> testVec;
  for (auto i = 0; i < 10000; ++i) testVec.emplace_back(i);
  return testVec;
}

static void BM_sumLoopBySize(benchmark::State &state) {
  auto v = makeTest();
  while (state.KeepRunning()) {
    int result = 0;
    for (size_t i = 0; i < v.size(); ++i)
      result += v[i];
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(BM_sumLoopBySize);

static void BM_sumLoopByRangeFor(benchmark::State &state) {
  auto v = makeTest();
  while (state.KeepRunning()) {
    int result = 0;
    for (int x : v) result += x;
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(BM_sumLoopByRangeFor);

static void BM_sumLoopBySizeCallingExternal(benchmark::State &state) {
  auto v = makeTest();
  while (state.KeepRunning()) {
    int result = 0;
    for (size_t i = 0; i < v.size(); ++i)
      result += externalFunc(v[i]);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(BM_sumLoopBySizeCallingExternal);

static void BM_sumLoopByRangeForCallingExternal(benchmark::State &state) {
  auto v = makeTest();
  while (state.KeepRunning()) {
    int result = 0;
    for (int x : v) result += externalFunc(x);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(BM_sumLoopByRangeForCallingExternal);

BENCHMARK_MAIN();
