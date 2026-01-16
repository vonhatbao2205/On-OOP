#include <iostream>

// --- Định nghĩa struct Fraction ---
struct Fraction {
    // Khai báo friend để DivisibleFracCounter truy cập được private
    friend struct DivisibleFracCounter;

    // Constructor khởi tạo
    Fraction(int num, int den) : m_num(num), m_den(den) {
        std::cout << "Create.\n";
    }

    // Copy Constructor (Được gọi khi truyền tham trị hoặc copy đối tượng)
    Fraction(const Fraction& f) : m_num(f.m_num), m_den(f.m_den) {
        std::cout << "Copy.\n";
    }

private:
    int m_num, m_den;
};

// --- Định nghĩa Template Counter ---
template <class T> 
struct Counter {
    // [VẤN ĐỀ Ở ĐÂY]: Hàm này nhận tham số 'num' kiểu T (truyền tham trị)
    // -> Nó sẽ tạo ra một bản sao (Copy) của đối tượng khi hàm được gọi.
    void operator()(T num) { 
        m_count += check(num); 
    }

    // Hàm trả về kết quả đếm
    int operator()() { return m_count; }

    // Hàm thuần ảo để kiểm tra điều kiện
    virtual bool check(const T& num) = 0;

protected:
    int m_count = 0;
};

// --- Định nghĩa DivisibleFracCounter ---
struct DivisibleFracCounter : public Counter<Fraction> {
    // Kiểm tra xem tử có chia hết cho mẫu không
    bool check(const Fraction& n) { 
        return n.m_num % n.m_den == 0; 
    }
};

// --- Hàm Main ---
int main() {
    // 1. Tạo mảng: Gọi Constructor 3 lần -> In "Create." 3 lần
    Fraction a[] = { {1, 2}, {3, 3}, {4, 2} };

    int n = sizeof(a) / sizeof(*a);
    DivisibleFracCounter count;

    // 2. Vòng lặp
    for (int i = 0; i < n; i++) {
        // Gọi count(a[i]):
        // Do hàm operator()(T num) nhận tham trị -> Gọi Copy Constructor
        // -> In "Copy." 3 lần tương ứng với 3 phần tử.
        count(a[i]); 
    }

    // 3. In kết quả đếm: {3,3} và {4,2} chia hết -> In "2"
    std::cout << count(); 

    return 0;
}