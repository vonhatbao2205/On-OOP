#include "library.h"

// Cau 1
//  Virtual
//  + Khai bao virtual
//  + Phai co cai dat trong lop co so
//  + Lop chua ham ao van co the khoi tao doi tuong
//  + Lop con co the override hoac dung lai ham lop cha
//  Pure virtual
//  + Khai bao virtual va gan = 0
//  + Khong bat buoc co cai dat trong lop co so
//  + Lop chua it nhat mot ham thuan ao se tro thanh abstract class va khong the
//  khoi tao doi tuong
//  + Lop con bat buoc phai override ham thuan ao neu muon khoi tao doi tuong

// Cau 2
//  a)
//  Make new beverage.
//  Make new coffee.
//  Make new cappuchino.
//  Make new beverage.
//  Copy coffee.
//  b)
//  Cappuchino c1
//  - Day la khoi tao doi tuong, nen Default constructor se duoc goi theo thu tu
//  tu class cha len class con
//  - Beverage() -> Coffee() -> Cappuchino()
//  Cappuchino c2
//  - Đay la khoi tao sao chep
//  - Vi Cappuchina khong dinh nghia sao chep nen sinh ra cai copy constructor
//  mac dinh va constructor nay se goi copy constructor cua Coffee
//  - Vi Copy construct cua coffee da duoc dinh nghia nhung lai khong goi copy
//  constructor cua class cha la beverage nen se goi Default constructor cua
//  class Beverage
//  - Beverage() -> Coffee(const Coffee& c) -> Default copy constructor cua
//  Cappuchino

// struct Beverage {
//   Beverage() { std::cout << "Make new beverage.\n"; }
//   Beverage(const Beverage &b) { std::cout << "Copy beverage.\n"; }
// };
// struct Coffee : public Beverage {
//   Coffee() { std::cout << "Make new coffee.\n"; }
//   Coffee(const Coffee &c) { std::cout << "Copy coffee.\n"; }
// };
// struct Cappuchino : public Coffee {
//   Cappuchino() { std::cout << "Make new cappuchino.\n"; }
// };
// int main() {
//   Cappuchino c1;
//   Cappuchino c2(c1);
//   return 0;
// }

// Cau 3

class PrimeList {
private:
  int *_primes;
  int _size;
  bool isPrime(int n) const {
    if (n < 2)
      return false;
    for (int i = 2; i <= sqrt(n); ++i) {
      if (n % i == 0)
        return false;
    }
    return true;
  }

public:
  PrimeList() : _primes(nullptr), _size(0) {}
  PrimeList(int upperBound) {
    _primes = nullptr;
    _size = 0;
    generate(upperBound);
  }
  ~PrimeList() {
    if (_primes) {
      delete[] _primes;
    }
  }
  void generate(int upperBound) {
    if (_primes) {
      delete[] _primes;
      _primes = nullptr;
      _size = 0;
    }
    int count = 0;
    for (int i = 2; i < upperBound; ++i) {
      if (isPrime(i))
        count++;
    }
    _size = count;
    if (_size > 0) {
      _primes = new int[_size];
      int index = 0;
      for (int i = 2; i < upperBound; ++i) {
        if (isPrime(i)) {
          _primes[index++] = i;
        }
      }
    }
  }
  PrimeList &operator=(const PrimeList &other) {
    if (this != &other) {
      if (_primes)
        delete[] _primes;
      _size = other._size;
      if (_size > 0) {
        _primes = new int[_size];
        for (int i = 0; i < _size; ++i) {
          _primes[i] = other._primes[i];
        }
      } else {
        _primes = nullptr;
      }
    }
    return *this;
  }
  PrimeList(const PrimeList &other) {
    _size = other._size;
    if (_size > 0) {
      _primes = new int[_size];
      for (int i = 0; i < _size; i++)
        _primes[i] = other._primes[i];
    } else {
      _primes = nullptr;
    }
  }
  int count() const { return _size; }
  int operator[](int index) const { return _primes[index]; }
  friend std::ostream &operator<<(std::ostream &os, const PrimeList &list) {
    for (int i = 0; i < list._size; ++i) {
      os << list._primes[i] << " ";
    }
    os << "\n";
    return os;
  }
};

// Cau 4
// a)
// classDiagram
//     class Mobile {
//         - string _name
//         - string _storage
//         - long _price
//         + Mobile(name, storage, price)
//         + print() void
//     }

//     class Crawler {
//         - string _url
//         + Crawler(url: const char*)
//         + execute() vector<Mobile*>
//     }

//     Crawler ..> Mobile : creates

// class Mobile {
// private:
//   string _name;
//   string _storage;
//   long _price;

// public:
//   Mobile(string name, string storage, long price)
//       : _name(name), _storage(storage), _price(price) {}
//   void print() { cout << _name << " " << _storage << " - " << _price; }
// };

// c)
// classDiagram
//     class IPriceFormatter {
//         <<interface>>
//         + format(price: long) string
//     }

//     class VNFormatter {
//         + format(price: long) string
//     }

//     class USFormatter {
//         + format(price: long) string
//     }

//     class Mobile {
//         - IPriceFormatter* _priceFormatter
//         + setPriceFormatter(formatter: IPriceFormatter*)
//         + print() void
//     }

//     VNFormatter ..|> IPriceFormatter : implements
//     USFormatter ..|> IPriceFormatter : implements
//     Mobile --> IPriceFormatter : uses strategy

// d)
// classDiagram
//     class ILayout {
//         <<interface>>
//         + printList(items: vector<Mobile*>) void
//     }

//     class SimpleLayout {
//         + printList(items: vector<Mobile*>) void
//     }

//     class TableLayout {
//         + printList(items: vector<Mobile*>) void
//     }

//     class Mobile {
//         + getName() string
//         + getPrice() long
//         + getStorage() string
//     }

//     SimpleLayout ..|> ILayout : implements
//     TableLayout ..|> ILayout : implements
//     ILayout ..> Mobile : depends on