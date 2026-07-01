#include "splashkit.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// Structs
struct song_data
{
    string name;
    string id; // Unique identifier: e.g. "song-0"
    string path;
    bool loved;
    int times_played;
};

struct music_player_data
{
    vector<song_data> songs;
    int next_id;
};

// Input Helpers
string read_string(string prompt)
{
    while (true)
    {
        write(prompt);
        string input = read_line();
        if (!input.empty())
        {
            return input;
        }
        write_line("Input cannot be empty. Please try again.");
    }
}

bool read_boolean(string prompt)
{
    while (true)
    {
        write(prompt);
        string input = read_line();
        if (input == "y" || input == "Y" || input == "yes" || input == "Yes" || input == "YES")
        {
            return true;
        }
        else if (input == "n" || input == "N" || input == "no" || input == "No" || input == "NO")
        {
            return false;
        }
        write_line("Invalid input. Please enter y or n.");
    }
}

int read_integer(string prompt, int min, int max)
{
    while (true)
    {
        write(prompt);
        string input = read_line();
        if (is_integer(input))
        {
            int val = convert_to_integer(input);
            if (val >= min && val <= max)
            {
                return val;
            }
        }
        write_line("Please enter an integer between " + to_string(min) + " and " + to_string(max) + ".");
    }
}

// Function Declarations/Definitions
void add_song(music_player_data &player)
{
    write_line("\n--- Add a New Song ---");
    string name = read_string("Enter song name: ");
    string path = read_string("Enter path to file: ");
    bool loved = read_boolean("Is the song loved? (y/n): ");

    song_data new_song;
    new_song.name = name;
    new_song.id = "song-" + std::to_string(player.next_id);
    new_song.path = path;
    new_song.loved = loved;
    new_song.times_played = 0;

    // Increment next unique ID
    player.next_id++;

    // Load music using SplashKit
    write_line("Loading song into SplashKit as " + new_song.id + " from: " + path);
    load_music(new_song.id, new_song.path);

    // Add to player's songs list
    player.songs.push_back(new_song);
    write_line("Song added successfully with ID: " + new_song.id);
}

// Search and select function
// Returns the index of the selected song in player.songs, or -1 if none/canceled
int search_and_select_song(const music_player_data &player)
{
    if (player.songs.empty())
    {
        write_line("No songs in the library. Please add a song first.");
        return -1;
    }

    string search_term = read_string("Enter search term (name to search for): ");
    
    vector<int> matches;
    for (int i = 0; i < player.songs.size(); i++)
    {
        // Use SplashKit contains function to match name
        if (contains(player.songs[i].name, search_term))
        {
            matches.push_back(i);
        }
    }

    if (matches.empty())
    {
        write_line("No matching songs found for '" + search_term + "'.");
        return -1;
    }

    write_line("\nMatching songs:");
    for (int i = 0; i < matches.size(); i++)
    {
        int original_idx = matches[i];
        const song_data &s = player.songs[original_idx];
        string loved_str = s.loved ? "[Loved]" : "";
        write_line(std::to_string(i + 1) + ": " + s.name + " (" + s.id + ") - Played: " + std::to_string(s.times_played) + " times " + loved_str);
    }

    int selection = read_integer("Enter the number of the song you want: ", 1, (int)matches.size());
    return matches[selection - 1];
}

void update_song(music_player_data &player)
{
    write_line("\n--- Update a Song ---");
    int song_idx = search_and_select_song(player);
    if (song_idx == -1)
    {
        return;
    }

    bool in_update_menu = true;
    while (in_update_menu)
    {
        // Get reference to the selected song
        song_data &song = player.songs[song_idx];

        write_line("\nSong Details:");
        write_line("Name:         " + song.name);
        write_line("ID:           " + song.id);
        write_line("Path:         " + song.path);
        write_line("Loved:        " + string(song.loved ? "Yes" : "No"));
        write_line("Times Played: " + to_string(song.times_played));
        
        write_line("\nUpdate Options:");
        write_line("1. Update name");
        write_line("2. Toggle loved status");
        write_line("3. Reset times played");
        write_line("4. Delete");
        write_line("5. Quit update");

        int choice = read_integer("Select an option (1-5): ", 1, 5);
        if (choice == 1)
        {
            string new_name = read_string("Enter new name: ");
            song.name = new_name;
            write_line("Name updated successfully!");
        }
        else if (choice == 2)
        {
            song.loved = !song.loved;
            write_line("Loved status toggled to: " + string(song.loved ? "Yes" : "No"));
        }
        else if (choice == 3)
        {
            song.times_played = 0;
            write_line("Times played has been reset to 0.");
        }
        else if (choice == 4)
        {
            // Free the SplashKit music resource
            music m = music_named(song.id);
            if (music_valid(m))
            {
                free_music(m);
            }
            
            // Delete song from vector
            player.songs.erase(player.songs.begin() + song_idx);
            write_line("Song deleted successfully.");
            in_update_menu = false; // Break update menu loop
        }
        else if (choice == 5)
        {
            in_update_menu = false;
        }
    }
}

void play_selected_song(music_player_data &player)
{
    write_line("\n--- Play a Song ---");
    int song_idx = search_and_select_song(player);
    if (song_idx == -1)
    {
        return;
    }

    song_data &song = player.songs[song_idx];

    // Increment times played
    song.times_played++;

    write_line("Playing song: " + song.name + " (" + song.id + ")...");
    
    // Play using SplashKit
    play_music(song.id);
}

void pause_resume_song()
{
    write_line("\n--- Pause / Resume Song ---");
    if (music_playing())
    {
        pause_music();
        write_line("Music has been paused.");
    }
    else if (music_paused())
    {
        resume_music();
        write_line("Music has been resumed.");
    }
    else
    {
        write_line("No music is currently playing or paused.");
    }
}

void print_status(const music_player_data &player)
{
    write_line("\n=== Music Player Status ===");
    write_line("Number of songs: " + std::to_string(player.songs.size()));
    
    int total_played = 0;
    int total_loved = 0;
    for (const auto &song : player.songs)
    {
        total_played += song.times_played;
        if (song.loved)
        {
            total_loved++;
        }
    }
    
    write_line("Total number of songs played: " + std::to_string(total_played));
    write_line("Total number of loved songs:  " + std::to_string(total_loved));
}

int main()
{
    music_player_data player;
    player.next_id = 0;

    bool quit = false;
    while (!quit)
    {
        write_line("\n=============================");
        write_line("===   MUSIC PLAYER MENU   ===");
        write_line("=============================");
        write_line("1. Add a new song");
        write_line("2. Update a song");
        write_line("3. Play a song");
        write_line("4. Pause / Resume song");
        write_line("5. Print status");
        write_line("6. Quit");
        write_line("=============================");
        
        int choice = read_integer("Select an option (1-6): ", 1, 6);
        switch (choice)
        {
            case 1:
                add_song(player);
                break;
            case 2:
                update_song(player);
                break;
            case 3:
                play_selected_song(player);
                break;
            case 4:
                pause_resume_song();
                break;
            case 5:
                print_status(player);
                break;
            case 6:
                write_line("Quitting music player. Goodbye!");
                quit = true;
                break;
        }
    }

    // Clean up all loaded music resources
    free_all_music();
    
    return 0;
}