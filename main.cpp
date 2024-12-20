#include "CalcList.hpp"
#include <iostream>

int main()
{
    CalcList calculator;
    bool active = true;

    while (active)
    {
        std::cout << "\na: Add new operation.\n"
                  << "d: Delete previous operation.\n"
                  << "t: View current total.\n"
                  << "s: View formatted string of all operations.\n"
                  << "e: Exit program.\n"
                  << "\nEnter desired operation code: ";
        char code;
        std::cin >> code;

        switch (code)
        {
        case 'a':   // add new operation
        {
            char func;
            std::cout << "Enter function (+, -, *, /): ";
            std::cin >> func;

            double value;
            std::cout << "Enter value: ";
            std::cin >> value;

            switch (func)
            {
            case '+':
            {
                calculator.newOperation(ADDITION, value);
                break;
            }
            case '-':
            {
                calculator.newOperation(SUBTRACTION, value);
                break;
            }
            case '*':
            {
                calculator.newOperation(MULTIPLICATION, value);
                break;
            }
            case '/':
            {
                if (value == 0)
                {
                    std::cout << "Error: Division by zero is not allowed.\n";
                    continue;
                }
                calculator.newOperation(DIVISION, value);
                break;
            }
            default:
            {
                std::cout << "Error: Invalid function. Please enter +, -, *, or /.\n";
                continue;
            }
            }

            std::cout << "Current total: " << calculator.total() << "\n";
            break;
        }
        case 'd':   // delete previous opeartion
        {
            try
            {
                calculator.removeLastOperation();
                std::cout << "Last operation removed.\n";
            }
            catch (const std::exception& e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 't':   // display current total
        {
            std::cout << "Current total: " << calculator.total() << "\n";
            break;
        }
        case 's':   // display operation history
        {
            std::cout << "\nOperation history:\n" << calculator.toString(2) << "\n";
            break;
        }
        case 'e':   // exit
        {
            active = false;
            std::cout << "Exited calculator.\n";
            break;
        }
        default:
        {
            std::cout << "Error: Invalid code.\n";
            break;
        }
        }
    }

    return 0;
}
