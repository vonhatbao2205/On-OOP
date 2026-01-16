#include "library.h"

// Cau 1 -> Skip
// Cau 4 -> Skip

// Cau 2
//  - Abstract class la class co chua it nhat mot phuong thuc thuan ao
//  - Syntax: virtual <return type> <name> (<parameter>) = 0
//  - Dong vai tro la base class de quy dinh mot khuon mau chung cho cac class
//  con ke thua
//  - VD
//  class PaymentMethod {
//  public:
//      virtual void processPayment(float amount) = 0;
//      virtual ~PaymentMethod() {}
//  };
//  class CreditCard : public PaymentMethod {
//  public:
//      void processPayment(float amount) override {cout <<
//      "Visa/Mastercard\n";}
//  };
//  class EWallet : public PaymentMethod {
//  public:
//      void processPayment(float amount) override {cout << "Vi dien tu\n";}
//  };

// Cau 3
//  b)
//  0
//  2880000
//  10000000
//  c)
//  void sortPayers(TaxPayer *taxPayers[], int nPayers) {
//      for (int i = 0; i < nPayers - 1; i++) {
//          for (int j = i + 1; j < nPayers; j++) {
//              if (taxPayers[i]->calcTax() > taxPayers[j]->calcTax()) {
//                  TaxPayer* temp = taxPayers[i];
//                  taxPayers[i] = taxPayers[j];
//                  taxPayers[j] = temp;
//              }
//          }
//      }
//  }
