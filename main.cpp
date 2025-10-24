#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define WHITE_COLOR "\033[0m"
#define CYAN_COLOR "\033[36m"

// Data Structures
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

// Function Prototypes
void DisplayWelcomeBanner();
void DisplayMainMenu();
void DisplayLoading();
void DisplayQuitBanner();
void DisplayInvalidChoice();
void DisplayEnterChoice(int min, int max);

// Core Functions
void AddPlaylist(Playlist *&head, string name);
void AddSongToPlaylist(Playlist *playlist, string title, string artist, string genre);
int GetValidChoice(int min, int max);

// Menu Handlers
void HandleMainMenu(Playlist *&playlists, int choice);
void HandleDisplayPlaylists(Playlist *playlists);
void HandleCreatePlaylist(Playlist *&playlists);
void HandleViewPlaylist(Playlist *playlists);
void HandlePlaylistMenu(Playlist *playlist);

// Display Functions
void ShowAllPlaylists(Playlist *head);
void ShowPlaylistSelection(Playlist *head);
void ShowPlaylistSongs(Playlist *playlist);
void ShowSongsForward(Playlist *playlist);
void ShowSongsBackward(Playlist *playlist);
void ShowFirstSong(Playlist *playlist);
void ShowLastSong(Playlist *playlist);

// Input Functions
void GetPlaylistName(Playlist *&head);
void GetSongDetails(Playlist *playlist);
Playlist* SelectPlaylist(Playlist *head);

// Menu Display Functions
void ShowMainMenu();
void ShowPlaylistOptions();
void ShowSongOptions();
void ShowEmptyPlaylistOptions();

int main()
{
    Playlist *playlists = NULL;
    
    DisplayWelcomeBanner();
    sleep(2);
    system("cls");
    DisplayLoading();
    
    while (true)
    {
        DisplayMainMenu();
        int choice = GetValidChoice(0, 5);
        
        if (choice == 5)
        {
            DisplayLoading();
            DisplayQuitBanner();
            break;
        }
        
        HandleMainMenu(playlists, choice);
    }
    
    return 0;
}

// ==================== DISPLAY FUNCTIONS ====================

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

void DisplayMainMenu()
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

void DisplayLoading()
{
    cout << endl << endl;
    cout << "==============================" << endl;
    cout << "||      L O A D I N G       ||" << endl;
    cout << "==============================" << endl;
    sleep(1);
    system("cls");
}

void DisplayQuitBanner()
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

void DisplayInvalidChoice()
{
    cout << RED_COLOR << "Invalid choice. Please try again." << WHITE_COLOR << endl;
}

void DisplayEnterChoice(int min, int max)
{
    cout << "Enter your choice (" << min << "-" << max << "): ";
}

// ==================== CORE FUNCTIONS ====================

void AddPlaylist(Playlist *&head, string name)
{
    Playlist *newPlaylist = new Playlist;
    newPlaylist->name = name;
    newPlaylist->songHead = NULL;
    newPlaylist->next = NULL;
    newPlaylist->prev = NULL;

    if (!head)
    {
        head = newPlaylist;
        return;
    }

    Playlist *current = head;
    Playlist *prev = NULL;

    while (current && current->name < name)
    {
        prev = current;
        current = current->next;
    }

    if (!prev)
    {
        newPlaylist->next = head;
        head->prev = newPlaylist;
        head = newPlaylist;
    }
    else
    {
        newPlaylist->next = current;
        newPlaylist->prev = prev;
        prev->next = newPlaylist;
        if (current)
            current->prev = newPlaylist;
    }
}

void AddSongToPlaylist(Playlist *playlist, string title, string artist, string genre)
{
    if (!playlist) return;

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

    while (current && current->title < title)
    {
        prev = current;
        current = current->next;
    }

    if (!prev)
    {
        newSong->next = playlist->songHead;
        playlist->songHead->prev = newSong;
        playlist->songHead = newSong;
    }
    else
    {
        newSong->next = current;
        newSong->prev = prev;
        prev->next = newSong;
        if (current)
            current->prev = newSong;
    }
}

int GetValidChoice(int min, int max)
{
    int choice;
    do
    {
        DisplayEnterChoice(min, max);
        cin >> choice;
        
        if (choice < min || choice > max)
            DisplayInvalidChoice();
    } while (choice < min || choice > max);
    
    return choice;
}

// ==================== MENU HANDLERS ====================

void HandleMainMenu(Playlist *&playlists, int choice)
{
    switch (choice)
    {
        case 0:
            system("cls");
            DisplayLoading();
            HandleDisplayPlaylists(playlists);
            break;
        case 1:
            HandleCreatePlaylist(playlists);
            break;
        case 2:
            HandleViewPlaylist(playlists);
            break;
        case 3:
            cout << "Duplicate playlist functionality not yet implemented." << endl;
            break;
        case 4:
            cout << "Delete playlist functionality not yet implemented." << endl;
            break;
    }
}

void HandleDisplayPlaylists(Playlist *playlists)
{
    ShowAllPlaylists(playlists);
    
    if (!playlists)
    {
        cout << "Press Enter to return to the main menu...";
        cin.ignore();
        cin.get();
        system("cls");
        DisplayLoading();
        return;
    }
    
    cout << endl << endl;
    ShowPlaylistOptions();
    
    int choice = GetValidChoice(0, 1);
    if (choice == 0)
    {
        system("cls");
        DisplayLoading();
        return;
    }
    
    if (choice == 1)
    {
        system("cls");
        DisplayLoading();
        ShowPlaylistSelection(playlists);
    }
}

