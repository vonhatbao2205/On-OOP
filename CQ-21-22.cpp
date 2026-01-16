#include "library.h"
// Cau 1

class Date {
private:
  int _day, _month, _year;
  const int daysInMonth[13] = {0,  31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};
  bool isLeapYear(int y) const {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
  }
  int getDaysInCurrentMonth(int m, int y) const {
    if (m == 2 && isLeapYear(y))
      return 29;
    return daysInMonth[m];
  }
  long long toTotalDays() const {
    int m = _month;
    int y = _year;
    if (m <= 2) {
      m += 12;
      y -= 1;
    }
    return (365 * y) + (y / 4) - (y / 100) + (y / 400) + (153 * m - 457) / 5 +
           _day - 306;
  }
  void addOneDay() {
    _day++;
    if (_day > getDaysInCurrentMonth(_month, _year)) {
      _day = 1;
      _month++;
      if (_month > 12) {
        _month = 1;
        _year++;
      }
    }
  }
  void subtractOneDay() {
    _day--;
    if (_day == 0) {
      _month--;
      if (_month == 0) {
        _month = 12;
        _year--;
      }
      _day = getDaysInCurrentMonth(_month, _year);
    }
  }

public:
  Date() : _day(1), _month(1), _year(1900) {}
  Date(string dateStr) {
    stringstream ss(dateStr);
    char slash;
    int d, m, y;
    ss >> d >> slash >> m >> slash >> y;
    if (y < 0 || m < 1 || m > 12) {
      cout << "Error: Ngay khong hop le! Set ve mac dinh 1/1/2000" << endl;
      _day = 1;
      _month = 1;
      _year = 2000;
      return;
    }
    int maxDay = (m == 2 && ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)))
                     ? 29
                     : daysInMonth[m];
    if (d < 1 || d > maxDay) {
      cout << "Error: Ngay khong hop le! Set ve mac dinh 1/1/2000" << endl;
      _day = 1;
      _month = 1;
      _year = 2000;
      return;
    }
    _day = d;
    _month = m;
    _year = y;
  }
  Date addDays(int n) {
    Date res = *this;
    if (n > 0) {
      for (int i = 0; i < n; i++)
        res.addOneDay();
    } else {
      for (int i = 0; i < -n; i++)
        res.subtractOneDay();
    }
    return res;
  }
  int distanceTo(const Date &other) {
    return abs(this->toTotalDays() - other.toTotalDays());
  }
  void print() { cout << _day << "/" << _month << "/" << _year << endl; }
};

// Cau 2
class Node {
public:
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};
class BST {
private:
  Node *root;
  Node *insertRec(Node *node, int val) {
    if (node == nullptr) {
      return new Node(val);
    }
    if (val < node->data)
      node->left = insertRec(node->left, val);
    else if (val > node->data)
      node->right = insertRec(node->right, val);
    return node;
  }
  Node *minValueNode(Node *node) {
    Node *current = node;
    while (current && current->left != nullptr)
      current = current->left;
    return current;
  }
  Node *deleteRec(Node *root, int val) {
    if (root == nullptr)
      return root;
    if (val < root->data)
      root->left = deleteRec(root->left, val);
    else if (val > root->data)
      root->right = deleteRec(root->right, val);
    else {
      if (root->left == nullptr) {
        Node *temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node *temp = root->left;
        delete root;
        return temp;
      }
      Node *temp = minValueNode(root->right);
      root->data = temp->data;
      root->right = deleteRec(root->right, temp->data);
    }
    return root;
  }
  void inorderRec(Node *root) {
    if (root != nullptr) {
      inorderRec(root->left);
      cout << root->data << " ";
      inorderRec(root->right);
    }
  }

public:
  BST() { root = nullptr; }
  void insert(int val) { root = insertRec(root, val); }
  void remove(int val) { root = deleteRec(root, val); }
  void printTree() {
    inorderRec(root);
    cout << endl;
  }
};
int main() {
  cout << "=== DEMO DATE ===" << endl;
  Date d1("28/02/2024");
  cout << "Ngay ban dau: ";
  d1.print();
  Date d2 = d1.addDays(3);
  cout << "Sau khi them 3 ngay: ";
  d2.print();
  Date d3("05/03/2024");
  cout << "Khoang cach tu 02/03 den 05/03 la: " << d2.distanceTo(d3) << " ngay."
       << endl;
  cout << "\n=== DEMO BST ===" << endl;
  BST tree;
  tree.insert(40);
  tree.insert(3);
  tree.insert(30);
  tree.insert(60);
  tree.insert(55);
  tree.insert(78);
  tree.insert(70);
  tree.insert(90);
  cout << "Cay ban dau (LNR): ";
  tree.printTree();
  cout << "Xoa node 60 (Node 2 con): ";
  tree.remove(60);
  tree.printTree();
  return 0;
}