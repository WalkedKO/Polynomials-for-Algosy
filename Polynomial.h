#ifndef POLY
#define POLY
#include <string>
#include <ostream>
class Polynomial
{
    protected:

    int degreeVal;
    float* coefficients;

    public:

    // Constructor used when someone passes only coefficients
    Polynomial(float* array, int newSize);
    //Copying constructor
    Polynomial(const Polynomial& another);

    // Assigning right Polynomial to this object
    Polynomial& operator=(const Polynomial& newP);

    // Addition of two polynomials, a + b
    friend Polynomial operator+(const Polynomial& left, const Polynomial& right);
    // Substraction of two polynomials a - b
    friend Polynomial operator-(const Polynomial& left, const Polynomial& right);
    // Multiplication of two polynomials
    friend Polynomial operator*(const Polynomial& left, const Polynomial& right);
    
    // Addition with assignment
    Polynomial& operator+=(const Polynomial& right);
    // Substraction with assignment
    Polynomial& operator-=(const Polynomial& right);
    // Multiplication with assignment
    Polynomial& operator*=(const Polynomial& right);

    // Multipilication operators for polynomial with a number
    friend Polynomial operator*(const Polynomial& left, const float& number);
    friend Polynomial operator*(const float& number, const Polynomial& right);
    Polynomial& operator*=(const float& number);
    

    // Calculates the result of polynomial with variable x, using Horner's algorithm, returns the result as float
    float operator()(float x);

    // Used for getting a coefficient
    float& operator[](int index);

    // Returns degree
    int degree();

    std::string toString();
    

    
};
// Returns a string of the polynomial in mathematical notation
std::ostream& operator<<(std::ostream& os, Polynomial thisOne);

#endif