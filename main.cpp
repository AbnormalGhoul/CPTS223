// Itay Shemesh, CPTS 223, Professor Kandaswamy
// PA1, Linux Game

#include "LinkedList.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef pair<string, string> CommandData;

// Displays the main menu options
void displayMenu() {
    cout << "\nMain Menu:\n";
    cout << "1. Game Rules\n";
    cout << "2. Play New Game\n";
    cout << "3. Load Previous Game\n";
    cout << "4. Add Command\n";
    cout << "5. Remove Command\n";
    cout << "6. Display All Commands\n";
    cout << "7. Save and Exit\n";
    cout << "Enter your choice: ";
}

// Displays the rules of the game
void displayRules() {
    cout << "\nGame Rules:\n";
    cout << "1. You will be asked to match Linux commands with their descriptions\n";
    cout << "2. Each correct answer awards you a point\n";
    cout << "3. Questions will not repeat in a single game session\n";
    cout << "4. If you wish to save your progress, use the Save and Exit option\n";
    cout << "5. You can load a saved game to continue your progress\n";
}

// Function to start a new game
void playGame(LinkedList<CommandData>& commands, int& playerScore) {
    int totalCommands = commands.getSize();
    
    // Checks for if there are enough options to play the game, at least once
    if (totalCommands < 3) {
        cout << "Not enough commands to play the game. Add more commands.\n";
        return;
    }

    vector<CommandData> commandList;
    Node<CommandData>* current = commands.getHead();
    while (current) {
        commandList.push_back(current->data);
        current = current->next;
    }

    srand(static_cast<unsigned>(time(0)));
    random_shuffle(commandList.begin(), commandList.end());
    int score = 0, questionCount = 0;

    // Asks for # of questions, and then checks for if that number is possible
    cout << "How many questions would you like to answer? ";
    cin >> questionCount;
    if (questionCount > totalCommands) {
        cout << "Not enough unique questions available. The maximum is " << totalCommands << ".\n";
        return;
    }

    // Repeats for the total amount of questions wanted
    for (int i = 0; i < questionCount; ++i) {
        CommandData question = commandList[i];
        vector<string> options = {question.second};
        // While there are less than 3 commands in the prompt, it will add them randomly
        while (options.size() < 3) {
            int randomIndex = rand() % totalCommands;
            if (find(options.begin(), options.end(), commandList[randomIndex].second) == options.end()) {
                options.push_back(commandList[randomIndex].second);
            }
        }

        // Randomly Shuffels the options
        random_shuffle(options.begin(), options.end());

        // Display's the options 
        cout << "\nWhat does the command '" << question.first << "' do?\n";
        for (size_t j = 0; j < options.size(); ++j) {
            cout << j + 1 << ". " << options[j] << "\n";
        }

        // User prompt
        int answer;
        cout << "Your choice: ";
        cin >> answer;

        // Correct/Inncorrect choice
        if (options[answer - 1] == question.second) {
            cout << "Correct!\n";
            ++score;
        } else {
            cout << "Incorrect.\n";
        }
    }

    playerScore += score;
    cout << "\nGame over! Your score: " << score << " (Total: " << playerScore << ")\n";
}

// Function to add a command to the commands.csv
void addCommand(LinkedList<CommandData>& commands) {
    string command, description;

    // Ask's for a command
    cout << "Enter command: ";
    cin.ignore();
    getline(cin, command);

    // Ask's for a description
    cout << "Enter description: ";
    getline(cin, description);

    // Add's the command to the linked list, so that when it saves it is also put into the .csv
    commands.insertAtFront(make_pair(command, description));
    cout << "Command added successfully.\n";
}

// Removes a command from commands.csv
void removeCommand(LinkedList<CommandData>& commands) {
    string command;
    
    // Ask's for command name
    cout << "Enter command to remove: ";
    cin.ignore();
    getline(cin, command);

    Node<CommandData>* current = commands.getHead();
    Node<CommandData>* prev = nullptr;

    // Will search commands.csv until it finds the wanted command name, and then delete it
    while (current) {
        if (current->data.first == command) {
            if (prev) {
                prev->next = current->next;
            } else {
                commands.setHead(current->next);
            }
            delete current;
            cout << "Command removed successfully.\n";
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // Otherwise command hasn't been found/exsits
    cout << "Command not found.\n";
}

// Loads previously played game, by player name
// It does have an issue when you save with the same name as another player
// I could make it either say that the name is alr taken or overwrite the previous name
// But it didn't say so in the instructions so...
void loadPreviousGame(string& playerName, int& playerScore) {

    // Checks for if profiles.csv is open
    ifstream file("profiles.csv");
    if (!file.is_open()) {
        cerr << "Error opening profiles file.\n";
        return;
    }

    string line, name;
    int score;

    // Ask's user for name
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, playerName);


    // Goes through the profiles.csv file until there are no more players left
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> score;

        // Welcome's back players if they have already played the game before
        if (name == playerName) {
            playerScore = score;
            cout << "Welcome back, " << playerName << "! Your score: " << playerScore << "\n";
            file.close();
            return;
        }
    }
    // No profiles of said name were found
    cout << "No previous profile found for " << playerName << ". Starting a new game.\n";
    playerScore = 0;
    file.close();
}

// This function saves and exists
// All the commands that are in the list are saved in commands.csv, including all commands that were added/removed
// Saves new profile name into profiles.csv
void saveAndExit(string playerName, int playerScore, LinkedList<CommandData>& commands) {
    ofstream file("profiles.csv", ios::app);
    // Checks if profiles.csv is open
    if (!file.is_open()) {
        cerr << "Error opening profiles file for writing.\n";
        return;
    }

    // Adds the player name and score to the file
    file << playerName << "," << playerScore << "\n";
    file.close();

    commands.saveToCSV("commands.csv");
    cout << "Progress saved. Goodbye, " << playerName << "!\n";
}

// Main function
int main() {
    LinkedList<CommandData> commands;
    commands.loadFromCSV("commands.csv");

    string playerName;
    int playerScore = 0;
    int choice;

    // Switch case for the options
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayRules();
                break;
            case 2:
                playGame(commands, playerScore);
                break;
            case 3:
                loadPreviousGame(playerName, playerScore);
                break;
            case 4:
                addCommand(commands);
                break;
            case 5:
                removeCommand(commands);
                break;
            case 6:
                cout << "\nCommands:\n";
                commands.display();
                break;
            case 7:
                cout << "Enter your name to save your progress: ";
                cin.ignore();
                getline(cin, playerName);
                saveAndExit(playerName, playerScore, commands);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
