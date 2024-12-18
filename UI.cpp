#include <iostream>
#include "UI.h"
#include "Polynomial.h"
#include <algorithm>
Polynomial UI::newPolynomial()
{
    Polynomial toReturn, firstPoly, secondPoly;
    std::string* words;
    std::string sentence;
    int i;
    int firstIndex, secondIndex;
    char operator;
    while(True)
    {
        i = 0;
        words = new std::string[3];
        std::cout << "Write a calculation using index of a polynomial and operator sign" << std::endl;
        std::cout << "For example: when you want to add first polynomial and third, write 1 + 3 separated by spaces" << std::endl;
        std::cin >> sentence;
        for(char sign : sentence)
        {
            if(i >= 3) break;
            if(sign == ' ') i++;
            else words[i] += sign;
        }
        firstIndex = std::stoi(words[0]);
        operator = words[1][0];
        secondIndex = std::stoi(words[2]);
        if(firstIndex >= polynomials.size() || secondIndex >= polynomials.size())
        {
            std::cout << "Index out of range" << std::endl;
            continue;
        }
        firstPoly = *polynomials[firstIndex];
        secondPoly = *polynomials[secondIndex];
        if(operator == '+') 
        {
            toReturn = firstPoly + secondPoly;
            break;
        }
        else if(operator == '-') 
        {
            toReturn = firstPoly - secondPoly;
            break;
        }
        else if(operator == '*')
        {
            toReturn = firstPoly * secondPoly;
            break;
        }
        else
        {
            cout << "Bad operator" << endl;
        }
    }
    return toReturn;
    

}
UI::UI()
{
    currentScreen = -1;
    resultStatus = "";
}
void UI::mainThread()
{
    while(currentScreen != 4)
    {
        if(currentScreen == -1) mainMenuPrint();
        else if(currentScreen == 0) addPolynomial();
        else if(currentScreen == 1) operations();
        else if(currentScreen == 2) calcValue();
        else if(currentScreen == 3) deletePolynomial();
        else if(currentScreen != 4)
        {
            std::cout << "There's no " << currentScreen << " option!" << std::endl << std::ndl;
            currentScreen = -1;
        }
    }
}
void UI::mainMenuPrint()
{
    printList();
    std::cout << "Instructions: " << std::endl;
    std::cout << "0 - add polynomial" << std::endl;
    std::cout << "1 - operations" << std::endl;
    std::cout << "2 - calculate the value of a polynomial" << std::endl;
    std::cout << "3 - delete a polynomial from the list" << std::endl;
    std::cout << "4 - exit" << std::endl;
    std::cout << std::endl;
    std::cout << resultStatus << std::endl;
    std::cin >> currentScreen;
}
void UI::printList()
{
    std::cout << "Saved polynomials" << std::endl;
    for(int i = 0; i < polynomials.size(); i++) cout << " - " << i << ":  " << (*polynomials)[i] << std::endl;
    std::cout << std::endl;
}
void UI::addPolynomial()
{
    int size;
    float* coefficients;
    float temp;
    while(true)
    {
        std::cout << "Set the new polynomial degree: " << std::endl;
        std::cin >> size;
        if(size >= 0) break;
        else cout << "The degree must be over or equal to 0! " << std::endl;
    }
    coefficients = new float[size + 1];
    for(int i = 0; i <= size; i++)
    {
        std::cout << "Write the coefficient of x^" << i << ": " << std::endl;
        std::cin >> temp;
    }
    Polynomial* newPoly = new Polynomial(coefficients, size);
    resultStatus = "Created a polynomial: " + (*newPoly).toString() +"\n";
    polynomials.push_back(newPoly);
    currentScreen = -1;
}
void UI::operations()
{
    
    int choice;
    Polynomial* toSave;
    while(True)
    {
        printList();
        std::cout << "0 - only calculate" << std::endl;
        std::cout << "1 - calculate and save " << std::endl;
        std::cin >> choice;
        toSave = new Polynomial(newPolynomial());
        if(choice == 1)
        {
            polynomials.push_back(toSave);
            break;
        }
        else if(choice != 0)
        {
            std::cout << "Choose 0 or 1" << std::endl;
        }
    }
    resultStatus = "Result: " + (*toSave).toString();
    currentScreen = -1;
}
void UI::calcValue()
{
    int choice;
    float value;
    while(true)
    {
        printList();
        std::cout << "Choose a polynomial from the list: " << std::endl;
        std::cin >> choice;
        if(choice >= polynomials.size())
        {
            std::cout << "Index out of the range" << std::endl;
            continue;
        }
        break;
    }
    std::cout << "Assign a value to the x" << std::endl;
    std::cin >> value;
    resultStatus = "Value of the polynomial number " + choice + " if the x is " + value + "is: " + (*polynomials[choice])(value);
    currentScreen = -1;

}
void UI::deletePolynomial()
{
    int index;
    while(true)
    {
        printList();
        std::cout << "Choose a polynomial to delete: " << std::endl;
        std::cin >> index;
        if(index >= polynomials.size())
        {
            std::cout << "Index out of the range" << std::endl;
            continue;
        }
        break;
    }
    resultStatus = "Deleted: " + (*polynomials[index]).toString();
    polynomials.erase(polynomials.begin() + index);
    currentScreen = -1;

}