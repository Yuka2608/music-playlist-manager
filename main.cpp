#include <iostream>
// #include <fstream>
#include <iomanip>
#include <windows.h>
// #include <cstring>

using namespace std;

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define WHITE_COLOR "\033[0m"
#define CYAN_COLOR "\033[36m"

// can edit these struct's values later
struct Song
{
    string title;
    string artist;
    string genre;
    Song *next;
    Song *prev;
};

struct Playlist
{
    string name;
    Song *songHead;
    Playlist *next;
    Playlist *prev;
};
// Display function prototypes
void DisplayWelcomeBanner();
void DisplayOptionsMenu();
void DisplayEnterChoicePrompt(int startRange, int endRange);
void DisplayLoading();
void DisplayProgramQuitBanner();
void DisplayInvalidChoiceMessage();
void DisplayOptionBoxAddPlaylist();
void DisplayOptionBoxAddSongPlaylist();

void MenuAddSong(Playlist *playlist);
void MenuAddPlaylist(Playlist *&head);

int GetValidChoice(int minRange, int maxRange);
void HandleMenuChoice(int choice, Playlist *&playlists);
void HandleAddPlaylistFlow(Playlist *&playlists);
void HandleAddSongFlow(Playlist *playlist);

void DisplayAllPlaylist(Playlist *head);
void HandleAfterDisplayPlaylist(Playlist *head);
void DisplaySongs(Playlist *playlist);

// New helper functions for cleaner code
void DisplayPlaylistMenu();
void DisplayPlaylistSelectionMenu();
void DisplaySongMenu();
void DisplayEmptyPlaylistMenu();
void HandlePlaylistSelection(Playlist *head);
void HandleSongDisplay(Playlist *playlist);
void DisplaySongsForward(Playlist *playlist);
void DisplaySongsBackward(Playlist *playlist);
void DisplayFirstSong(Playlist *playlist);
void DisplayLastSong(Playlist *playlist);

// core function prototypes
void AddPlaylist(Playlist *&headOfPlaylists, string newPlaylistName);
void AddSongToPlaylist(Playlist *playlist, string title, string artist, string genre);

