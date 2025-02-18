#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <numeric> // For std::gcd
using namespace std;

class flo {
private:
    int numerator, denominator;

    void simplify() {
        int _gcd = gcd(numerator, denominator);
        numerator /= _gcd;
        denominator /= _gcd;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    flo(int num = 0, int denom = 1) {
        if (denom == 0) throw invalid_argument("Denominator cannot be zero!");
        numerator = num;
        denominator = denom;
        simplify();
    }

    bool operator==(const flo &other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator!=(const flo &other) const {
        return !(*this == other);
    }

    flo operator+(const flo &other) const {
        return flo(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    flo operator-(const flo &other) const {
        return flo(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    flo operator*(const flo &other) const {
        return flo(numerator * other.numerator, denominator * other.denominator);
    }

    flo operator/(const flo &other) const {
        if (other.numerator == 0) throw invalid_argument("Cannot divide by zero!");
        return flo(numerator * other.denominator, denominator * other.numerator);
    }

    int getNumerator(){
        return numerator;
    }
    int getDenominator(){
        return denominator;
    }

    friend ostream &operator<<(ostream &os, const flo &f) {
        os << f.numerator << "/" << f.denominator;
        return os;
    }
    void print() const {
        cout<< " " << numerator;
        if(denominator != 1) cout << "/" << denominator;
    }
};

#endif // FRACTION_H

