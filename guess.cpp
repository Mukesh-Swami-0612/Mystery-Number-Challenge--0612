#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

void displayWelcomeLogo() {
    cout << "**************************************************" << endl;
    cout << "*                                                *" << endl;
    cout << "*       Welcome to the Higher or Lower Game!     *" << endl;
    cout << "*                                                *" << endl;
    cout << "*                 Best of Luck!                  *" << endl;
    cout << "*                                                *" << endl;
    cout << "**************************************************" << endl;
    cout << endl;
}

void displaySparkles() {
    cout << "*****************************************" << endl;
    cout << "*   *     *     * *     *     *     *   *" << endl;
    cout << "*   Congratulations! You win!    *     *" << endl;
    cout << "*   *     *     * *     *     *     *   *" << endl;
    cout << "*****************************************" << endl;
}

void displaySadFace() {
    cout << "*****************************************" << endl;
    cout << "*        Better luck next time! :(      *" << endl;
    cout << "*****************************************" << endl;
}

void displayLastRounds(const vector<string>& rounds) {
    if (rounds.empty()) {
        cout << "No rounds have been played yet." << endl;
    } else {
        cout << "Last 3 rounds results:" << endl;
        for (const string& round : rounds) {
            cout << round << endl;
        }
    }
}

void displayStats(int gamesPlayed, int wins, int losses) {
    cout << "*****************************************" << endl;
    cout << "*            Player Statistics           *" << endl;
    cout << "*****************************************" << endl;
    cout << "* Games Played: " << gamesPlayed << "                       *" << endl;
    cout << "* Wins: " << wins << "                                *" << endl;
    cout << "* Losses: " << losses << "                              *" << endl;
    cout << "*****************************************" << endl;
}

int main() {
    srand(time(0));
    vector<string> lastRounds;
    int gamesPlayed = 0, wins = 0, losses = 0;
    char choice;

    while (true) {
        displayWelcomeLogo();
        cout << "Choose an option:" << endl;
        cout << "1. Start a new game" << endl;
        cout << "2. Display the last 3 rounds" << endl;
        cout << "3. Display player statistics" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        if (choice == '1') {
            int maxRange = 100;
            int attempts = 5;

            cout << "Select difficulty level: " << endl;
            cout << "1. Easy (1-50, 7 attempts)" << endl;
            cout << "2. Medium (1-100, 5 attempts)" << endl;
            cout << "3. Hard (1-200, 3 attempts)" << endl;
            int difficulty;
            cin >> difficulty;

            if (difficulty == 1) {
                maxRange = 50;
                attempts = 7;
            } else if (difficulty == 3) {
                maxRange = 200;
                attempts = 3;
            }

            int ranNum = rand() % maxRange + 1;
            bool win = false;
            int guess;
            int pTries = 0;
            string result;

            while (!win && pTries < attempts) {
                if (pTries == attempts - 1) {
                    cout << "This is your last attempt! Here are 5 numbers to choose from: ";
                    int options[5];
                    bool numberIncluded = false;

                    for (int i = 0; i < 5; ++i) {
                        options[i] = rand() % maxRange + 1;
                    }

                    if (!numberIncluded) {
                        options[rand() % 5] = ranNum;
                    }

                    for (int i = 0; i < 5; ++i) {
                        cout << options[i] << " ";
                    }
                    cout << endl;
                } else {
                    cout << "Guess a number between 1 and " << maxRange << ": ";
                }

                cin >> guess;
                pTries++;

                if (guess == ranNum) {
                    displaySparkles();
                    cout << "Congratulations! You guessed the number in " << pTries << " tries!" << endl;
                    win = true;
                    wins++;
                    result = "Win: Guessed the number " + to_string(ranNum) + " in " + to_string(pTries) + " tries.";
                } else if (pTries == attempts) {
                    displaySadFace();
                    cout << "Sorry, the correct number was " << ranNum << ". Better luck next time!" << endl;
                    losses++;
                    result = "Loss: Did not guess the number " + to_string(ranNum) + " in " + to_string(attempts) + " tries.";
                    break;
                } else if (guess < ranNum) {
                    cout << "Too low! ";
                } else {
                    cout << "Too high! ";
                }

                // Provide a hint if not the last attempt
                if (!win && pTries < attempts - 1) {
                    int range = maxRange / 10;
                    if (abs(guess - ranNum) <= range) {
                        cout << "You're very close!" << endl;
                    } else if (abs(guess - ranNum) <= range * 2) {
                        cout << "You're close!" << endl;
                    } else {
                        cout << "Not close." << endl;
                    }
                }
            }

            // Record the result of the game
            gamesPlayed++;
            if (lastRounds.size() == 3) {
                lastRounds.erase(lastRounds.begin());
            }
            lastRounds.push_back(result);

        } else if (choice == '2') {
            displayLastRounds(lastRounds);
        } else if (choice == '3') {
            displayStats(gamesPlayed, wins, losses);
        } else if (choice == '4') {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
