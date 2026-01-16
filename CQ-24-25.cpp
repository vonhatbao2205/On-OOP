#include "library.h"
// Cau 1
//  #include <climits>
//  #include <pthread.h>
//  a)
//  - Private:
//  + Class con khong the truy cap phan tu private cua class char
//  - Protected:
//  + Class con co the truy cap phan tu protected cua class cha
//  - VD:
//  class Mobile
//  {
//      private:
//          int price;
//      protected:
//          int weight;
//  };
//  class Phone: public Mobile
//  {
//      public:
//          int getWeight()
//          {
//              return weight;
//          }
//          int getPrice()
//          {
//              return price; // Price khong the truy cap nen se bi loi bien
//              dich
//          }
//  };
//  b)
//  - virtual function: class cha khai bao la virtual thi class con co the
//  override function
//  - override function: khi override function thi khong can khai bao la virtual

// Cau 2

#include <iostream>
#include <vector>
using namespace std;
class ICustomer {
public:
  virtual void update(string message) = 0;
};
class IStore {
public:
  virtual void addCustomer(ICustomer *cust) = 0;
  virtual void removeCustomer(ICustomer *cust) = 0;
  virtual void notifyCustomer(string message) = 0;
};
class ConcreteStore : public IStore {
protected:
  vector<ICustomer *> customers;

public:
  void addCustomer(ICustomer *cust) { customers.push_back(cust); }
  void removeCustomer(ICustomer *cust) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
      if (*it == cust) {
        customers.erase(it);
        break;
      }
    }
  }
  void notifyCustomer(string message) {
    for (auto cust : customers) {
      cust->update(message);
    }
  }
};
class ConreteCustomer : public ICustomer {
public:
  void update(string message) {
    cout << "Customer received message: " << message << endl;
  }
};

// Cau 3
class Normalize {
public:
  virtual string normalize(string s) = 0;
  virtual ~Normalize() {}
  virtual Normalize *clone() const = 0;
};
class NormalizeCasing : public Normalize {
public:
  string normalize(string s) {
    stringstream ss(s);
    string new_s, tmp;
    while (ss >> tmp) {
      tmp[0] = toupper(tmp[0]);
      for (int i = 1; i < tmp.size(); i++)
        tmp[i] = tolower(tmp[i]);
      new_s = new_s + tmp + " ";
    }
    new_s.pop_back();
    return new_s;
  }
  Normalize *clone() const { return new NormalizeCasing(*this); }
};
class RemoveSpecialCharacter : public Normalize {
public:
  string normalize(string s) {
    string new_s;
    for (char c : s) {
      if (c != '-' && c != '_' && c != ' ' && c != '.')
        new_s += c;
    }
    return new_s;
  }
  Normalize *clone() const { return new RemoveSpecialCharacter(*this); }
};
class AddDatePrefix : public Normalize {
public:
  string normalize(string s) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string new_s = to_string(1900 + ltm->tm_year) + to_string(1 + ltm->tm_mon) +
                   to_string(ltm->tm_mday) + "_" + s;
    return new_s;
  }
  Normalize *clone() const { return new AddDatePrefix(*this); }
};
class RenameCVFileUseCase {
private:
  vector<Normalize *> normalizes;

public:
  string rename(const string &originalFilename) {
    string newFilename = originalFilename;
    for (Normalize *normalize : normalizes) {
      newFilename = normalize->normalize(newFilename);
    }
    return newFilename;
  }
  void addNormalize(Normalize *normalize) { normalizes.push_back(normalize); }
  void removeNormalize(Normalize *normalize) {
    for (int i = 0; i < normalizes.size(); i++) {
      if (normalizes[i] == normalize) {
        normalizes.erase(normalizes.begin() + i);
        break;
      }
    }
  }
  RenameCVFileUseCase() { normalizes = vector<Normalize *>(); }
  ~RenameCVFileUseCase() {
    for (Normalize *normalize : normalizes) {
      delete normalize;
    }
  }
  RenameCVFileUseCase(const RenameCVFileUseCase &other) {
    for (Normalize *normalize : other.normalizes) {
      normalizes.push_back(normalize->clone());
    }
  }
  RenameCVFileUseCase &operator=(const RenameCVFileUseCase &other) {
    if (this != &other) {
      for (Normalize *normalize : normalizes) {
        delete normalize;
      }
      normalizes.clear();
      for (Normalize *normalize : other.normalizes) {
        normalizes.push_back(normalize->clone());
      }
    }
    return *this;
  }
  void loadRules(string filename) {
    for (Normalize *normalize : normalizes) {
      delete normalize;
    }
    normalizes.clear();

    ifstream file(filename);
    if (!file) {
      cout << "Error: Khong the mo file " << filename << endl;
      return;
    }

    string line;
    while (getline(file, line)) {
      stringstream ss(line);
      string ruleName;
      ss >> ruleName;
      if (ruleName == "NormalizeCasing") {
        addNormalize(new NormalizeCasing());
      } else if (ruleName == "RemoveSpecialCharacter" ||
                 ruleName == "RemoveSpecialsCharacter") {
        addNormalize(new RemoveSpecialCharacter());
      } else if (ruleName == "AddDatePrefix") {
        addNormalize(new AddDatePrefix());
      }
    }
    file.close();
  }
};
int main() {
  RenameCVFileUseCase useCase;
  useCase.loadRules("rules.txt");
  cout << useCase.rename("ho so xin viec cua nguyen van B") << endl;
  return 0;
}