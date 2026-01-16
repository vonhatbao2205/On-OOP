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
// class Fraction
// {
//     protected:
//         int _num,_den;
//     public:
//         friend ostream& operator<<(ostream& out, const Fraction& other)
//         {
//             out<<other._num<<"/"<<other._den;
//             return out;
//         }
//         Fraction(int num, int den): _num(num), _den(den) {}
// };
// class PrimeFracIterator
// {
//     private:
//         Fraction *curr;
//         Fraction *end;
//         void findNextValid()
//         {
//             while(curr!=end && !isPrime(curr->_num))
//             {
//                 curr++;
//             }
//         }
//     public:
//         PrimeFracIterator(Fraction* arr, int size)
//         {
//             _size=size;
//             _arr=new Fraction[size];
//             for(int i=0;i<size;i++)
//             {
//                 _arr[i]=arr[i];
//             }
//         }
//         ~PrimeFracIterator()
//         {
//             delete[] _arr;
//         }
//         PrimeFracIterator(const PrimeFracIterator& other)
//         {
//             _size=other._size;
//             _arr=new Fraction[_size];
//             for(int i=0;i<_size;i++)
//             {
//                 _arr[i]=other._arr[i];
//             }
//         }
//         PrimeFracIterator& operator=(const PrimeFracIterator& other)
//         {
//             if(this!=&other)
//             {
//                 delete[] _arr;
//                 _size=other._size;
//                 _arr=new Fraction[_size];
//                 for(int i=0;i<_size;i++)
//                 {
//                     _arr[i]=other._arr[i];
//                 }
//             }
//             return *this;
//         }
//         PrimeFracIterator& operator++()
//         {
//             curr++;
//             findNextValid();
//             return *this;
//         }
//         Fraction operator*()
//         {
//             return *curr;
//         }
//         operator bool()
//         {
//             return curr!=end;
//         }
// };
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
