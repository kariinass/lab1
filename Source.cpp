#include <iostream>
#include <string>
#include <bitset>
#include <limits>
#include <stdexcept>

class BinaryCalculator {
private:
    int bitSize; 

    void validateInput(int num) { 
        int maxValue = 2 ^ bitSize - 1;
        if (num > maxValue || num < 0) {
            throw std::overflow_error("Input number exceeds bit size limit");
        }
    }

    int toBinary(int num) {
        return std::bitset<32>(num).to_ulong();
    }

public:
    BinaryCalculator(int bitSize) : bitSize(bitSize) {}

    void add(int a, int b) {
        validateInput(a);
        validateInput(b);

        int result = a + b;
        validateInput(result);

        std::cout << "Decimal input: " << a << " + " << b << std::endl;
        std::cout << "Binary result: " << std::bitset<32>(result).to_string().substr(32 - bitSize) << std::endl;
    }

    void subtract(int a, int b) {
        validateInput(a);
        validateInput(b);

        int result = a - b;
        if (result < 0) {
            throw std::overflow_error("Result is negative, cannot represent in unsigned binary");
        }

        std::cout << "Decimal input: " << a << " - " << b << std::endl;
        std::cout << "Binary result: " << std::bitset<32>(result).to_string().substr(32 - bitSize) << std::endl;
    }

    void multiply(int a, int b) {
        validateInput(a);
        validateInput(b);

        int result = a * b;
        validateInput(result);

        std::cout << "Decimal input: " << a << " * " << b << std::endl;
        std::cout << "Binary result: " << std::bitset<32>(result).to_string().substr(32 - bitSize) << std::endl;
    }
};

int main() {
    int bitSize;
    std::cout << "Enter the bit size: ";
    std::cin >> bitSize;

    BinaryCalculator calculator(bitSize);

    while (true) {
        int choice;
        int a, b;
        std::cout << "\nChoose an operation:\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Exit\n";
        std::cin >> choice;

        if (choice == 4) break;

        std::cout << "Enter two decimal numbers: ";
        std::cin >> a >> b;

        try {
            switch (choice) {
            case 1:
                calculator.add(a, b);
                break;
            case 2:
                calculator.subtract(a, b);
                break;
            case 3:
                calculator.multiply(a, b);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        catch (const std::overflow_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
