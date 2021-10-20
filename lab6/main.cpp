#include <iostream>
#include <string>
#include "TBigInt.hpp"

int main() {
    TBigInt zero("0");
    std::string str1, str2;
    char operation;
    while (std::cin >> str1 >> str2 >> operation) {
        TBigInt num1(str1);
        TBigInt num2(str2);
        if (operation == '+') {
            TBigInt num3 = num1 + num2;
            std::cout << num3 << '\n';
        }
        if (operation == '-') {
            if (num1 < num2) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 - num2 << "\n";
            }
        }
        if (operation == '*') {
            std::cout << num1 * num2 << "\n";
        }
        if (operation == '/') {
            if (num2 == zero) {
                std::cout << "Error\n";
            } else {
                std::cout << num1 / num2 << "\n";
                //(num1 / num2).print();
            }
        }
        if (operation == '^'){
            if (num1 == zero and num2 == zero) {
                std::cout << "Error\n";
            } else {
                TBigInt num3 = num1 ^ num2;
                std::cout << num3 << "\n";
            }
        }
        if (operation == '=') {
            if (num1 == num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
        if (operation == '>') {
            if (num1 > num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
        if (operation == '<') {
            if (num1 < num2) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
    }
}