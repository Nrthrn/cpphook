#include <iostream>
#include <windows.h>
#include <iomanip>
#include <sstream>

namespace var {
    int input = 0;
}

void* read_mem() {
    std::string input;
    std::cout << "Enter the memory address (in hex, e.g., 0x12345678): ";
    std::cin >> input;

    uintptr_t address;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> address;

    void* ptr = reinterpret_cast<void*>(address);
    return ptr;
}


void menu()
{
    std::cout << "              [1] Read Mem\n\nInput: ";

    std::cin >> var::input;

    switch (var::input)
    {
    case 1:
        void* mem_ptr = read_mem();

        int value = *reinterpret_cast<int*>(mem_ptr);
        std::cout << "Value at address: " << std::hex << mem_ptr << " is " << value << std::endl;
        Sleep(2000);
        system("cls");
    }
}

int main()
{
    while (true)
    {
        menu();
    }
}