// @author: gezhipeng @ 20230409
// @file: allocator.cc
// @brief: allocator
#include "allocator.h"
#include "log.h"
#include <google/protobuf/stubs/mutex.h>
#include <list>
namespace gcode {
namespace base {
Allocator::~Allocator() {}

class PoolAllocatorPrivate {
public:
  google::protobuf::Mutex budgets_lock;
  google::protobuf::Mutex payouts_lock;
  unsigned int size_compare_ratio; // 0~256
  size_t size_drop_threshold;
  std::list<std::pair<size_t, void *>> budgets;
  std::list<std::pair<size_t, void *>> payouts;
};

PoolAllocator::PoolAllocator() : Allocator(), d(new PoolAllocatorPrivate) {
  d->size_compare_ratio = 0;
  d->size_drop_threshold = 10;
}

PoolAllocator::~PoolAllocator() {
  clear();

  if (!d->payouts.empty()) {
    LOG_ERROR << "FATAL ERROR! pool allocator destroyed too early";
    std::list<std::pair<size_t, void *>>::iterator it = d->payouts.begin();
    for (; it != d->payouts.end(); ++it) {
      void *ptr = it->second;
      LOG_ERROR << ptr << " still in use";
    }
  }

  delete d;
}

PoolAllocator::PoolAllocator(const PoolAllocator &) : d(0) {}

PoolAllocator &PoolAllocator::operator=(const PoolAllocator &) { return *this; }

void PoolAllocator::clear() {
  d->budgets_lock.Lock();

  std::list<std::pair<size_t, void *>>::iterator it = d->budgets.begin();
  for (; it != d->budgets.end(); ++it) {
    void *ptr = it->second;
    gcode::base::fastFree(ptr);
  }
  d->budgets.clear();

  d->budgets_lock.Unlock();
}

void PoolAllocator::set_size_compare_ratio(float scr) {
  if (scr < 0.f || scr > 1.f) {
    LOG_ERROR << "invalid size compare ratio " << scr;
    return;
  }

  d->size_compare_ratio = (unsigned int)(scr * 256);
}

void PoolAllocator::set_size_drop_threshold(size_t threshold) {
  d->size_drop_threshold = threshold;
}

void *PoolAllocator::fastMalloc(size_t size) {
  d->budgets_lock.Lock();

  // find free budget
  std::list<std::pair<size_t, void *>>::iterator it = d->budgets.begin(),
                                                 it_max = d->budgets.begin(),
                                                 it_min = d->budgets.begin();
  for (; it != d->budgets.end(); ++it) {
    size_t bs = it->first;

    // size_compare_ratio ~ 100%
    if (bs >= size && ((bs * d->size_compare_ratio) >> 8) <= size) {
      void *ptr = it->second;

      d->budgets.erase(it);

      d->budgets_lock.Unlock();

      d->payouts_lock.Lock();

      d->payouts.push_back(std::make_pair(bs, ptr));

      d->payouts_lock.Unlock();

      return ptr;
    }

    if (bs < it_min->first) {
      it_min = it;
    }
    if (bs > it_max->first) {
      it_max = it;
    }
  }

  if (d->budgets.size() >= d->size_drop_threshold) {
    // All chunks in pool are not chosen. Then try to drop some outdated
    // chunks and return them to OS.
    if (it_max->first < size) {
      // Current query is asking for a chunk larger than any cached chunks.
      // Then remove the smallest one.
      gcode::base::fastFree(it_min->second);
      d->budgets.erase(it_min);
    } else if (it_min->first > size) {
      // Current query is asking for a chunk smaller than any cached chunks.
      // Then remove the largest one.
      gcode::base::fastFree(it_max->second);
      d->budgets.erase(it_max);
    }
  }

  d->budgets_lock.Unlock();

  // new
  void *ptr = gcode::base::fastMalloc(size);

  d->payouts_lock.Lock();

  d->payouts.push_back(std::make_pair(size, ptr));

  d->payouts_lock.Unlock();

  return ptr;
}

void PoolAllocator::fastFree(void *ptr) {
  d->payouts_lock.Lock();

  // return to budgets
  std::list<std::pair<size_t, void *>>::iterator it = d->payouts.begin();
  for (; it != d->payouts.end(); ++it) {
    if (it->second == ptr) {
      size_t size = it->first;

      d->payouts.erase(it);

      d->payouts_lock.Unlock();

      d->budgets_lock.Lock();

      d->budgets.push_back(std::make_pair(size, ptr));

      d->budgets_lock.Unlock();

      return;
    }
  }

  d->payouts_lock.Unlock();

  LOG_ERROR << "FATAL ERROR! pool allocator get wild " << ptr;
  gcode::base::fastFree(ptr);
}

class UnlockedPoolAllocatorPrivate {
public:
  unsigned int size_compare_ratio; // 0~256
  size_t size_drop_threshold;
  std::list<std::pair<size_t, void *>> budgets;
  std::list<std::pair<size_t, void *>> payouts;
};

UnlockedPoolAllocator::UnlockedPoolAllocator()
    : Allocator(), d(new UnlockedPoolAllocatorPrivate) {
  d->size_compare_ratio = 0;
  d->size_drop_threshold = 10;
}

UnlockedPoolAllocator::~UnlockedPoolAllocator() {
  clear();

  if (!d->payouts.empty()) {
    LOG_ERROR << "FATAL ERROR! unlocked pool allocator destroyed too early";
    std::list<std::pair<size_t, void *>>::iterator it = d->payouts.begin();
    for (; it != d->payouts.end(); ++it) {
      void *ptr = it->second;
      LOG_ERROR << ptr << " still in use";
    }
  }

  delete d;
}

UnlockedPoolAllocator::UnlockedPoolAllocator(const UnlockedPoolAllocator &)
    : d(0) {}

UnlockedPoolAllocator &UnlockedPoolAllocator::
operator=(const UnlockedPoolAllocator &) {
  return *this;
}

void UnlockedPoolAllocator::clear() {
  std::list<std::pair<size_t, void *>>::iterator it = d->budgets.begin();
  for (; it != d->budgets.end(); ++it) {
    void *ptr = it->second;
    gcode::base::fastFree(ptr);
  }
  d->budgets.clear();
}

void UnlockedPoolAllocator::set_size_compare_ratio(float scr) {
  if (scr < 0.f || scr > 1.f) {
    LOG_ERROR << "invalid size compare ratio " << scr;
    return;
  }

  d->size_compare_ratio = (unsigned int)(scr * 256);
}

void UnlockedPoolAllocator::set_size_drop_threshold(size_t threshold) {
  d->size_drop_threshold = threshold;
}

void *UnlockedPoolAllocator::fastMalloc(size_t size) {
  // find free budget
  std::list<std::pair<size_t, void *>>::iterator it = d->budgets.begin(),
                                                 it_max = d->budgets.begin(),
                                                 it_min = d->budgets.begin();
  for (; it != d->budgets.end(); ++it) {
    size_t bs = it->first;

    // size_compare_ratio ~ 100%
    if (bs >= size && ((bs * d->size_compare_ratio) >> 8) <= size) {
      void *ptr = it->second;

      d->budgets.erase(it);

      d->payouts.push_back(std::make_pair(bs, ptr));

      return ptr;
    }

    if (bs > it_max->first) {
      it_max = it;
    }
    if (bs < it_min->first) {
      it_min = it;
    }
  }

  if (d->budgets.size() >= d->size_drop_threshold) {
    if (it_max->first < size) {
      gcode::base::fastFree(it_min->second);
      d->budgets.erase(it_min);
    } else if (it_min->first > size) {
      gcode::base::fastFree(it_max->second);
      d->budgets.erase(it_max);
    }
  }

  // new
  void *ptr = gcode::base::fastMalloc(size);

  d->payouts.push_back(std::make_pair(size, ptr));

  return ptr;
}

void UnlockedPoolAllocator::fastFree(void *ptr) {
  // return to budgets
  std::list<std::pair<size_t, void *>>::iterator it = d->payouts.begin();
  for (; it != d->payouts.end(); ++it) {
    if (it->second == ptr) {
      size_t size = it->first;

      d->payouts.erase(it);

      d->budgets.push_back(std::make_pair(size, ptr));

      return;
    }
  }

  LOG_ERROR << "FATAL ERROR! unlocked pool allocator get wild " << ptr;
  gcode::base::fastFree(ptr);
}

} // namespace base
} // namespace gcode