void HandleCreatePlaylist(Playlist *&playlists)
{
    system("cls");
    DisplayLoading();
    GetPlaylistName(playlists);
    
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the menu                     ||" << endl;
    cout << "||                Press 1 add song to this playlist                  ||" << endl;
    cout << "||                Press 2 add another playlist                       ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
    
    int choice = GetValidChoice(0, 2);
    if (choice == 0)
    {
        system("cls");
        DisplayLoading();
    }
    else if (choice == 1)
    {
        Playlist *newPlaylist = playlists;
        while (newPlaylist && newPlaylist->next)
            newPlaylist = newPlaylist->next;
        
        if (newPlaylist)
        {
            system("cls");
            DisplayLoading();
            GetSongDetails(newPlaylist);
        }
    }
    else if (choice == 2)
    {
        HandleCreatePlaylist(playlists);
    }
}

void HandleViewPlaylist(Playlist *playlists)
{
    if (!playlists)
    {
        cout << "No playlists available. Please create a playlist first!" << endl;
        return;
    }
    
    system("cls");
    DisplayLoading();
    ShowPlaylistSelection(playlists);
}

void HandlePlaylistMenu(Playlist *playlist)
{
    if (!playlist || !playlist->songHead)
    {
        cout << endl;
        cout << "======================================================================" << endl;
        cout << "       Now viewing playlist: " << playlist->name << endl;
        cout << "======================================================================" << endl;
        cout << RED_COLOR << "This playlist has no songs yet." << WHITE_COLOR << endl;
        ShowEmptyPlaylistOptions();
        
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
            DisplayLoading();
            GetSongDetails(playlist);
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
        ShowSongOptions();
        cout << "Enter your choice: ";
        cin >> choice;
        
        system("cls");
        DisplayLoading();
        
        switch (choice)
        {
            case 1:
                ShowSongsForward(playlist);
                break;
            case 2:
                ShowSongsBackward(playlist);
                break;
            case 3:
                ShowFirstSong(playlist);
                break;
            case 4:
                ShowLastSong(playlist);
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

// ==================== DISPLAY FUNCTIONS ====================

void ShowAllPlaylists(Playlist *head)
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

void ShowPlaylistSelection(Playlist *head)
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
    HandlePlaylistMenu(current);
}

void ShowPlaylistSongs(Playlist *playlist)
{
    HandlePlaylistMenu(playlist);
}

void ShowSongsForward(Playlist *playlist)
{
    cout << endl << "Songs in forward order:" << endl;
    Song *song = playlist->songHead;
    while(song)
    {
        cout << "- " << song->title << " by " << song->artist << endl;
        song = song->next;
    }
}

void ShowSongsBackward(Playlist *playlist)
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

void ShowFirstSong(Playlist *playlist)
{
    cout << endl << "First song in the playlist:" << endl;
    cout << "- " << playlist->songHead->title << " by " << playlist->songHead->artist << endl;
}

void ShowLastSong(Playlist *playlist)
{
    cout << endl << "Last song in the playlist:" << endl;
    Song *song = playlist->songHead;
    while(song && song->next)
        song = song->next;
    cout << "- " << song->title << " by " << song->artist << endl;
}

// ==================== INPUT FUNCTIONS ====================

void GetPlaylistName(Playlist *&head)
{
    string name;
    cout << "========== ADD NEW PLAYLIST ==========" << endl << endl;
    
    cin.ignore(); 
    do
    {
        cout << "Enter playlist name: ";
        getline(cin, name);
        if (name.empty())
        {
            DisplayInvalidChoice();
        }
    } while (name.empty());
    
    AddPlaylist(head, name);
    cout << endl << GREEN_COLOR << "Playlist \"" << name << "\" added successfully!" << WHITE_COLOR << endl;
}

void GetSongDetails(Playlist *playlist)
{
    if (!playlist)
    {
        cout << RED_COLOR << "No playlist available. Please create a playlist first!" << WHITE_COLOR << endl;
        return;
    }
    
    string title, artist, genre;
    cout << "========== ADD SONG TO PLAYLIST ==========" << endl << endl;
    cout << CYAN_COLOR << "CURRENT PLAYLIST: " << playlist->name << WHITE_COLOR << endl << endl;
    
    cin.ignore(); 
    do
    {
        cout << "Enter song title: ";
        getline(cin, title);
        if (title.empty())
        {
            DisplayInvalidChoice();
        }
    } while (title.empty());
    
    do
    {
        cout << "Enter artist name: ";
        getline(cin, artist);
        if (artist.empty())
        {
            DisplayInvalidChoice();
        }
    } while (artist.empty());
    
    do
    {
        cout << "Enter genre: ";
        getline(cin, genre);
        if (genre.empty())
        {
            DisplayInvalidChoice();
        }
    } while (genre.empty());
    
    AddSongToPlaylist(playlist, title, artist, genre);
    cout << endl << GREEN_COLOR << "Song \"" << title << "\" added to playlist \"" << playlist->name << "\" successfully!" << WHITE_COLOR << endl;
    
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to add another song to this playlist       ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
    
    int choice = GetValidChoice(0, 1);
    if (choice == 0)
    {
        system("cls");
        DisplayLoading();
    }
    else if (choice == 1)
    {
        system("cls");
        DisplayLoading();
        GetSongDetails(playlist);
    }
}

// ==================== MENU DISPLAY FUNCTIONS ====================

void ShowMainMenu()
{
    DisplayMainMenu();
}

void ShowPlaylistOptions()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to display songs in playlist               ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}

void ShowSongOptions()
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

void ShowEmptyPlaylistOptions()
{
    cout << endl;
    cout << "=======================================================================" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "||                Press 0 to go back to the main menu                ||" << endl;
    cout << "||                Press 1 to add song to this playlist               ||" << endl;
    cout << "||                                                                   ||" << endl;
    cout << "=======================================================================" << endl;
}