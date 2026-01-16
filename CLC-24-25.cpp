// #include "library.h"
// // Cau 1
// - Struct: Members are public by default. Inheritance is public by default.
// - Class: Members are private by default. Inheritance is private by default.

// // Cau 2

// Circle Constructor
// 1st point constructor
// 2st point constructor
// Circle: 12.56
// Point destructor
// Circle destructor
// Point destructor

// #include <iostream>
// #include <string>

// using namespace std;

// // 1. Class Figure (Lớp cha)
// class Figure {
// protected:
//     string _name;
// public:
//     virtual void showFigure() {
//         cout << _name << endl;
//     }
//     virtual double calcArea() = 0; // Pure virtual function
// };

// // 2. Class Point
// class Point {
// private:
//     int _x, _y;
// public:
//     // Constructor có tham số (Output: 1st point constructor)
//     Point(int x, int y) {
//         cout << "1st point constructor" << endl;
//         _x = x;
//         _y = y;
//     }

//     // Copy Constructor (Output: 2nd point constructor)
//     // -> Đây là hàm em bị thiếu khi trace code
//     Point(const Point& I) {
//         cout << "2nd point constructor" << endl;
//         _x = I._x;
//         _y = I._y;
//     }

//     void setX(int x) { _x = x; }
//     void setY(int y) { _y = y; }
//     int getX() { return _x; }
//     int getY() { return _y; }

//     // Destructor (Output: Point destructor)
//     ~Point() {
//         cout << "Point destructor" << endl;
//     }
// };

// // 3. Class Circle (Kế thừa Figure)
// class Circle : public Figure {
// private:
//     Point* _I; // Con trỏ Point
//     double _R;
// public:
//     // Setter cho tâm I
//     void setI(const Point& I) {
//         if (_I == nullptr)
//             _I = new Point(I); // <--- DÒNG QUAN TRỌNG: Gọi Copy Constructor
//             của Point
//         else
//             *(_I) = I; // Gọi toán tử gán (Assignment operator)
//     }

//     void setR(double R) {
//         if (R >= 0) _R = R;
//     }

//     double getR() { return _R; }

//     double calcArea() { return 3.14 * _R * _R; }

//     // Constructor của Circle
//     Circle() {
//         cout << "Circle constructor" << endl;
//         _name = "Circle";
//         _I = nullptr;
//         _R = 0;
//     }

//     // Destructor của Circle
//     ~Circle() {
//         // Thứ tự hủy quan trọng:
//         if (_I != nullptr) delete _I; // -> Gọi destructor của Point trước!
//         cout << "Circle destructor" << endl; // -> Sau đó mới in dòng này
//     }

//     void showFigure() {
//         cout << _name << ": " << calcArea() << endl;
//     }
// };

// // 4. Hàm main
// int main() {
//     Circle* c = new Circle(); // 1. Circle constructor
//     Point I(1, 2);            // 2. 1st point constructor

//     c->setI(I);               // 3. 2nd point constructor (Do dòng _I = new
//     Point(I)) c->setR(2);

//     c->showFigure();          // 4. Circle: 12.56

//     delete c;                 // 5. Point destructor (do delete _I)
//                               // 6. Circle destructor

//     return 0;                 // 7. Point destructor (do biến I trong main
//     hủy)
// }

// Cau 3

// #include <iostream>
// using namespace std;

// class Complex {
// private:
//   double real;
//   double imag;

// public:
//   Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
//   Complex operator+(const Complex &other) const {
//     return Complex(real + other.real, imag + other.imag);
//   }
//   Complex operator-(const Complex &other) const {
//     return Complex(real - other.real, imag - other.imag);
//   }
//   Complex operator*(const Complex &other) const {
//     double r = real * other.real - imag * other.imag;
//     double i = real * other.imag + imag * other.real;
//     return Complex(r, i);
//   }
//   friend ostream &operator<<(ostream &os, const Complex &c) {
//     os << c.real;
//     if (c.imag >= 0) {
//       os << " + " << c.imag << "i";
//     } else {
//       os << " - " << -c.imag
//          << "i";
//     }
//     return os;
//   }
//   friend istream &operator>>(istream &is, Complex &c) {
//     cout << "Enter real part: ";
//     is >> c.real;
//     cout << "Enter imaginary part: ";
//     is >> c.imag;
//     return is;
//   }
// };

// Cau 4
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class IDrawStrategy {
public:
  virtual void draw(int width, int height, char brush) const = 0;
  virtual ~IDrawStrategy() {}
};
class SolidDraw : public IDrawStrategy {
public:
  void draw(int width, int height, char brush) const override {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        cout << brush;
      }
      cout << endl;
    }
  }
};
class HollowDraw : public IDrawStrategy {
public:
  void draw(int width, int height, char brush) const override {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
          cout << brush;
        else
          cout << " ";
      }
      cout << endl;
    }
  }
};
class IShape {
protected:
  IDrawStrategy *_drawBehavior;

public:
  IShape() : _drawBehavior(nullptr) {}
  virtual string toString() const = 0;
  virtual ~IShape() {
    if (_drawBehavior)
      delete _drawBehavior;
  }
  void setDrawStrategy(IDrawStrategy *strategy) {
    if (_drawBehavior)
      delete _drawBehavior;
    _drawBehavior = strategy;
  }
  virtual void draw(char brush) const = 0;
};
class Rectangle : public IShape {
protected:
  int _width;
  int _height;

public:
  Rectangle(int w, int h) {
    if (w < 0 || h < 0) {
      throw invalid_argument("Kich thuoc khong duoc am!");
    }
    _width = w;
    _height = h;
  }
  string toString() const override {
    stringstream ss;
    ss << "Rectangle Width=" << _width << ", Height=" << _height;
    return ss.str();
  }
  void draw(char brush) const override {
    if (_drawBehavior) {
      _drawBehavior->draw(_width, _height, brush);
    } else {
      cout << "(Chua thiet lap kieu ve cho hinh nay)" << endl;
    }
  }
};
class Square : public Rectangle {
public:
  Square(int side) : Rectangle(side, side) {}

  string toString() const override {
    stringstream ss;
    ss << "Square Side=" << _width;
    return ss.str();
  }
};
int main() {
  cout << "=== OUTPUT THEO DE BAI ===" << endl;
  try {
    std::vector<IShape *> shapes = {
        new Rectangle(10, 6), new Square(5), new Rectangle(8, 5), new Square(3)
        // new Square(-5)
    };
    for (const IShape *shape : shapes) {
      std::cout << shape->toString() << "\n";
    }
    cout << "\n=== DEMO VE HINH ===" << endl;
    cout << "1. Ve Rectangle (Solid, *):" << endl;
    shapes[0]->setDrawStrategy(new SolidDraw());
    shapes[0]->draw('*');
    cout << "\n2. Ve Square (Hollow, @):" << endl;
    shapes[1]->setDrawStrategy(new HollowDraw());
    shapes[1]->draw('@');

    for (IShape *shape : shapes) {
      delete shape;
    }
    shapes.clear();
  } catch (const exception &e) {
    cerr << "LOI KHOI TAO: " << e.what() << endl;
  }
  return 0;
}
