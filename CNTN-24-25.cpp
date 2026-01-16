// Cau 1
// a)
// Create.
// Create.
// Create.
// Copy.
// Copy.
// Copy.
// 2

// b)
// Modify void operator()(T num) into void operator()(const T &num)

// // Cau 2
// #include <iostream>
// #include <cmath>

// using namespace std;

// bool isPrime(int n) {
//     if (n < 2) return false;
//     for (int i = 2; i <= sqrt(n); ++i)
//         if (n % i == 0) return false;
//     return true;
// }

// class Fraction {
// private:
//     int _num, _den;

//     friend class PrimeFracIterator;

// public:
//     Fraction(int num = 0, int den = 1) : _num(num), _den(den) {}

//     friend ostream& operator<<(ostream& out, const Fraction& f) {
//         out << f._num << "/" << f._den;
//         return out;
//     }
// };

// class PrimeFracIterator {
// private:
//     Fraction* curr;
//     Fraction* end;

//     bool isValid(Fraction* f) {
//         return isPrime(f->_num) && isPrime(f->_den);
//     }
//     void findNextValid() {
//         while (curr < end && !isValid(curr)) {
//             curr++;
//         }
//     }

// public:
//     PrimeFracIterator(Fraction* arr, int size) {
//         curr = arr;
//         end = arr + size;

//         if (curr < end && !isValid(curr)) {
//             findNextValid();
//         }
//     }
//     PrimeFracIterator& operator++() {
//         curr++;
//         return *this;
//     }
//     Fraction operator*() {
//         return *curr;
//     }
//     operator bool() {
//         return curr < end;
//     }
// };

// int main() {
//     Fraction a[] = { {1, 2}, {2, 3}, {4, 2}, {3, 5} };

//     PrimeFracIterator i(a, 4);

//     while(i) {
//         cout << *i << " ";
//         ++i;
//     }
//     return 0;
// }
// Cau 3
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

template <class T> class Filter {
public:
  virtual bool check(T val, int index, const vector<T> &data) = 0;
  virtual ~Filter() {}
  virtual Filter *clone() const = 0;
};

template <class T> class DivisibleFilter : public Filter<T> {
private:
  int n;

public:
  DivisibleFilter(int n) : n(n) {}
  bool check(T val, int index, const vector<T> &data) override {
    return (val % n == 0);
  }
  DivisibleFilter *clone() const override { return new DivisibleFilter(*this); }
};

template <class T> class OddIndexFilter : public Filter<T> {
public:
  bool check(T val, int index, const vector<T> &data) override {
    return (index % 2 != 0);
  }
  OddIndexFilter *clone() const override { return new OddIndexFilter(*this); }
};

template <class T> class DiffAvgFilter : public Filter<T> {
private:
  double percent;

public:
  DiffAvgFilter(double p) : percent(p) {}

  bool check(T val, int index, const vector<T> &data) override {
    if (data.empty())
      return false;

    double sum = 0;
    for (T x : data)
      sum += x;
    double avg = sum / data.size();
    return abs(val - avg) <= (avg * percent);
  }
  DiffAvgFilter *clone() const override { return new DiffAvgFilter(*this); }
};

template <class T> class Extractor {
private:
  vector<Filter<T> *> filters;

public:
  void add(Filter<T> *f) { filters.push_back(f); }
  Extractor() { filters = vector<Filter<T> *>(); }
  ~Extractor() {
    for (auto f : filters) {
      delete f;
    }
  }
  Extractor(const Extractor &other) {
    for (Filter<T> *f : other.filters) {
      filters.push_back(f->clone());
    }
  }
  Extractor &operator=(const Extractor &other) {
    if (this != &other) {
      for (Filter<T> *f : filters) {
        delete f;
      }
      filters.clear();
      for (Filter<T> *f : other.filters) {
        filters.push_back(f->clone());
      }
    }
    return *this;
  }
  vector<T> extract(const vector<T> &data) {
    vector<T> result;

    for (int i = 0; i < data.size(); ++i) {
      bool passedAll = true;

      for (auto f : filters) {
        if (!f->check(data[i], i, data)) {
          passedAll = false;
          break;
        }
      }

      if (passedAll) {
        result.push_back(data[i]);
      }
    }
    return result;
  }
};

int main() {
  Extractor<int> ex;
  ex.add(new DivisibleFilter<int>(3));
  ex.add(new OddIndexFilter<int>());
  ex.add(new DiffAvgFilter<int>(0.2));

  std::vector<int> a = {10, 3, 15, 6, 2, 9, 4, 15, 5, 6};
  std::vector<int> b = ex.extract(a);

  for (auto &e : b) {
    std::cout << e << " ";
  }
  return 0;
}
