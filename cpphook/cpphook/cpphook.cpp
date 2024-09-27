#include <iostream>
#include <windows.h>

namespace var {
    int input = 0;
}

void menu()
{
    std::cout << "              [1] Test\n\nInput: ";

    std::cin >> var::input;

    switch (var::input)
    {
    case 1:
        std::cout << "Hello, World!\n";
        Sleep(1000);
        system("cls");
    }
}

int main()
{
    std::cout << "Welcome to CPPHook!\n";
    Sleep(1000);
    std::cout << "Loading.\n";
    Sleep(400);
    std::cout << "Loading..\n";
    Sleep(400);
    std::cout << "Loading...\n";
    Sleep(400);
    system("cls");
    std::cout << "Done!";
    Sleep(100);
    system("cls");

    while (true)
    {
        menu();
    }
}