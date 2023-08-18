#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Functions for appearance 

void printWithTypingEffect(const char* str, int delay) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
        fflush(stdout);
        Sleep(delay);
    }
}

void setBackgroundColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Set the color attributes
    SetConsoleTextAttribute(hConsole, 0xF0);

    // Fill the entire screen buffer with spaces to paint its background
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, coord, &count);
    FillConsoleOutputAttribute(hConsole, 0xF0, cellCount, coord, &count);

    // Reset the cursor position to the top-left
    SetConsoleCursorPosition(hConsole, coord);
}

// Main Functionality

void executeCommand(const char* cmd) {
    printWithTypingEffect("Executing: ", 2);
    printWithTypingEffect(cmd, 2);
    printWithTypingEffect("\n", 2);

    int status = system(cmd);
    if (status == 0) {
        printWithTypingEffect("Command executed successfully.\n", 2);
    }
    else {
        char buffer[50];
        sprintf(buffer, "Failed to execute command. Status: %d\n", status);
        printWithTypingEffect(buffer, 2);
    }
}

void restartExplorer() {
    system("taskkill /f /im explorer.exe");
    printWithTypingEffect("\n", 1);
    printWithTypingEffect("Applying changes and restarting the Windows Shell...\n\n", 1);
    printWithTypingEffect("\nIf the shell does not restart automatically, follow these instructions:\n", 1);
    printWithTypingEffect("\n1. Press CTRL + SHIFT + ESC or CTRL + ALT + DEL and choose Task Manager from the list.", 1);
    printWithTypingEffect("\n2. In Task Manager, click on File in the top-left corner and choose Run new task.", 1);
    printWithTypingEffect("\n3. In the Create new task window, type explorer.exe and press Enter or click OK.", 1);
    printWithTypingEffect("\n4. The Windows shell should now restart, and your desktop icons and taskbar should reappear.", 1);
    printWithTypingEffect("\n\nOnce you've done this, you can close this program.\n", 1);

    Sleep(1000);
    system("C:/windows/Explorer.exe");
}

int main() {
    // Open a new command window
    if (AllocConsole()) {
        SetConsoleTitle("Windows 11 Context Menu Tweak - by Mike Vermeer");
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        freopen("CONIN$", "r", stdin);
    }

    setBackgroundColor();

    // Copyright and startup message
    printWithTypingEffect("Windows 11 Context Menu Tweak\n", 20);
    printWithTypingEffect("This program gives you the option to switch back and forth between the old context menu, that was used in Windows 10, and the new context menu in Windows 11.\n\n", 10);
    
    printWithTypingEffect("This Software has been released under the MIT License\n", 1);
    printWithTypingEffect("Copyright (c) [2023] [Mike Vermeer]\n\n", 25);

    int choice;
    printWithTypingEffect("Choose an option:\n", 2);
    printWithTypingEffect("1. Enable the old context menu\n", 2);
    printWithTypingEffect("2. Disable the old context menu\n", 2);
    printWithTypingEffect("3. Exit\n", 2);
    printWithTypingEffect("> ", 2);
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        executeCommand("reg.exe add \"HKCU\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32\" /f /ve");
        break;
    case 2:
        executeCommand("reg.exe delete \"HKCU\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\" /f");
        break;
    case 3:
        return 0;
    default:
        printWithTypingEffect("Invalid choice!\n", 2);
        return 1;
    }

    restartExplorer();

    return 0;
}