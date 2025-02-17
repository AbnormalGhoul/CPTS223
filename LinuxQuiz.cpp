// LinuxQuiz.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
#include "Data.cpp"

class PlayerProfile {
public:
    std::string name;
    int score;
    PlayerProfile(std::string n, int s) : name(n), score(s) {}
};

void displayMenu() {
    std::cout << "1. Game Rules\n";
    std::cout << "2. Play New Game\n";
    std::cout << "3. Load Previous Game\n";
    std::cout << "4. Add Command\n";
    std::cout << "5. Remove Command\n";
    std::cout << "6. Display All Commands\n";
    std::cout << "7. Save and Exit\n";
}

void gameRules() {
    std::cout << "Game Rules:\n";
    std::cout << "Match Linux commands with their descriptions.\n";
    std::cout << "You will be awarded points for correct matches and deducted points for incorrect ones.\n";
}

void playGame(LinkedList<Data>& commandList, PlayerProfile& player) {
    int numQuestions;
    std::cout << "Enter the number of questions: ";
    std::cin >> numQuestions;

    Node<Data>* current = commandList.getHead();
    for (int i = 0; i < numQuestions; ++i) {
        if (current == nullptr) {
            current = commandList.getHead();
        }

        std::string command = current->data.command;
        std::string correctAnswer = current->data.description;

        std::cout << "What does the command " << command << " do?\n";
        // Display options and handle user input
        // Update player score based on correctness
        current = current->next;
    }
}

int main() {
    LinkedList<Data> commandList;
    std::vector<PlayerProfile> profiles;

    // Load commands from CSV
    // Load profiles from CSV

    while (true) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                gameRules();
                break;
            case 2:
                // Play New Game
                break;
            case 3:
                // Load Previous Game
                break;
            case 4:
                // Add Command
                break;
            case 5:
                // Remove Command
                break;
            case 6:
                // Display All Commands
                break;
            case 7:
                // Save and Exit
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}