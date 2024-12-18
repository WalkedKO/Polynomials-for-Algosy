#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <ostream>
#include "Polynomial.h"
float Horner(float* coefs, int degree, float x)
{
    if(degree == 0) return coefs[degree];
    else return coefs[degree] + (x * Horner(coefs, degree - 1, x));
}
Polynomial::Polynomial(float* array, int newSize)
{
    degreeVal = newSize;
    coefficients = new float[newSize + 1];
    for(int i = 0; i <= degreeVal; i++) coefficients[i] = array[i];
}
Polynomial::Polynomial(const Polynomial& another)
{
    this->degreeVal = another.degreeVal;
    this->coefficients = new float[this->degreeVal];
    for(int i = 0; i <= this->degreeVal; i++) this->coefficients[i] = another.coefficients[i];
}
Polynomial& Polynomial::operator=(const Polynomial& newP)
{
    this->degreeVal = newP.degreeVal;
    this->coefficients = new float[this->degreeVal];
    for(int i = 0; i <= this->degreeVal; i++) this->coefficients[i] = newP.coefficients[i];
    return *this;
}
Polynomial operator+(const Polynomial& left, const Polynomial& right)
{
    if(left.degreeVal < right.degreeVal)
    {
        for(int i = 0; i <= left.degreeVal; i++) right.coefficients[i] += left.coefficients[i];
        return right;
    } 
    else
    {
        for(int i = 0; i <= left.degreeVal; i++) left.coefficients[i] += right.coefficients[i];
        return left;
    } 
}
Polynomial operator-(const Polynomial& left, const Polynomial& right)
{
    if(left.degreeVal < right.degreeVal)
    {
        for(int i = 0; i <= left.degreeVal; i++) right.coefficients[i] -= left.coefficients[i];
        return right;
    } 
    else
    {
        for(int i = 0; i <= left.degreeVal; i++) left.coefficients[i] -= right.coefficients[i];
        return left;
    } 
}
Polynomial operator*(const Polynomial& left, const Polynomial& right)
{
    int newSize = left.degreeVal + right.degreeVal;
    float* newArray = new float[newSize];
    for(int i = 0; i < newSize; i++)
    {
        newArray[i] = 0.0;
    }
    for(int i = 0; i <= left.degreeVal; i++)
    {
        for(int j = 0; j <= right.degreeVal; j++)
        {
            newArray[i + j] += left.coefficients[i] * right.coefficients[j];
        }
    }
    return Polynomial(newArray, newSize);

}


Polynomial& Polynomial::operator+=(const Polynomial& right)
{
    *this = *this + right;
    return *this;
}
Polynomial& Polynomial::operator-=(const Polynomial& right)
{
    *this = *this - right;
    return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& right)
{
    *this = *this * right;
    return *this;
}


Polynomial operator*(const Polynomial& left, const float& number)
{
    int newSize = left.degreeVal;
    float* newArray = new float[newSize + 1];
    for(int i = 0; i <= newSize; i++)
    {
        newArray[i] = left.coefficients[i] * number;
    }
    return Polynomial(newArray, newSize);

}
Polynomial operator*(const float& number, const Polynomial& right)
{
    return right * number;
}
Polynomial& Polynomial::operator*=(const float& number)
{
    *this = *this * number;
    return *this;
}


float Polynomial::operator()(float x)
{
    float* cpOfCoefs = new float[this->degreeVal + 1];
    for(int i = 0; i <= this->degreeVal; i++)
    {
        cpOfCoefs[degreeVal - i] = this->coefficients[i];
    }
    int cpOfDegree = this->degreeVal;
    return Horner(cpOfCoefs, cpOfDegree, x);
}
float& Polynomial::operator[](int index)
{
    return coefficients[index];
}
int Polynomial::degree()
{
    return degreeVal;
}

std::string Polynomial::toString()
{
    std::string result = "";
    for(int i = 0; i <= degree(); i++)
    {
        if(i != degree())  result = result + "(" + std::to_string(coefficients[degree() - i]) + ")" + " * ( x ^ " + std::to_string(degree() - i) + ") + ";
        else result += std::to_string(coefficients[degree() - i]);
    }
    return result;
}


std::ostream& operator<<(std::ostream& os, Polynomial thisOne)
{
    std::string toPass = "";
    for(int i = 0; i <= thisOne.degree(); i++)
    {
        if(i != thisOne.degree())  os << "(" << thisOne[thisOne.degree() - i] << ")" << " * ( x ^ " << thisOne.degree() - i << ") + ";
        else os << thisOne[thisOne.degree() - i];
    }
    return os;
}
