// Reference - 
// Division algorithm obtained from psudecode section on
// Wikipedia page - https://en.wikipedia.org/wiki/Polynomial_long_division
// on 31st October 2021
// in (function - quotOrRemainder() - lines 183 - 221)

#include "polynomial.h"
#include "rational.h"
#include <sstream>
#include <utility>
using namespace std;

//default constructor, creates the 0 polynomial
Polynomial::Polynomial() {
    coeffs = new Rational[1];
    capacity = -1;
}

// move-assign constructor, && -> takes rvalue reference
Polynomial& Polynomial::operator=(Polynomial &&other) {
    capacity = other.capacity;
    delete[] coeffs;
    coeffs = other.coeffs;
    other.coeffs = nullptr;
    return *this;
}

// copy-assign constructor, & -> takes lvalue reference
Polynomial& Polynomial::operator=(const Polynomial &other) { 
    Polynomial copy(other);
    std::swap(capacity, copy.capacity);
    std::swap(coeffs, copy.coeffs);
    return *this;
}

// move constructor - &&
Polynomial :: Polynomial(Polynomial &&other) {
    coeffs = other.coeffs;
    capacity = other.capacity;
    other.coeffs = nullptr;
}

// copy constructor - &
Polynomial::Polynomial(const Polynomial &other) { 
    capacity = other.capacity;
    coeffs = new Rational[capacity + 1];
    for (int i = 0; i <= capacity; i++) {
        coeffs[i] = other.coeffs[i];
    }
}

// Destructor
Polynomial::~Polynomial() {
    delete[] coeffs;
    coeffs = nullptr;
}

// degree() returns the degree (integer) of the polynomial
// according to capacity (if capacity = -1, degree = 0)
int Polynomial::degree() const {
    if(capacity == -1) return 0;
    return capacity;
}

// Overloaded + operator, will add two polynmoials 
// according to exponents and return an integer
Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    int limit = capacity;
    int lower = rhs.capacity;
    Rational sum;
    Polynomial temp;
    if(rhs.capacity > limit) {
        limit = rhs.capacity;
        lower = capacity;
    }
    delete[] temp.coeffs;
    temp.coeffs = new Rational[limit + 1];
    for(int i = limit; i >= 0; i--) {
        sum.num = 0;
        sum.den = 1;
        // CASE: rhs is of lower degree
        if(rhs.capacity < capacity) {
            if(i <= lower) {
                sum = coeffs[i] + rhs.coeffs[i];    
            }
            else {
                sum = coeffs[i];
            }
        }
        // CASE: this is of lower degree
        else if(rhs.capacity > capacity) {
            if(i <= lower) {
                sum = coeffs[i] + rhs.coeffs[i];    
            }
            else {
                sum = rhs.coeffs[i];
            }
        }
        // CASE 3: degrees of rhs and this are equal
        else {
            sum = coeffs[i] + rhs.coeffs[i]; 
        }
        // Assigning sum of rationals from current iteration 
        // of loop to the return Polynomial object
        temp.coeffs[i] = sum;
    }
    
    temp.capacity = limit;
    return temp;
}


// Overloaded - operator, will add subtract polynmoials 
// according to exponents and return an integer
Polynomial Polynomial::operator-(const Polynomial &rhs) const {
    int limit = capacity;
    int lower = rhs.capacity;
    Rational sum;
    Polynomial temp;
    if(rhs.capacity > limit) {
        limit = rhs.capacity;
        lower = capacity;
    }
    delete[] temp.coeffs;
    temp.coeffs = new Rational[limit + 1];
    for(int i = limit; i >= 0; i--) {
        sum.num = 0;
        sum.den = 1;
        // CASE: rhs is of lower degree
        if(rhs.capacity < capacity) {
            if(i <= lower) {
                sum = coeffs[i] - rhs.coeffs[i];    
            }
            else {
                sum = coeffs[i];
            }
        }
        // CASE: this is of lower degree
        else if(rhs.capacity > capacity) {
            if(i <= lower) {
                sum = coeffs[i] - rhs.coeffs[i];    
            }
            else {
                sum.num = rhs.coeffs[i].num * -1;
                sum.den = rhs.coeffs[i].den;
            }
        }
        // CASE 3: degrees of rhs and this are equal
        else {
            sum = coeffs[i] - rhs.coeffs[i]; 
        }
        temp.coeffs[i] = sum;
    }
    
    temp.capacity = limit;

    return temp;
}

