#include <iostream>
// #include <fstream>
#include <iomanip>
#include <windows.h>
// #include <cstring>

using namespace std;

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define WHITE_COLOR "\033[0m"

// can edit this later
struct Song
{
    string title;
    string artist;
    // int duration;
    string genre;
};

void DisplayWelcomeBanner();
void DisplayOptionsMenu();
void DisplayEnterChoicePrompt(int startRange, int endRange);
void DisplayLoading();
void DisplayProgramQuitBanner();
void DisplayInvalidChoiceMessage();

main()
{
    int choice;
    bool shouldQuitProgram = false;

    DisplayWelcomeBanner();

    sleep(2);
    system("cls");
    DisplayLoading();
    while (!shouldQuitProgram)
    {
        DisplayOptionsMenu();
        do
        {
            DisplayEnterChoicePrompt(0, 5);
            cin >> choice;

            if (choice < 0 || choice > 5)
            {
                DisplayInvalidChoiceMessage();
            }
            else if (choice == 5)
            {
                shouldQuitProgram = true;

                cout << GREEN_COLOR << "Exiting program. Goodbye!" << WHITE_COLOR << endl;
                sleep(1);
                system("cls");
                DisplayLoading();
                DisplayProgramQuitBanner();
            }
        } while (choice < 0 || choice > 5);
    }
}

void DisplayWelcomeBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                          W E L C O M E !                         ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayOptionsMenu()
{
    cout << "============================= MENU ===================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [0] Display all playlists                                       ||" << endl;
    cout << "||  [1] Create a new playlist                                       ||" << endl;
    cout << "||  [2] Go to playlist                                              ||" << endl;
    cout << "||  [3] Duplicate playlist                                          ||" << endl;
    cout << "||  [4] Delete playlist                                             ||" << endl;
    cout << "||  [5] Exit Program                                                ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayEnterChoicePrompt(int startRange, int endRange)
{
    cout << "Enter your choice (" << startRange << "-" << endRange << "): ";
}

void DisplayLoading()
{
    cout << endl
         << endl;
    cout << "==============================" << endl;
    cout << "||      L O A D I N G       ||" << endl;
    cout << "==============================" << endl;
    sleep(1);
    system("cls");
}

void DisplayProgramQuitBanner()
{
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||               " << GREEN_COLOR << "P R O G R A M   S U C C E S S F U L L Y" << WHITE_COLOR << "            ||" << endl;
    cout << "||                           " << GREEN_COLOR << "Q U I T !" << WHITE_COLOR << "                              ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayInvalidChoiceMessage()
{
    cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
}