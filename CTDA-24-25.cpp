//#include "library.h"
///* Câu 1
//- Static data members
//+ Thuộc về lớp 
//+ Khởi tạo ngoài hàm
//+ Có thể gọi tên qua tên lớp
//+ Nhiều đối tượng có thể thể truy cập
//- Non-static data members
//+ Thuộc về đối tượng
//+ Khởi tạo thông qua hàm tạo của đối tượng
//+ Phải gọi tên thông qua đối tượng
//+ Mỗi đối tượng có một bản sao riêng biệt
//*/
//
///* Câu 2
//Point constructor // Point(1,2)
//Shape paremeter constructor //Shape("Rectangle")
//Point copy constructor // _topLeft(p)
//Rectangle constructor // Rectangle(Point(1,2),4,5)
//Point destructor // After end line 56
//Shape default constructor //Shape* s = new Rectangle(rec1)
//Point constructor // _topLeft = p._width
//Rectangle copy constructor // new Rectangle(rec1)
//Rectangle : 20 // s->display -> display() of class Rectangle, 20 because it call area() with virtual so it is area() of class Rectangle which is child of class Shape
//Rectangle destructor // delete s -> call ~Rectangle()
//Point destructor // After call ~Rectangle then call ~Point()
//Shape destructor // After call ~Rectangle then call ~Shape()
//Rectangle destructor // Main end then rec1 deleted
//Point destructor // After Rectangle destructor
//Shape destructor // After Rectangle destructor
//*/
//
///*Câu 3
//class Computered
//{
//private:
//	string brand;
//	int ram;
//	float cpu;
//public:
//	float getPerformanceScore() const{
//		return ram * cpu;
//	}
//	bool operator==(const Computered& other)const {
//		return this->getPerformanceScore() == other.getPerformanceScore();
//	}
//	bool operator!=(const Computered& other)const {
//		return !(*this == other);
//	}
//	bool operator<(const Computered& other)const {
//		return this->getPerformanceScore() < other.getPerformanceScore();
//	}
//	bool operator>(const Computered& other) const {
//		return other < *this;
//	}
//	bool operator<=(const Computered& other) const {
//		return !(other<*this);
//	}
//	bool operator>=(const Computered& other)const {
//		return !(*this < other);
//	}
//	friend istream& operator>>(istream& in, Computered& comp)
//	{
//		cout << "Brand: ";
//		in >> comp.brand;
//		cout << "RAM (GB): ";
//		in >> comp.ram;
//		cout << "CPU (GHz): ";
//		in >> comp.cpu;
//		return in;
//	}
//	friend ostream& operator<<(ostream& out, const Computered& comp)
//	{
//		out << "Brand: " << comp.brand << ", RAM: " << comp.ram << "GB, CPU: " << comp.cpu << "GHz";
//		return out;
//	}
//};*/
//
////Câu 4
///*classDiagram
//class Expected_T {
//	+bool success
//		+ string message
//		+ T data
//}
//
//class Validator {
//	<< interface >>
//		+validate(string input)* Expected~int~
//		+clone()* Validator*
//}
//
//class ValidIntegerFormatValidator {
//	+validate(string input) Expected~int~
//}
//
//class ValidIntegerValuesValidator {
//	-int min
//	- int max
//	+ validate(string input) Expected~int~
//}
//
//class IsPrimeValidator {
//	+validate(string input) Expected~int~
//}
//
//class IntegerRequestUseCase {
//	-vector~Validator * ~validators
//	+ void addValidator(Validator * v)
//	+ nextPrime(string prompt) Expected~int~
//}
//
//class Integer {
//	+static bool isPrime(int number)
//}
//
//Validator <| ..ValidIntegerFormatValidator
//Validator <| ..ValidIntegerValuesValidator
//Validator <| ..IsPrimeValidator
//IntegerRequestUseCase <>-- Validator : contains
//IntegerRequestUseCase ..> Expected_T : uses*/
//
//class Interger
//{
//public:
//	static bool isPrime(int number) {
//		for (int i = 2;i <= sqrt(number);i++) {
//			if (number % i == 0) return false;
//		}
//		return number > 1;
//	}
//};
//template<class T>
//struct Expected
//{
//public:
//	bool success;
//	string message;
//	T data;
//};
//template<class T>
//Expected<T> succeed(T data) {
//	return Expected<T>{ true, "", data };
//}
//template<class T>
//Expected<T> fail(string message) {
//	return Expected<T>{ false, message, T() };
//}
//class Validator
//{
//public:
//	virtual Expected<int> validate(string input) = 0;
//	virtual ~Validator(){}
//	virtual Validator* clone() = 0;
//};
//class ValidintegerFormatValidator : public Validator
//{
//public:
//	Expected<int> validate(string input) override
//	{
//		stringstream ss(input);
//		int val = 0;
//		if (!(ss >> val) || !(ss.eof())) {
//			return fail<int>("Invalid integer format");
//		}
//		return succeed<int>(val);
//	}
//	Validator* clone() override {
//		return new ValidintegerFormatValidator(*this);
//	}
//};
//class IsPrimeValidator : public Validator
//{
//public:
//	Expected<int> validate(string input) override
//	{
//		int number = stoi(input);
//		if (!Interger::isPrime(number)) {
//			return fail<int>("Not a prime number");
//		}
//		return succeed<int>(number);
//	}
//	Validator* clone() override {
//		return new IsPrimeValidator(*this);
//	}
//};
//class ValidIntegerValuesValidator : public Validator
//{
//private:
//	int min, max;
//public:
//	ValidIntegerValuesValidator(int min, int max) : min(min), max(max) {}
//	Expected<int> validate(string input) override
//	{
//		int number = stoi(input);
//		if (number < min || number > max) {
//			return fail<int>("Value out of range");
//		}
//		return succeed<int>(number);
//	}
//	Validator* clone() override {
//		return new ValidIntegerValuesValidator(*this);
//	}
//};
//class IntegerRequestUseCase
//{
//private:
//	vector<Validator*> validators;
//public:
//	Expected<int> nextPrime(string prompt) {
//		cout << prompt;
//		string buffer;
//		getline(cin, buffer);
//		int value = 0;
//		for (Validator* v : validators) {
//			Expected<int> res = v->validate(buffer);
//			if(!res.success){
//				return fail<int>(res.message);
//			}
//			value = res.data;
//		}
//		return succeed<int>(value);
//	}
//	void addValidator(Validator* v) {
//		validators.push_back(v);
//	}
//	IntegerRequestUseCase() {}
//	IntegerRequestUseCase(const IntegerRequestUseCase& other) {
//		for (Validator* v : other.validators) {
//			validators.push_back(v->clone());
//		}
//	}
//	IntegerRequestUseCase& operator=(const IntegerRequestUseCase& other) {
//		if (this != &other) {
//			for (Validator* v : validators) {
//				delete v;
//			}
//			validators.clear();
//			for (Validator* v : other.validators) {
//				validators.push_back(v->clone());
//			}
//		}
//		return *this;
//	}
//	~IntegerRequestUseCase() {
//		for (Validator* v : validators) {
//			delete v;
//		}
//		validators.clear();
//	}
//};
//int main() {
//	int min = 1, max = 100;
//	IntegerRequestUseCase useCase;
//	useCase.addValidator(new ValidintegerFormatValidator());
//	useCase.addValidator(new ValidIntegerValuesValidator(min, max));
//	useCase.addValidator(new IsPrimeValidator());
//
//	stringstream ss;
//	ss << "Please enter a prime number within the range of [" << min << ", " << max << "]: ";
//	string prompt = ss.str();
//
//	auto result = useCase.nextPrime(prompt);
//	if (result.success) {
//		cout << "You entered a prime: " << result.data << endl;
//	}
//	else {
//		cout << "Error: " << result.message << endl;
//	}
//	return 0;
//}
