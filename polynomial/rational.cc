#include <iostream>
#include "rational.h"
using namespace std;

int gcd(int num, int den) {
    if(num < 0) num *= -1;
    if(den < 0) den *= -1;
    int bigger = num;
    if(den >= num) bigger = den;
    int i = bigger - 1;
    while(i > 0) {
        if((den % i == 0) && (num % i == 0)) return i;
        else i--;
    }
    return i;
}

void simplify2(int &num, int &den) {
    int simp = gcd(num, den);
    num /= simp;
    den /= simp;
    if((num < 0 && den < 0) || (den < 0)) {
        num *= -1;
        den *= -1;
    }
}

void Rational::simplify() {
    simplify2(num, den);
}

Rational::Rational(int num, int den) {
    num = 0;
    den = 1;
}

Rational Rational::operator+(const Rational &rhs) const {
    int n = 0;
    int d = 0;
    Rational sum;
    n = (num * rhs.den) + (den * rhs.num);
    d = (den * rhs.den);
    simplify2(n, d);
    sum.num = n;
    sum.den = d;
    return sum;
}


Rational Rational::operator-(const Rational &rhs) const {
    int n = 0;
    int d = 0;
    Rational diff;
    n = (num * rhs.den) - (den * rhs.num);
    d = (den * rhs.den);
    simplify2(n, d);
    diff.num = n;
    diff.den = d;
    return diff;
}

Rational Rational::operator*(const Rational &rhs) const {
    int n = 1;
    int d = 1;
    Rational mult;
    n = (num * rhs.num);
    d = (den * rhs.den);
    simplify2(n, d);
    mult.num = n;
    mult.den = d;
    return mult;
}

Rational Rational::operator/(const Rational &rhs) const {
    int n = 1;
    int d = 1;
    Rational div;
    n = (num * rhs.den);
    d = (den * rhs.num);
    simplify2(n, d);
    div.num = n;
    div.den = d;
    return div;
}

Rational& Rational::operator+=(const Rational &rhs) {
    num = (num * rhs.den) + (den * rhs.num);
    den = (den * rhs.den);
    simplify();
    return *this;
}

Rational& Rational::operator-=(const Rational &rhs) {
    num = (num * rhs.den) - (den * rhs.num);
    den = (den * rhs.den);
    simplify();
    return *this;
}

int Rational::getNumerator() const {
    return num;
}

int Rational::getDenominator() const {
    return den;
}

Rational Rational::operator-() const {
    int n = num;
    int d = den;
    Rational negated;
    if(num < 0 && den < 0) {
        n *= -1;
        d *= -1;
    }
    else if(num < 0 || den < 0) {
        if(num < 0) {
            n *= -1;
        }
        if(den < 0) {
            d *= -1;
            n *= -1;
        }
    }
    else {
        n *= -1;
    } 
    negated.num = n;
    negated.den = d;
    // cout << n << "/" << d << endl;
    return negated;
}

std::ostream &operator<<(std::ostream &out, const Rational &rat) {
    // cout << rat.num << "/" << rat.den;
    if(rat.den == 1) {
      cout << rat.num;
    }
    else if (rat.num == rat.den) {
      cout << 1;
    }
    else if (rat.num == 0) {
      cout << 0;
    }
    else {
       cout << rat.num << "/" << rat.den;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Rational &rat) {
    int num;
    int den;
    char slash = '/';
    in >> num >> slash >> den;
    rat.num = num;
    rat.den = den;
    rat.simplify();
    return in;
}
