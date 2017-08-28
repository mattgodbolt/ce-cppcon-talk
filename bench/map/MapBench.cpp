#include <benchmark/benchmark.h>

#include <iostream>
#include <random>
#include <variant>
#include <vector>
#include "OrderIdMap.h"


namespace {

using namespace std;
struct Add {
  OrderId id;
  uint32_t instrument;
  double px;
  uint32_t qty;
};
struct Modify {
  OrderId id;
  double px;
  uint32_t qty;
};
struct Remove {
  OrderId id;
};

using Action = variant<Add, Modify, Remove>;

vector<Action> makeActions(size_t numActions, size_t startingOrders) noexcept {
  vector<OrderId> active;
  mt19937_64 engine(31415926);
  uniform_int_distribution<OrderId> randomOrderId;
  uniform_int_distribution<uint32_t> randomQty(1, 1000);
  uniform_int_distribution<uint32_t> randomInstr(1, 10000);
  uniform_real_distribution<double> randomPx(-50000, 50000);
  uniform_int_distribution<int> randomAction(0, 8);
  vector<Action> actions;
  size_t maxSize = 0;
  auto addOrder = [&]{
    auto id = randomOrderId(engine);
    active.emplace_back(id);
    actions.emplace_back(Add{id, randomInstr(engine), randomPx(engine), randomQty(engine)});
    maxSize = std::max(maxSize, active.size());
  };
  for (auto i = 0u; i < startingOrders; ++i) addOrder();
  while (actions.size() < numActions) {
    switch (randomAction(engine)) {
      case 0:
        addOrder();
        break;
      case 1:
        if (!active.empty()) {
          auto index = uniform_int_distribution<>(0, active.size() - 1)(engine);
          actions.emplace_back(Remove{active[index]});
          active.erase(active.begin() + index);
        }
        break;
      default:
        if (!active.empty()) {
          auto index = uniform_int_distribution<>(0, active.size() - 1)(engine);
          actions.emplace_back(Modify{active[index], randomPx(engine), randomQty(engine)});
          break;
        }
    }
  }
  std::cout << "Max orders: " << maxSize << ", orders at end: " << active.size() << "\n";
  return actions;
}

const auto actions = makeActions(100'000, 1'000);

template<typename T>
struct Visitor {
  T &container;
  explicit Visitor(T &container) : container(container) {}
  void operator()(const Add &add) { container.add(add.id, add.instrument, add.px, add.qty); }
  void operator()(const Modify &mod) { container.modify(mod.id, mod.px, mod.qty); }
  void operator()(const Remove &rem) { container.remove(rem.id); }
};

template<typename T>
void runBench(benchmark::State &state) {
  while (state.KeepRunning()) {
    state.PauseTiming();
    T container;
    Visitor v(container);
    state.ResumeTiming();
    for (auto &&action : actions)
      visit(v, action);
    benchmark::ClobberMemory();
  }
}

void BM_UnorderedMap(benchmark::State &state) {
  runBench<OrderIdMap_UnorderedMap>(state);
}

BENCHMARK(BM_UnorderedMap);

void BM_UnorderedMapReserved5000(benchmark::State &state) {
  runBench<OrderIdMap_UnorderedMapReserved5000>(state);
}

BENCHMARK(BM_UnorderedMapReserved5000);

void BM_Map(benchmark::State &state) {
  runBench<OrderIdMap_Map>(state);
}

BENCHMARK(BM_Map);

void BM_FixedMap(benchmark::State &state) {
  runBench<FixedOrderIdMap<2048,5>>(state);
}

BENCHMARK(BM_FixedMap);

}

BENCHMARK_MAIN();
