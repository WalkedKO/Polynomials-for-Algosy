#ifndef UI 
#define UI 
#include <vector>
#include "Polynomial.h"
class UI
{
    private:
    std::vector<Polynomial*> polynomials;
    int currentScreen;
    std::string resultStatus;
    Polynomial newPolynomial();
    public:
    UI();
    void mainThread();
    void mainMenuPrint();
    void printList();

    void addPolynomial();
    void operations();
    void calcValue();
    void deletePolynomial();

};
#endif