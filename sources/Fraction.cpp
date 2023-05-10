#include "Fraction.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <climits>

namespace ariel{

    Fraction:: Fraction(){
        this->numerator = 0;
        this->denominator = 1;
    }

    Fraction::Fraction(float num){
        this->setNumerator(num*1000);
        this->setDenominator(1000);
        negativeCheck();
        reduce();
    }


    Fraction::Fraction(int numerator,int denominator){
        if(denominator == 0){
            throw std::invalid_argument("Denominator cannot be 0!");
        }
        this->numerator = numerator;
        this->denominator = denominator;
        negativeCheck();
        reduce();
    }

    void Fraction::reduce(){
        int gcd = __gcd(this->getNumerator(),this->getDenominator());
        gcd = abs(gcd);
        this->setNumerator(this->getNumerator()/gcd);
        this->setDenominator(this->getDenominator()/gcd);
    }

    void Fraction::negativeCheck(){
        if(numerator<0 && denominator <0){
            setNumerator(getNumerator()*(-1));
            setDenominator(getDenominator()*(-1));
        }
        else if(numerator>0 && denominator<0){
            setNumerator(getNumerator()*(-1));
            setDenominator(getDenominator()*(-1));
        }
        
    }

    int Fraction::compareTo(const Fraction &other) const{
        float firstNun = fractionToFloat(*this);
        float secondNum = fractionToFloat(other);
        if(firstNun>secondNum){
            return 1;
        }
        else if(firstNun<secondNum){
            return -1;
        }
        return 0;
    }

    float Fraction::fractionToFloat(const Fraction& other){
        float numerator = static_cast<float>(other.getNumerator());
        float denominator = static_cast<float>(other.getDenominator());
        float rv = numerator/denominator;
        return round(rv * 1000) / 1000;
    }

    int Fraction::getNumerator() const{
        return this->numerator;
    }
    
    int Fraction::getDenominator()const{
        return this->denominator;
    }
    void Fraction::setNumerator(int num){
        this->numerator = num;
    }
    void Fraction::setDenominator(int den){
        this->denominator = den;
    }

    std::ostream &operator<<(std::ostream &stream, const Fraction &fraction) {
        stream << fraction.numerator << "/" << fraction.denominator;
        return stream;
    }

    std::istream &operator>>(std::istream &stream,Fraction &fraction) { 
        int num;
        if(stream >> num){
            if (stream >> fraction.denominator){
                if(num > 0 && fraction.denominator < 0){
                fraction.denominator = fraction.denominator * (-1);
                fraction.numerator = num * (-1);
                }
                else if(fraction.denominator < 0 && num < 0){
                fraction.denominator = fraction.denominator * (-1);
                fraction.numerator = num * (-1);
                }
                else{
                    fraction.numerator = num;
                }
            // Both numerator and denominator have been read
            }
            else
            {
            // Only one number has been read
            throw std::runtime_error("Invalid input: Expected two integers separated by space");
            }
        }
        else{
            throw std::runtime_error("Invalid input: Expected a number");
        }
        if (fraction.denominator == 0){
        throw std::runtime_error("Denominator can't be zero");
        }
        fraction.reduce();
        return stream;
    }

    Fraction &Fraction::operator++() {
        this->setNumerator(this->getNumerator()+this->getDenominator());
        this->setDenominator(this->getDenominator());
        reduce();
        return *this;
    }

    Fraction Fraction::operator++(int dummy) { 
        Fraction fracTemp(*this);
        this->setNumerator(this->getNumerator()+this->getDenominator());
        this->setDenominator(this->getDenominator());
        return fracTemp;
    }

    Fraction &Fraction::operator--() { 
        this->setNumerator(this->getNumerator()-this->getDenominator());
        this->setDenominator(this->getDenominator());
        reduce();
        return *this; 
    }

    Fraction Fraction::operator--(int dummy) { 
        Fraction fracTemp(*this);
        this->setNumerator(this->getNumerator()-this->getDenominator());
        this->setDenominator(this->getDenominator());
        return fracTemp;
    }

    Fraction Fraction::operator+(const Fraction& other) const {
        long long num = (long long)this->getNumerator()*(long long)other.denominator + (long long)other.numerator*(long long)this->getDenominator();
        long long den = (long long)this->getDenominator()*(long long)other.denominator;
        if(num>INT_MAX || num < INT_MIN || den> INT_MAX || den< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the add will cause overflow");
        }
        return Fraction((int)num,(int)den);
    }

