#include "library.h"

//Câu 1
class Mobile {
private:
	string code;
	string name;
	string brand;
	string date;
public:
	Mobile() : code(""), name(""), brand(""), date("") {}
	Mobile(string c, string n, string b, string d) : code(c), name(n), brand(b), date(d) {}
	bool operator==(const Mobile& other) const {
		return this->date == other.date;
	}
	bool operator<(const Mobile& other) const {
		return this->date < other.date;
	}
	bool operator!=(const Mobile& other) const {
		return !(*this == other);
	}
	bool operator>(const Mobile& other) const {
		return other < *this;
	}
	bool operator<=(const Mobile& other) const {
		return !(*this > other);
	}
	bool operator>=(const Mobile& other) const {
		return !(*this < other);
	}
	friend istream& operator>>(istream& in, Mobile& m) {
		cout << "Enter code: ";
		getline(in, m.code);
		cout << "Enter name: ";
		getline(in, m.name);
		cout << "Enter brand: ";	
		getline(in, m.brand);
		cout << "Enter date (YYYY-MM-DD): ";
		getline(in, m.date);
		return in;
	}
	friend ostream& operator<<(ostream& out, const Mobile& m) {
		out << "Code: " << m.code << ", Name: " << m.name << ", Brand: " << m.brand << ", Date: " << m.date;
		return out;
	}
};

//Câu 2
/*Testing 1: 
Base::Base(int) //x(5)
Derived::Derived(int) //x(5)
Base::Base() //y(3,7)
Derived::derived(int, int) //y(3,7)
Testing 2: 
Base::Base(const Base&) //Derived second
Derived::Derived(const Derived&) //Derived second
Testing 3:
Base::Base() //Derived x
Derived::Derived() //Derived x
Derived::operator=() //x=second
Derived::doSth(int) //first.doSth
Base::doSthE(int) //first.doSthE
Testing 4:
Derived::doSth(int) //x.doSth
Derived::doSthE(int) //x.doSthE
Derived::~Derived() // local x in testing()
Base::~Base()
Derived::~Derived() // local second in testing()
Base::~Base()
Testing 5:
Derived::~Derived() // y in main
Base::~Base()
Derived::~Derived() // x in main
Base::~Base()*/

/*class Base {
public:
    Base() {
        cout << "Base::Base()" << endl;
    }
    Base(int t) {
        cout << "Base::Base(int)" << endl;
    }
    Base(int t, int k) {
        cout << "Base::Base(int,int)" << endl;
    }
    Base(const Base& src) {
        cout << "Base::Base(const Base&)" << endl;
    }
    Base& operator=(const Base& src) {
        cout << "Base::operator=()" << endl;
        return *this;
    }
    virtual void doSth(int x) {
        cout << "Base::doSth(int)" << endl;
    }
    void doSthE(int x) {
        cout << "Base::doSthE(int)" << endl;
    }
    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};
class Derived : public Base {
public:
    Derived() {
        cout << "Derived::Derived()" << endl;
    }
    Derived(int t) : Base(t) {
        cout << "Derived::Derived(int)" << endl;
    }
    Derived(int t, int k) {
        cout << "Derived::Derived(int, int)" << endl;
    }
    Derived(const Derived& src) : Base(src) {
        cout << "Derived::Derived(const Derived&)" << endl;
    }
    Derived& operator=(const Derived& src) {
        cout << "Derived::operator=()" << endl;
        return *this;
    }
    void doSth(int x) {
        cout << "Derived::doSth(int)" << endl;
    }
    void doSthE(int x) {
        cout << "Derived::doSthE(int)" << endl;
    }
    ~Derived() {
        cout << "Derived::~Derived()" << endl;
    }
};
void testing(Base& first, Derived second) {
    cout << "Testing 3: " << endl;
    Derived x;
    x = second; 
    first.doSth(1);  
    first.doSthE(2);
    cout << "Testing 4: " << endl;
    x.doSth(3);
    x.doSthE(4);
}
int main() {
    cout << "Testing 1: " << endl;
    Derived x(5), y(3, 7);
    cout << "Testing 2: " << endl;
    testing(x, y);
    cout << "Testing 5: " << endl;
    return 0;
}*/