// Overloaded * operator, will multiply polynmoials 
// according to exponents and return an integer
Polynomial Polynomial::operator*(const Polynomial &rhs) const {
    int limit = capacity;
    Rational prod;
    Polynomial temp;
    int addToIndex;
    temp.capacity = capacity + rhs.capacity;
    delete[] temp.coeffs;
    temp.coeffs = new Rational[temp.capacity + 1];

    for(int i = 0; i <= capacity; i++) {
        for(int j = 0; j <= rhs.capacity; j++) {
            addToIndex = i + j;
            temp.coeffs[addToIndex] += (coeffs[i] * rhs.coeffs[j]);
        }
    }

    return temp;
}

// Called from overloaded '/' or '%' functions,
// returns remainder or quotient depending on value of symbol
Polynomial quotOrRemainder(const Polynomial &lhs, const Polynomial &rhs, char symbol) {
    Polynomial quotient;
    quotient.capacity = lhs.capacity - rhs.capacity;
    delete[] quotient.coeffs;
    quotient.coeffs = new Rational[quotient.capacity + 1];

    Polynomial dividend = lhs;

    // checking if denominator was zero
    int goDivision = 1;
    if(rhs.coeffs[rhs.capacity].num == 0) {
        delete[] quotient.coeffs;
        quotient.coeffs = new Rational[1];
        quotient.coeffs[0].num = 1;
        quotient.coeffs[0].den = 1;
        delete[] dividend.coeffs;
        dividend.coeffs = new Rational[1];
        dividend.coeffs[0].num = 0;
        dividend.coeffs[0].den = 1;
        goDivision = 0;
    }

    if(goDivision){
        Polynomial intermediate;
        while (dividend.capacity >= rhs.capacity) {
            int exponent = dividend.capacity - rhs.capacity;
            intermediate.capacity = exponent;
            delete[] intermediate.coeffs;
            intermediate.coeffs = new Rational[intermediate.capacity + 1];
            intermediate.coeffs[exponent] = 
                dividend.coeffs[dividend.capacity] / rhs.coeffs[rhs.capacity];
            dividend = dividend - (intermediate * rhs);
            quotient = quotient + intermediate;
            dividend.capacity--;
        }
    }
    if(symbol == '/') return quotient;
    else return dividend;
}

// Overloaded / operator, will add divide polynmoials 
// and return quotient according to exponents and return an integer
Polynomial Polynomial::Polynomial::operator/(const Polynomial &rhs) const {
    return quotOrRemainder(*this, rhs, '/');
}

// Overloaded % operator, will add divide polynmoials 
// and return remainder according to exponents and return an integer
Polynomial Polynomial::Polynomial::operator%(const Polynomial &rhs) const {
    return quotOrRemainder(*this, rhs, '%');
}


// Print with decresing exponents.
std::ostream& operator<<(std::ostream& out, const Polynomial &poly) {
    if(poly.capacity == -1) {
        cout << "0";
        return out;
    }
    if((poly.capacity == 1) && poly.coeffs[0].num == 0) {
        cout << "0";
        return out;
    }
    int zeroFlag = 1;
    for(int i = poly.capacity; i >= 0; i--) {
        if(poly.coeffs[i].num != 0) zeroFlag = 0;
    }
    if(zeroFlag) {
        cout << 0;
        return out;
    }

    // reduce capacity if starting terms are zeroes -
    // (if the polynomial starts with zeroes)
    int reduceCapacityBy = 0;
    for(int k = poly.capacity; k >= 0; k--) {
        if(poly.coeffs[k].num == 0) reduceCapacityBy++;
        else break;
    }

    int tempCapacity = poly.capacity - reduceCapacityBy;

    for(int i = tempCapacity; i >= 0; i--) {
        if(poly.coeffs[i].num == 0) continue; 
        if(i != tempCapacity) cout << " + "; 
        if(i == 1) cout << "(" << poly.coeffs[i] << ")x"; 
        else if(i == 0) cout << "(" << poly.coeffs[i] << ")";
        else cout << "(" << poly.coeffs[i] << ")x^" << i;
    }
    return out;
}

// Read until newline consisting of one polynomial in specified format
std::istream& operator>>(std::istream& in, Polynomial &poly) {
    int exp;
    string input;
    Rational temp;
    getline(cin, input);
    istringstream customIn {input};
    customIn >> temp >> exp;

    poly.capacity = exp;
    delete[] poly.coeffs;
    poly.coeffs = new Rational[poly.capacity + 2];
    poly.coeffs[exp] = temp;
    int limit = exp;

    while(customIn >> temp >> exp) {
        poly.coeffs[exp] = temp;
    }
    return in;
}