main()
{
    Playlist *playlists = NULL;
    bool shouldQuitProgram = false;

    DisplayWelcomeBanner();
    sleep(2);
    system("cls");
    DisplayLoading();

    while (!shouldQuitProgram)
    {
        DisplayOptionsMenu();
        int choice = GetValidChoice(0, 5);
        
        if (choice == 5)
        {
            shouldQuitProgram = true;
            DisplayLoading();
            DisplayProgramQuitBanner();
        }
        else
        {
            HandleMenuChoice(choice, playlists);
        }
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

void DisplayOptionBoxAddPlaylist()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                Press 1 add song to this playlist                  ||" << endl;
    cout << "||                Press 2 add another playlist                       ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}

void DisplayOptionBoxAddSongPlaylist()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to add another song to this playlist       ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}

void AddPlaylist(Playlist *&headOfPlaylists, string newPlaylistName)
{
    Playlist *newPlaylistNode = new (Playlist);
    newPlaylistNode->name = newPlaylistName;
    newPlaylistNode->songHead = NULL;
    newPlaylistNode->next = NULL;
    newPlaylistNode->prev = NULL;

    if (!headOfPlaylists)
    {
        headOfPlaylists = newPlaylistNode;
        return;
    }

    Playlist *currentNode = headOfPlaylists;
    Playlist *previousNode = NULL;

    while (currentNode && currentNode->name < newPlaylistName)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // Insert at front (head of playlists)
    if (!previousNode)
    {
        newPlaylistNode->next = headOfPlaylists;
        headOfPlaylists->prev = newPlaylistNode;
        headOfPlaylists = newPlaylistNode;
    }
    else
    {
        // Insert in middle or end
        newPlaylistNode->next = currentNode;
        newPlaylistNode->prev = previousNode;
        previousNode->next = newPlaylistNode;
        if (currentNode){
            currentNode->prev = newPlaylistNode;
        }
    }
}

void AddSongToPlaylist(Playlist *playlist, string title, string artist, string genre)
{
    if (!playlist)
        return;

    Song *newSong = new Song;
    newSong->title = title;
    newSong->artist = artist;
    newSong->genre = genre;
    newSong->next = nullptr;
    newSong->prev = nullptr;

    if (!playlist->songHead)
    {
        playlist->songHead = newSong;
        return;
    }

    Song *current = playlist->songHead;
    Song *prev = nullptr;

    // Find correct position in sorted order
    while (current && current->title < title)
    {
        prev = current;
        current = current->next;
    }

    if (!prev)
    {
        // Insert at head
        newSong->next = playlist->songHead;
        playlist->songHead->prev = newSong;
        playlist->songHead = newSong;
    }
    else
    {
        // Insert in middle or end
        newSong->next = current;
        newSong->prev = prev;
        prev->next = newSong;
        if (current)
            current->prev = newSong;
    }
}

void MenuAddPlaylist(Playlist *&head)
{
    string name;

    cout << "========== ADD NEW PLAYLIST ==========" << endl
         << endl;

    cin.ignore(); 
    do
    {
        cout << "Enter playlist name: ";
        getline(cin, name);
        if (name.empty())
        {
            DisplayInvalidChoiceMessage();
        }
    } while (name.empty());

    AddPlaylist(head, name);

    cout << endl
         << GREEN_COLOR << "Playlist \"" << name << "\" added successfully!" << WHITE_COLOR << endl;
}

void MenuAddSong(Playlist *playlist)
{
    if (!playlist)
    {
        cout << RED_COLOR << "No playlist available. Please create a playlist first!" << WHITE_COLOR << endl;
        return;
    }

    string title, artist, genre;

    cout << "========== ADD SONG TO PLAYLIST ==========" << endl
         << endl;
    
    cout << CYAN_COLOR << "CURRENT PLAYLIST: " << playlist->name  << WHITE_COLOR << endl;
    cout << endl;

    cin.ignore(); 
    do
    {
        cout << "Enter song title: ";
        getline(cin, title);
        if (title.empty())
        {
            DisplayInvalidChoiceMessage();
        }
    } while (title.empty());

    do
    {
        cout << "Enter artist name: ";
        getline(cin, artist);
        if (artist.empty())
        {
            DisplayInvalidChoiceMessage();
        }
    } while (artist.empty());

    do
    {
        cout << "Enter genre: ";
        getline(cin, genre);
        if (genre.empty())
        {
            DisplayInvalidChoiceMessage();
        }
    } while (genre.empty());

    AddSongToPlaylist(playlist, title, artist, genre);

    cout << endl
         << GREEN_COLOR << "Song \"" << title << "\" added to playlist \"" << playlist->name << "\" successfully!" << WHITE_COLOR << endl;
}

int GetValidChoice(int minRange, int maxRange)
{
    int choice;
    do
    {
        DisplayEnterChoicePrompt(minRange, maxRange);
        cin >> choice;
        
        if (choice < minRange || choice > maxRange)
        {
            DisplayInvalidChoiceMessage();
        }
    } while (choice < minRange || choice > maxRange);
    
    return choice;
}

void HandleMenuChoice(int choice, Playlist *&playlists)
{
    switch (choice)
    {
        case 0:
            system("cls");
            DisplayLoading();
            DisplayAllPlaylist(playlists);
            HandleAfterDisplayPlaylist(playlists);
            break;
        case 1:
            HandleAddPlaylistFlow(playlists);
            break;
        case 2:
            cout << "Go to playlist functionality not yet implemented." << endl;
            break;
        case 3:
            cout << "Duplicate playlist functionality not yet implemented." << endl;
            break;
        case 4:
            cout << "Delete playlist functionality not yet implemented." << endl;
            break;
    }
}

void HandleAddPlaylistFlow(Playlist *&playlists)
{
    system("cls");
    DisplayLoading();
    MenuAddPlaylist(playlists);
    DisplayOptionBoxAddPlaylist();

    int subChoice = GetValidChoice(0, 2);
    if (subChoice == 0)
    {
        system("cls");
        DisplayLoading();
    }
    else if (subChoice == 1)
    {
        // Find the newly created playlist (last one added)
        Playlist *newPlaylist = playlists;
        while (newPlaylist && newPlaylist->next)
        {
            newPlaylist = newPlaylist->next;
        }
        
        if (newPlaylist)
        {
            HandleAddSongFlow(newPlaylist);
        }
    }
    else if (subChoice == 2)
    {
        // Add another playlist
        HandleAddPlaylistFlow(playlists);
    }
}

void HandleAddSongFlow(Playlist *playlist)
{
    bool continueAdding = true;
    
    while (continueAdding)
    {
        system("cls");
        DisplayLoading();
        MenuAddSong(playlist);
        DisplayOptionBoxAddSongPlaylist();
        
        int choice = GetValidChoice(0, 1);
        if (choice == 0)
        {
            continueAdding = false;
            system("cls");
            DisplayLoading();
        }
        // If choice == 1, continue the loop to add another song
    }
}

void DisplayAllPlaylist(Playlist *head)
{
    cout << endl;
    cout << "========================= AVAILABLE PLAYLIST ==========================" << endl;
    
    if (!head)
    {
        cout << endl << endl;
        cout << RED_COLOR << "No playlist available." << WHITE_COLOR << endl;
        cout << endl << endl;
        cout << "=======================================================================" << endl;
        return;
    }
    
    int index = 1;
    Playlist *current = head;
    
    while (current)
    {
        cout << index << ". " << current->name << endl;
        current = current->next;
        index++;
    }
    
    cout << "=======================================================================" << endl;
}

void HandleAfterDisplayPlaylist(Playlist *head)
{
    if(!head)
    {
        cout << "Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        system("cls");
        DisplayLoading();
        return;
    }
    
    cout << endl;
    cout << endl;
    DisplayPlaylistMenu();
    
    int choice = GetValidChoice(0, 1);
    if (choice == 0)
    {
        system("cls");
        DisplayLoading();
        return;
    }
    
    if(choice == 1)
    {
        system("cls");
        DisplayLoading();
        HandlePlaylistSelection(head);
    }
}	

void DisplayPlaylistMenu()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to display songs in playlist               ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}

