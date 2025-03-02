#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;

// Unicode character for a filled rectangle, representing a Maya bar
const char* MAYAN_BAR = "\u2580\u2580\u2580\u2580\u2580";
const int POWER_LIMIT = 6;
const int BASE = 20;
const int MIN_GUESS_VALUE = 10;
const int SPACING_WIDTH = 4;

// Function to ask the user if they want to play another game
bool askToDoAnother(char choice)
{
    // Read in the user's selection
    cout << "Do you want to play another game? (Y/N) ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

// Function to print the welcome screen
void printWelcomeScreen() {
    cout << "MAYAN NUMBER GAME" << endl;
    cout << "=================" << endl;
    cout << "You'll first enter a number (>= 10) to be the maximum number to guess. You'll then match a decimal number to its Mayan equivalent."
         << endl << endl;
}

// Function to print a specified number of 'o's
void printOnes(int count) {
    string ones = "";
    for (int i = 0; i < count; i++) {
        ones += 'o';
    }
    cout << setw(SPACING_WIDTH + 1) << ones << endl;
}

// Function to print a specified number of MAYAN_BAR
void printFives(int count) {
    for (int i = 0; i < count; i++) {
        cout << setw(SPACING_WIDTH) << MAYAN_BAR << endl;
    }
}

// Function to print the Mayan representation of a decimal number
void printMayanNumber(int decimalNumber) {
    vector<int> digits;
    int quotient = 0;

    // Decompose the decimal number into Mayan digits 
    for (int i = POWER_LIMIT; i >= 0; i--) {
        int value = pow(BASE, i);
        quotient = decimalNumber / value;

        // Include Mayan digits in the vector only if they are non-zero or it's the last digit
        if (quotient != 0 || i == 0) {
            digits.push_back(quotient);
        }

        decimalNumber %= value;
    }

    // Print the Mayan representation
    for (unsigned int x = 0; x < digits.size(); x++) {
        int digit = digits.at(x);

        if (x != 0) {
            cout << "------" << endl;
        }

        if (digit == 0) {
            cout << setw(SPACING_WIDTH + 1) << "00" << endl;
        } else {
            int onesCount = digit % 5;
            int fivesCount = digit / 5;

            if (onesCount) {
                printOnes(onesCount);
            }
            if (fivesCount) {
                printFives(fivesCount);
            }
        }
    }
}

// Function to generate a random incorrect answer within a specified range
int incorrectAnswer(int correctDecimalAnswer) {
    int lowerLimit = correctDecimalAnswer * 0.5;
    int upperLimit = correctDecimalAnswer * 1.5;

    int incorrectAnswer = correctDecimalAnswer % (upperLimit - lowerLimit + 1) + lowerLimit;
    return incorrectAnswer;
}

// Function to generate answer choices for the game
void generateAnswerChoices(int& correctDecimalAnswer, int userNumber, vector<int>& answerChoices) {
    correctDecimalAnswer = rand() % (userNumber - 4 + 1) + 4;

    answerChoices.push_back(correctDecimalAnswer); // Correct answer
    answerChoices.push_back(incorrectAnswer(correctDecimalAnswer)); // Incorrect answer 1
    answerChoices.push_back(incorrectAnswer(correctDecimalAnswer) + rand() % correctDecimalAnswer + 1); // Incorrect answer 2

    // Shuffle the answer choices
    for (int i = 0; i < 3; i++) {
        int randomIndex = rand() % 3;
        swap(answerChoices[i], answerChoices[randomIndex]);
    }
}

// Function to print the question and answer choices
void printQuestionAndChoices(int correctDecimalAnswer, const vector<int>& answerChoices) {
    cout << "Which of these Mayan numbers is equal to " << correctDecimalAnswer << "?" << endl;

    // Print the answer choices
    for (int i = 0; i < 3; i++) {
        char option = 'a' + i;
        cout << option << ". \n";
        printMayanNumber(answerChoices.at(i));
        cout << endl;
    }
}
// Function to get the user's choice
char getUserChoice() {
    char userChoice = ' ';
    cout << "Enter a, b, or c: ";
    cin >> userChoice;
    return userChoice;
}

// Function to find the correct choice based on the answer choices and correct answer
char findCorrectChoice(const vector<int>& answerChoices, int correctAnswer) {
    for (size_t i = 0; i < answerChoices.size(); i++) {
        if (answerChoices.at(i) == correctAnswer) {
            return 'a' + static_cast<char>(i);
        }
    }
    return ' '; 
}

// Function to evaluate the user's choice and provide feedback
void evaluateUserChoice(char userChoice, char correctChoice, int correctDecimalAnswer) {
    if (userChoice == correctChoice) {
        cout << "CORRECT! " << endl;
    } else {
        cout << "INCORRECT! " << endl;
        cout << "The Mayan representation of " << correctDecimalAnswer << " is"
             << endl;
        printMayanNumber(correctDecimalAnswer);
    }
}

// Main function
int main() {
    cout << "Printing out the Maya number for 2,072,025: " << endl;
    printMayanNumber(2072025);

    printWelcomeScreen();

    // Initialize variables
    bool keepReading = 1;
    int userNumber = 0;
    srand(time(nullptr));

    // Get user input for the maximum number to guess
    cout << "Enter maximum to guess from (< 10 exits): ";
    cin >> userNumber;
    int exit = 1;

    while (keepReading) {
        // Check if the entered number is at least 10
        if (userNumber < MIN_GUESS_VALUE) {
            cout << "Please enter a number greater than or equal to 10." << endl;
            break;
        }

        // Variables for the current game
        int correctDecimalValue = 0;
        vector<int> answerChoices;

        // Generate answer choices for the current game
        cout << "Round " << exit << endl;
        generateAnswerChoices(correctDecimalValue, userNumber, answerChoices);
        
        // Print the question and answer choices
        printQuestionAndChoices(correctDecimalValue, answerChoices);

        // Get user choice
        char userChoice = getUserChoice();

        // Find the correct choice
        char correctChoice = findCorrectChoice(answerChoices, correctDecimalValue);

        // Evaluate user choice 
        evaluateUserChoice(userChoice, correctChoice, correctDecimalValue);

        exit++;
        if(exit > 10){
            exit = 1; 
            break;
        }

        // Ask if the user wants to play another game
        char choice = ' ';
        keepReading = askToDoAnother(choice);
    }

    return 0;
}