#ifndef NMTKIT_ARRAY_H_
#define NMTKIT_ARRAY_H_

#include <algorithm>
#include <utility>
#include <nmtkit/random.h>

namespace NMTKit {

// Array manipulators.
class Array {
public:
  // Sort given vector.
  // Arguments:
  //   arr: Target vector.
  //   less: Predicate indicating first arg < second arg.
  template <typename T, typename P>
  static void sort(std::vector<T> * arr, P less) {
    // Implementing heap sort.
    auto downheap = [&](int k, int r) {
      while (true) {
        int j = (k << 1) + 1;
        if (j > r) {
          break;
        }
        if (j != r) {
          if (less((*arr)[j], (*arr)[j + 1])) {
            ++j;
          }
        }
        if (less((*arr)[j], (*arr)[k])) {
          break;
        }
        std::swap((*arr)[k], (*arr)[j]);
        k = j;
      }
    };
    const int n = arr->size();
    for (int i = (n - 2) >> 1; i >= 0; --i) {
      downheap(i, n - 1);
    }
    for (int i = n - 1; i > 0; --i) {
      std::swap((*arr)[0], (*arr)[i]);
      downheap(0, i - 1);
    }
  }

  // Shuffles given vector.
  // Arguments:
  //   arr: Target vector.
  //   rnd: Random object to be used.
  template <typename T>
  static void shuffle(std::vector<T> * arr, Random * rnd) {
    // Implementing Fisher-Yates algorithm.
    const unsigned M = arr->size();
    for (unsigned i = 0; i < M - 1; ++i) {
      const unsigned j = rnd->uniform(i, M);
      if (j > i) {
        std::swap((*arr)[i], (*arr)[j]);
      }
    }
  }
};

}  // namespace NMTKit

#endif  // NMTKIT_ARRAY_H_