    Fraction Fraction::operator-(const Fraction& other) const {
        long long num = (long long)this->getNumerator()*(long long)other.denominator - other.numerator*this->getDenominator();
        long long den = (long long)this->getDenominator()*(long long)other.denominator;
        if(num>INT_MAX || num < INT_MIN || den> INT_MAX || den< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the subtraction will cause overflow");
        }
        return Fraction((int)num,(int)den);
    }

    Fraction Fraction:: operator*(const Fraction& other) const {
        long long num = (long long)this->getNumerator()*(long long)other.numerator;
        long long den = (long long)this->getDenominator()*(long long)other.denominator;
        if(num>INT_MAX || num < INT_MIN || den> INT_MAX || den< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the multiplication will cause overflow");
        }
        return Fraction((int)num,(int)den);
    }

    Fraction Fraction:: operator/(const Fraction& other) const {
        long long num = (long long)this->getNumerator()*(long long)other.denominator;
        long long den = (long long)this->getDenominator()*(long long)other.numerator;
        if(den ==0){
            throw std::runtime_error("Denominator cannot be 0!");
        }
        if(num>INT_MAX || num < INT_MIN || den> INT_MAX || den< INT_MIN){
            throw std::overflow_error("Overflow error: the result of the division will cause overflow");
        }
        return Fraction((int)num,(int)den);
    }

    Fraction Fraction:: operator+(float num){
        Fraction f(num);
        return *this + f;
    }

    Fraction Fraction:: operator-(float num){ 
        Fraction f(num);
        return *this - f;
    }

    Fraction Fraction:: operator*(float num){
        Fraction f(num);
        return *this * f;
    }

    Fraction Fraction:: operator/(float num){
        Fraction f(num);
        return *this / f;
    }

    Fraction operator+(float num, const Fraction& other){
        Fraction f(num);
        return f + other;  
    }

    Fraction operator-(float num, const Fraction& other){
        Fraction f(num);
        return f - other;
    }

    Fraction operator*(float num, const Fraction& other){
        Fraction f(num);
        return f * other;
    }

    Fraction operator/(float num, const Fraction& other){
        Fraction f(num);
        return f / other;    
    }

    bool Fraction::operator<(float num){
        Fraction f(num);
        if(this->compareTo(f)<0){
            return true;
        }
        return false;
    }

    bool Fraction::operator<=(float num){
        Fraction f(num);
        if(this->compareTo(f)<=0){
            return true;
        }
        return false;
    }

    bool Fraction::operator>(float num){
        Fraction f(num);
        if(compareTo(f)>0){
            return true;
        }
        return false;
    }

    bool Fraction::operator>=(float num){
        Fraction f(num);
        if(compareTo(f)>=0){
            return true;
        }
        return false;
    }

    bool Fraction::operator==(float num){
        Fraction f(num);
        if(compareTo(f)==0){
            return true;
        }
        return false;
    }

    bool Fraction::operator<(const Fraction& other) const {
        if(compareTo(other)<0){
            return true;
        }
        return false;
    }

    bool Fraction::operator<=(const Fraction& other) const {
        if(compareTo(other)<=0){
            return true;
        }
        return false;
    }

    bool Fraction::operator>(const Fraction& other) const {
        if(compareTo(other)>0){
            return true;
        }
        return false;
    }

    bool Fraction::operator>=(const Fraction& other) const {
        int res = compareTo(other);
        if(res>=0){
            return true;
        }
        else{
            return false;
        }
    }

    bool Fraction::operator==(const Fraction& other) const {
        if(compareTo(other) ==0){
            return true;
        }
        return false;
    }

    bool operator<(float num, const Fraction& other){
        Fraction f(num*1000,1000);
        if(f.compareTo(other)<0){
            return true;
        }
        return false;
    }
    bool operator<=(float num, const Fraction& other){
        Fraction f(num*1000,1000);
        if(f.compareTo(other)<=0){
            return true;
        }
        return false;
    }
    bool operator>(float num, const Fraction& other){
        Fraction f(num*1000,1000);
        if(f.compareTo(other)>0){
            return true;
        }
        return false;
    }
    bool operator>=(float num, const Fraction& other){
        Fraction f(num*1000,1000);
        if(f.compareTo(other)>=0){
            return true;
        }
        return false;
    }
    bool operator==(float num, const Fraction& other){
        Fraction f(num*1000,1000);
        if(f.compareTo(other)==0){
            return true;
        }
        return false;
    }

}