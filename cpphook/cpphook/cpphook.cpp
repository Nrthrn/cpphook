#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h>
#include <string>
#include <Lmcons.h>    // For UNLEN and MAX_COMPUTERNAME_LENGTH

#pragma comment(lib, "ws2_32.lib")

namespace var {
    int input = 0;
}

std::string getUserAndComputerName() {
    // Buffers for user name and computer name
    char username[UNLEN + 1] = { 0 };                // Zero-initialize
    char computername[MAX_COMPUTERNAME_LENGTH + 1] = { 0 };

    // Sizes for the buffers
    DWORD username_len = UNLEN + 1;
    DWORD computername_len = MAX_COMPUTERNAME_LENGTH + 1;

    // Get the current user name
    if (!GetUserNameA(username, &username_len)) {    // Use GetUserNameA for ANSI
        return "Failed to get user name";
    }

    // Get the computer name
    if (!GetComputerNameA(computername, &computername_len)) {    // Use GetComputerNameA for ANSI
        return "Failed to get computer name";
    }

    // Return formatted "username@computername"
    return std::string(username) + "@" + std::string(computername);
}

std::string getLocalIPAddress() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return "0.0.0.0"; // Return a default value on failure
    }

    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        std::cerr << "gethostname failed." << std::endl;
        WSACleanup();
        return "0.0.0.0"; // Return a default value on failure
    }

    struct addrinfo hints, * info;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Use IPv4
    hints.ai_socktype = SOCK_STREAM;

    int result = getaddrinfo(hostname, NULL, &hints, &info);
    if (result != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(result) << std::endl;
        WSACleanup();
        return "0.0.0.0"; // Return a default value on failure
    }

    // Convert the first valid address to a string
    char ip[INET_ADDRSTRLEN];
    struct sockaddr_in* ipv4 = reinterpret_cast<struct sockaddr_in*>(info->ai_addr);
    inet_ntop(AF_INET, &ipv4->sin_addr, ip, sizeof(ip));

    freeaddrinfo(info); // Free the linked list allocated by getaddrinfo
    WSACleanup(); // Clean up Winsock
    return std::string(ip);
}

void centeredText(const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int padding = (consoleWidth - text.length()) / 2;

    std::cout << std::string(padding, ' ') << text << std::endl;
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

void menu() {
    std::string mainMenu = R"(
                CPPHook
                     .-.
               .'   `.
               :g g   :
               : o    `.
              :         ``.
             :             `.
            :  :         .   `.
            :   :          ` . `.
             `.. :            `. ``;
                `:;             `:' 
                   :              `.
                    `.              `.     .
                      `'`'`'`---..,___`;.-'
            [1] Read Mem      [2] Device Info

            Input: )";

    std::cout << mainMenu;

    std::cin >> var::input;

    switch (var::input) {
    case 1: {
        system("cls");

        void* mem_ptr = read_mem();

        // Check if the pointer is valid before dereferencing
        if (mem_ptr) {
            int value = *reinterpret_cast<int*>(mem_ptr);
            std::cout << "Value at address: " << std::hex << mem_ptr << " is " << value << std::endl;
        }
        else {
            std::cout << "Invalid memory address." << std::endl;
        }
        std::cout << "\nPress enter to continue..." << std::endl;
        while (_getch() != '\r');
        system("cls");
        menu();
        break;
    }
    case 2: {
        system("cls");

        std::string ip = getLocalIPAddress();
        std::string user = getUserAndComputerName();

        std::string info = R"(
                    .-.                        USER: )" + user + R"(
               .'   `.                         IP: )" + ip + R"(
               :g g   :
               : o    `.
              :         ``.
             :             `.
            :  :         .   `.
            :   :          ` . `.
             `.. :            `. ``;
                `:;             `:' 
                   :              `.
                    `.              `.     .
                      `'`'`'`---..,___`;.-'
            )";

        std::cout << info;
        std::cout << "\nPress enter to continue..." << std::endl;
        while (_getch() != '\r');
        system("cls");
        menu();
        break;
    }
    default:
        std::cout << "Invalid option. Please select again." << std::endl;
        break;
    }
}

int main() {
    while (true) {
        menu();
    }
}