void DisplaySongMenu()
{
    cout << endl;
    cout << "======================================================================" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "||  [1] Display songs (forward order)                               ||" << endl;
    cout << "||  [2] Display songs (backward order)                              ||" << endl;
    cout << "||  [3] Show first song only                                        ||" << endl;
    cout << "||  [4] Show last song only                                         ||" << endl;
    cout << "||  [0] Return to previous menu                                     ||" << endl;
    cout << "||                                                                  ||" << endl;
    cout << "======================================================================" << endl;
}

void DisplayEmptyPlaylistMenu()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to add song to this playlist               ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}

void HandlePlaylistSelection(Playlist *head)
{
    Playlist *current = head;
    int index = 1;
    int playlistCount = 0;
    
    cout << "Playlist Options:" << endl;
    while(current)
    {
        cout << index << ". " << current->name << endl;
        current = current->next;
        index++;
        playlistCount++;
    }
    
    int selectedNum;
    do
    {
        cout << endl << "Enter playlist number: ";
        cin >> selectedNum;
        
        if(selectedNum < 1 || selectedNum > playlistCount)
        {
            cout << RED_COLOR << "Invalid number. Please try again." << WHITE_COLOR << endl;
        }
    } while(selectedNum < 1 || selectedNum > playlistCount);
    
    current = head;
    for(int i = 1; i < selectedNum; i++)
        current = current->next;
        
    system("cls");
    DisplayLoading();
    HandleSongDisplay(current);
}

void HandleSongDisplay(Playlist *playlist)
{
    if(!playlist || !playlist->songHead)
    {
        cout << endl;
        cout << "======================================================================" << endl;
        cout << "       Now viewing playlist: " << playlist->name << endl;
        cout << "======================================================================" << endl;
        cout << RED_COLOR << "This playlist has no songs yet." << WHITE_COLOR << endl;
        DisplayEmptyPlaylistMenu();
        
        int choice = GetValidChoice(0, 1);
        if (choice == 0)
        {
            system("cls");
            DisplayLoading();
            return;
        }
        else if (choice == 1)
        {
            system("cls");
            // DisplayLoading();
            HandleAddSongFlow(playlist);
        }
        return;
    }
    
    int choice;
    do
    {
        cout << endl;
        cout << "======================================================================" << endl;
        cout << "       Now viewing playlist: " << playlist->name << endl;
        cout << "======================================================================" << endl;
        DisplaySongMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        system("cls");
        DisplayLoading();
        
        switch (choice)
        {
            case 1:
                DisplaySongsForward(playlist);
                break;
            case 2:
                DisplaySongsBackward(playlist);
                break;
            case 3:
                DisplayFirstSong(playlist);
                break;
            case 4:
                DisplayLastSong(playlist);
                break;
            case 0:
                cout << "Returning..." << endl;
                system("cls");
                DisplayLoading();
                break;
            default:
                cout << RED_COLOR << "Invalid choice. Try again." << WHITE_COLOR << endl;
        }
        
        if (choice != 0)
        {
            cout << endl << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
        }
        
    } while (choice != 0);
}

void DisplaySongsForward(Playlist *playlist)
{
    cout << endl << "Songs in forward order:" << endl;
    Song *song = playlist->songHead;
    while(song)
    {
        cout << "- " << song->title << " by " << song->artist << endl;
        song = song->next;
    }
}

void DisplaySongsBackward(Playlist *playlist)
{
    cout << endl << "Songs in backward order:" << endl;
    Song *song = playlist->songHead;
    while(song && song->next)
        song = song->next;
         
    while(song)
    {
        cout << "- " << song->title << " by " << song->artist << endl;
        song = song->prev;
    }
}

void DisplayFirstSong(Playlist *playlist)
{
    cout << endl << "First song in the playlist:" << endl;
    cout << "- " << playlist->songHead->title << " by " << playlist->songHead->artist << endl;
}

void DisplayLastSong(Playlist *playlist)
{
    cout << endl << "Last song in the playlist:" << endl;
    Song *song = playlist->songHead;
    while(song && song->next)
        song = song->next;
    cout << "- " << song->title << " by " << song->artist << endl;
}