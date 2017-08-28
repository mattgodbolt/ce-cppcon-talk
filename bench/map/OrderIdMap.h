#pragma once

#include <cstdint>
#include <unordered_map>
#include <optional>
#include <map>
#include <iostream>

using OrderId = uint64_t;

struct Order {
  uint32_t instrument;
  double px;
  uint32_t qty;
  Order(uint32_t instrument, double px, uint32_t qty) : instrument(instrument), px(px), qty(qty) {}
};

template<typename Container>
struct OrderIdMapBase {
  Container map_;
  void add(OrderId id, uint32_t instrument, double px, uint32_t qty) {
    map_.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(instrument, px, qty));
  }
  void modify(OrderId id, double px, uint32_t qty) {
    auto it = map_.find(id);
    it->second.px = px;
    it->second.qty = qty;
  }
  void remove(OrderId id) {
    map_.erase(id);
  }
};

using OrderIdMap_UnorderedMap = OrderIdMapBase<std::unordered_map<OrderId, Order>>;
using OrderIdMap_Map = OrderIdMapBase<std::map<OrderId, Order>>;

struct OrderIdMap_UnorderedMapReserved5000 : OrderIdMapBase<std::unordered_map<OrderId, Order>> {
  OrderIdMap_UnorderedMapReserved5000() {
    map_.reserve(5000);
  }
};

template<unsigned NumBuckets, unsigned BucketSize>
struct FixedOrderIdMap {
  struct Elem {
    OrderId id;
    Order order;
    Elem(OrderId id, uint32_t instrument, double px, uint32_t qty)
        : id(id), order(instrument, px, qty) {}
  };

  struct Bucket {
    std::optional<Elem> elem_[BucketSize];
  };
  Bucket buckets_[NumBuckets];

  static constexpr uint64_t hash(OrderId id) noexcept {
    return id * 14695981039346656037ull;
  }

  Bucket &bucketFor(OrderId id) noexcept {
    return buckets_[hash(id) % NumBuckets];
  }

  std::optional<Elem> &elemFor(OrderId id) {
    auto &bucket = bucketFor(id);
    for (auto i = 0u; i < BucketSize; ++i) {
      if (bucket.elem_[i] && bucket.elem_[i]->id == id)
        return bucket.elem_[i];
    }
    throw std::runtime_error("missing");
  }

  void add(OrderId id, uint32_t instrument, double px, uint32_t qty) {
    auto &bucket = bucketFor(id);
    for (auto i = 0u; i < BucketSize; ++i) {
      if (!bucket.elem_[i]) {
        bucket.elem_[i].emplace(id, instrument, px, qty);
        return;
      }
    }
    dump();
    throw std::runtime_error("collision");
  }
  void modify(OrderId id, double px, uint32_t qty) noexcept {
    auto &elem = elemFor(id);
    elem->order.px = px;
    elem->order.qty = qty;
  }
  void remove(OrderId id) noexcept {
    elemFor(id) = {};
  }

  void dump() const {
    for (auto i = 0u; i < NumBuckets; ++i) {
      std::cout << i << " :";
      for (auto &elem : buckets_[i].elem_) {
        if (elem) std::cout << ' ' << elem->id;
      }
      std::cout << '\n';
    }
  }
};