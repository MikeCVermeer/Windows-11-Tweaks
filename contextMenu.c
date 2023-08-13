#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void executeCommand(const char* cmd) {
    printf("Executing: %s\n", cmd); // Print the exact command being executed
    int status = system(cmd);
    if (status == 0) {
        printf("Command executed successfully.\n");
    }
    else {
        printf("Failed to execute command. Status: %d\n", status);
    }
}

void restartExplorer() {
    system("taskkill /f /im explorer.exe");

    printf("\n");

    printf("Applying changes and resarting the Windows Shell...");

    printf("\n");
    printf("\n");

    printf("\nIf the shell does not restart automatically, follow these instructions:\n");
    printf("\n1. Press CTRL + SHIFT + ESC or CTRL + ALT + DEL and choose Task Manager from the list.");
    printf("\n2. In Task Manager, click on File in the top-left corner and choose Run new task.");
    printf("\n3. In the Create new task window, type explorer.exe and press Enter or click OK.");
    printf("\n4. The Windows shell should now restart, and your desktop icons and taskbar should reappear.");
    printf("\n\nOnce you've done this, you can close this program.\n");

    Sleep(1000);
    system("C:/windows/Explorer.exe");
}

int main() {
    // Open a new command window
    if (AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
        freopen("CONIN$", "r", stdin);
    }

    int choice;
    printf("Choose an option:\n");
    printf("1. Enable the old context menu\n");
    printf("2. Disable the old context menu\n");
    printf("3. Exit\n");
    printf("> ");
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
        printf("Invalid choice!\n");
        return 1;
    }

    restartExplorer();

    return 0;
}