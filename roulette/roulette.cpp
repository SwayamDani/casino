#include <iostream>
#include <limits>
#include <vector>
#include <unordered_set>
#include <thread>
#include <chrono>
#include <iomanip>
#include "./roulette.h"
#include "../include/utils.h"

using namespace std;

const unordered_set<int> redNumbers = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

roulette::roulette(Player* playerPtr) : player(playerPtr) {}

void roulette::play() {
    char stop = 'N';
    char game_type;

    clearScreen();
    cout << BOLD << RED;
    cout << R"(
╔═════════════════════════════════════════════════╗
║                                                 ║
║           🎲 Welcome to Roulette! 🎲            ║
║                                                 ║
╚═════════════════════════════════════════════════╝
    )" << RESET << endl;
    

    // Sleep for a moment to let the user read the welcome message
    this_thread::sleep_for(chrono::milliseconds(1000));

    while (stop != 'Y' && stop != 'y' && player->getBank() > 0) {
        cout << YELLOW << BOLD << "\n" << centerText("ROULETTE TABLE", 50) << RESET << "\n\n";

        // Display a simplified roulette wheel
        displayRouletteWheel();

        std::cout << "\n";
        
        // Show betting options
        displayBettingOptions();
        
        // Show the player's balance
        cout << CYAN << "\n" << player->getName() << "'s balance: " << GREEN << formatMoney(player->getBank()) << RESET << "\n";

        // Get bet amount
        cout << YELLOW << "\nEnter your bet amount: " << RESET;
        
        // Input validation for bet_amount
        while (true) {
            cin >> bet_amount;
            if (cin.fail() || bet_amount <= 0 || bet_amount > player->getBank()) {
                cout << RED << "Invalid bet amount. Please enter a valid number that you can afford: " << RESET;
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            } else {
                break;  // Break the loop if the input is valid
            }
        }

        // Get bet type
        cout << YELLOW << "\nChoose bet type:\n" << RESET;
        cout << CYAN << "  (N) " << WHITE << "Number (pays 35:1)\n";
        cout << CYAN << "  (E) " << WHITE << "Even/Odd (pays 1:1)\n";
        cout << CYAN << "  (R) " << WHITE << "Red/Black (pays 1:1)\n" << RESET;
        cout << YELLOW << "Your choice: " << RESET;
        
        while (true) {
            cin >> game_type;
            game_type = toupper(game_type); // Convert to uppercase
            if (game_type == 'N' || game_type == 'E' || game_type == 'R') {
                break;
            } else {
                cout << RED << "Invalid choice. Please enter N, E, or R: " << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Process the bet
        process_bet(game_type);

        // Check if player is out of money
        if (player->getBank() <= 0) {
            cout << RED << "\nYou're out of money! Game over.\n" << RESET;
            break;
        }

        // Ask if player wants to continue
        cout << YELLOW << "\nDo you want to play again? (Y/N): " << RESET;
        while (true) {
            cin >> stop;
            stop = toupper(stop); // Convert to uppercase
            if (stop == 'Y' || stop == 'N') {
                break;
            } else {
                cout << RED << "Invalid input. Please enter 'Y' to stop or 'N' to continue: " << RESET;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        if (stop == 'N') {
            clearScreen(); // Clear the screen for the next round
        }
    }

    cout << MAGENTA << "\nThanks for playing Roulette, " << player->getName() << "!" << RESET << endl;
    cout << CYAN << "Final balance: " << GREEN << formatMoney(player->getBank()) << RESET << "\n\n";
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void roulette::animateRouletteSpinning(int finalNumber) {
    // Clear the screen for the animation
    clearScreen();
    
    const int NUM_FRAMES = 30;  // Total frames for animation
    const int FINAL_SLOWDOWN_FRAMES = 10;  // Last frames to slow down
    
    // European roulette wheel with numbers in correct order
    // This is the actual sequence around a European roulette wheel
    std::vector<int> wheelNumbers = {
        0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33,
        1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26
    };
    
    // Set of red numbers
    std::unordered_set<int> redNumbersLocal = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    
    // Find position of final number in the wheel
    int finalPos = 0;
    for (size_t i = 0; i < wheelNumbers.size(); i++) {
        if (wheelNumbers[i] == finalNumber) {
            finalPos = i;
            break;
        }
    }
    
    // Calculate frame durations - starting fast and slowing down
    std::vector<int> frameDurations;
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (i < NUM_FRAMES - FINAL_SLOWDOWN_FRAMES) {
            frameDurations.push_back(50);  // Fast frames (50ms)
        } else {
            // Gradually increase duration for last frames (slowing down)
            int slowdownFactor = (i - (NUM_FRAMES - FINAL_SLOWDOWN_FRAMES) + 1) * 40;
            frameDurations.push_back(50 + slowdownFactor);
        }
    }
    
    // Display spinning animation
    std::cout << YELLOW << BOLD << "\n" << centerText("SPINNING THE ROULETTE WHEEL", 60) << RESET << "\n\n";
    
    int currentPos = 0;
    int rotationAngle = 0;
    
    for (int frame = 0; frame < NUM_FRAMES; frame++) {
        clearScreen();
        
        std::cout << YELLOW << BOLD << "\n" << centerText("SPINNING THE ROULETTE WHEEL", 60) << RESET << "\n\n";
        
        // Calculate current position - speed decreases as we approach the end
        int increment;
        if (frame < NUM_FRAMES - FINAL_SLOWDOWN_FRAMES) {
            increment = 5 - (frame / 8);  // Start fast, gradually slow down
        } else {
            // Very slow for final frames
            increment = 1;
        }
        
        // Ensure we end at the final position
        if (frame == NUM_FRAMES - 1) {
            currentPos = finalPos;
        } else {
            currentPos = (currentPos + increment) % wheelNumbers.size();
        }
        
        // Simulate rotation angle (for visual effect)
        rotationAngle = (rotationAngle + 10) % 360;
        
        // Display wheel with current position highlighted
        displayCircularWheel(wheelNumbers, currentPos, redNumbersLocal, rotationAngle);
        
        // Sleep according to current frame duration
        std::this_thread::sleep_for(std::chrono::milliseconds(frameDurations[frame]));
    }
    
    // Final display of the result
    clearScreen();
    std::cout << YELLOW << BOLD << "\n" << centerText("WHEEL STOPPED", 60) << RESET << "\n\n";
    displayCircularWheel(wheelNumbers, finalPos, redNumbersLocal, 0);
    
    // Determine color and properties of the number
    std::string colorName;
    std::string colorCode;
    std::string evenOdd;
    
    if (finalNumber == 0) {
        colorName = "GREEN";
        colorCode = GREEN;
        evenOdd = "ZERO";
    } else {
        bool is_red = redNumbersLocal.find(finalNumber) != redNumbersLocal.end();
        colorName = is_red ? "RED" : "BLACK";
        colorCode = is_red ? RED : BLACK;
        evenOdd = (finalNumber % 2 == 0) ? "EVEN" : "ODD";
    }
    
    // Display the result
    std::cout << "\n\nThe ball lands on " << colorCode << BOLD << finalNumber << RESET;
    
    // Only show color and even/odd for non-zero numbers
    if (finalNumber != 0) {
        std::cout << " (" << colorCode << colorName << RESET;
        std::cout << ", " << evenOdd << ")";
    } else {
        std::cout << " (" << GREEN << "ZERO" << RESET << ")";
    }
    std::cout << "\n\n";
    
    // Add a short pause after displaying the result
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void roulette::displayCircularWheel(const std::vector<int>& wheelNumbers, int currentPos, const std::unordered_set<int>& redNumbersLocal, int rotation) {
    
    std::cout << "\n";
    std::cout << "            .----------------------------.\n";
    std::cout << "          .'                              '.\n";
    std::cout << "        .'      " << MAGENTA << "EUROPEAN ROULETTE" << RESET << "        '.\n";
    std::cout << "       /                                    \\\n";
    
    // Display top row of numbers
    std::cout << "      |  ";
    for (int i = -3; i <= 3; i++) {
        int pos = (currentPos + i + wheelNumbers.size()) % wheelNumbers.size();
        int num = wheelNumbers[pos];
        
        // Highlight the current position
        if (i == 0) {
            std::cout << "[";
        } else {
            std::cout << " ";
        }
        
        // Apply correct color
        if (num == 0) {
            std::cout << GREEN << std::setw(2) << num << RESET;
        } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
            std::cout << RED << std::setw(2) << num << RESET;
        } else {
            std::cout << WHITE << std::setw(2) << num << RESET;
        }
        
        if (i == 0) {
            std::cout << "]";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "  |\n";
    
    // Middle section with ball
    std::cout << "      |                                    |\n";
    
    // Display the ball in the center for the current number
    std::cout << "      |            ";
    int num = wheelNumbers[currentPos];
    std::string ballColor = YELLOW;
    std::string numColor;
    
    if (num == 0) {
        numColor = GREEN;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        numColor = RED;
    } else {
        numColor = WHITE;
    }
    
    std::cout << "    " << ballColor << "O" << RESET << "               |\n";
    std::cout << "      |            ";
    std::cout << "  " << numColor << BOLD << std::setw(2) << num << RESET << "               |\n";
    std::cout << "      |                                    |\n";
    
    // Bottom row of numbers
    std::cout << "      |  ";
    for (int i = 4; i <= 10; i++) {
        int pos = (currentPos + i + wheelNumbers.size()) % wheelNumbers.size();
        int num = wheelNumbers[pos];
        
        // Apply correct color
        if (num == 0) {
            std::cout << GREEN << std::setw(2) << num << RESET << " ";
        } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
            std::cout << RED << std::setw(2) << num << RESET << " ";
        } else {
            std::cout << WHITE << std::setw(2) << num << RESET << " ";
        }
    }
    std::cout << " |\n";
    
    // Bottom of wheel
    std::cout << "       \\                                    /\n";
    std::cout << "        '.                                .'\n";
    std::cout << "          '.                            .'\n";
    std::cout << "            '----------------------------'\n";
    
    // Spinning indicator at bottom
    std::string spinIndicator;
    if (rotation > 0) {
        spinIndicator = (rotation % 6 < 3) ? ">>> SPINNING >>>" : "<<< SPINNING <<<";
    } else {
        spinIndicator = "    STOPPED    ";
    }
    
    std::cout << "\n";
    std::cout << "            " << YELLOW << spinIndicator << RESET << "\n";
    
    // Ball trajectory indicator
    if (rotation > 0) {
        std::cout << "            ";
        int ballPos = rotation % 15;
        for (int i = 0; i < 15; i++) {
            if (i == ballPos) {
                std::cout << YELLOW << "o" << RESET;
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void roulette::displayWheelAnimation(const std::vector<int>& wheelNumbers, int currentPos, const std::unordered_set<int>& redNumbersLocal) {
    // ASCII art for a simplified roulette wheel with the ball position
    std::cout << WHITE << "               ╭───────────────────╮                " << RESET << std::endl;
    std::cout << WHITE << "            ╭──┤ " << MAGENTA << "    ROULETTE     " << WHITE << "├──╮             " << RESET << std::endl;
    std::cout << WHITE << "          ╭─┤  ╰───────────────────╯  ├─╮           " << RESET << std::endl;
    
    // Display top section of wheel with numbers
    std::cout << WHITE << "        ╭─┤ ";
    
    // Position to left
    int leftPos = (currentPos - 2 + wheelNumbers.size()) % wheelNumbers.size();
    int num = wheelNumbers[leftPos];
    if (num == 0) {
        std::cout << GREEN << std::setw(2) << num << RESET;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        std::cout << RED << std::setw(2) << num << RESET;
    } else {
        std::cout << BLACK << std::setw(2) << num << RESET;
    }
    
    // Position to far left
    leftPos = (currentPos - 1 + wheelNumbers.size()) % wheelNumbers.size();
    num = wheelNumbers[leftPos];
    if (num == 0) {
        std::cout << WHITE << "│" << GREEN << std::setw(2) << num << RESET;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        std::cout << WHITE << "│" << RED << std::setw(2) << num << RESET;
    } else {
        std::cout << WHITE << "│" << BLACK << std::setw(2) << num << RESET;
    }
    
    // Current position (highlighted)
    num = wheelNumbers[currentPos];
    std::string highlight = std::string(BOLD) + std::string(WHITE) + "【";
    std::string endHighlight = std::string(BOLD) + std::string(WHITE) + "】";
    
    if (num == 0) {
        std::cout << highlight << GREEN << BOLD << std::setw(2) << num << endHighlight << RESET;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        std::cout << highlight << RED << BOLD << std::setw(2) << num << endHighlight << RESET;
    } else {
        std::cout << highlight << BLACK << BOLD << std::setw(2) << num << endHighlight << RESET;
    }
    
    // Position to right
    int rightPos = (currentPos + 1) % wheelNumbers.size();
    num = wheelNumbers[rightPos];
    if (num == 0) {
        std::cout << WHITE << "│" << GREEN << std::setw(2) << num << RESET;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        std::cout << WHITE << "│" << RED << std::setw(2) << num << RESET;
    } else {
        std::cout << WHITE << "│" << BLACK << std::setw(2) << num << RESET;
    }
    
    // Position to far right
    rightPos = (currentPos + 2) % wheelNumbers.size();
    num = wheelNumbers[rightPos];
    if (num == 0) {
        std::cout << GREEN << std::setw(2) << num << WHITE << " ├─╮         " << RESET << std::endl;
    } else if (redNumbersLocal.find(num) != redNumbersLocal.end()) {
        std::cout << RED << std::setw(2) << num << WHITE << " ├─╮         " << RESET << std::endl;
    } else {
        std::cout << BLACK << std::setw(2) << num << WHITE << " ├─╮         " << RESET << std::endl;
    }
    
    // Middle of the wheel
    std::cout << WHITE << "        │ ╰─────────┬─┴─┬─────────╯ │         " << RESET << std::endl;
    std::cout << WHITE << "        │           │   │           │         " << RESET << std::endl;
    std::cout << WHITE << "        │           │ " << YELLOW << "▼" << WHITE << " │           │         " << RESET << std::endl;
    std::cout << WHITE << "        │           │   │           │         " << RESET << std::endl;
    std::cout << WHITE << "        ╰───────────┴───┴───────────╯         " << RESET << std::endl;
    
    // Ball animation
    std::string ball = std::string(YELLOW) + "●" + std::string(RESET);
    std::cout << "                      " << ball << "                       " << std::endl;
    std::cout << "                                                 " << std::endl;
}

void roulette::displayRouletteWheel() {
    std::cout << WHITE << "┌─────────────────────────────────────────────────┐" << RESET << std::endl;
    std::cout << WHITE << "│              " << BOLD << "EUROPEAN ROULETTE" << RESET << WHITE << "                  │" << RESET << std::endl;
    std::cout << WHITE << "├─────────────────────────────────────────────────┤" << RESET << std::endl;
    
    // Display numbers in rows
    std::vector<std::vector<int>> numberRows = {
        {03, 06, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36},
        {02, 05, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35},
        {01, 04, 07, 10, 13, 16, 19, 22, 25, 28, 31, 34}
    };
    
    for (const auto& row : numberRows) {
        std::cout << WHITE << "│       ";
        for (int num : row) {
            bool is_red = redNumbers.find(num) != redNumbers.end();
            std::cout << (is_red ? RED : GREEN) << std::setw(2) << num << " " << RESET;
        }
        std::cout << WHITE << "      │" << RESET << std::endl;
    }
    
    std::cout << WHITE << "├────────────┬────────────┬────────────┬──────────┤" << RESET << std::endl;
    std::cout << WHITE << "│  1st 12    │  2nd 12    │  3rd 12    │  " << GREEN << "0" << WHITE << "       │" << RESET << std::endl;
    std::cout << WHITE << "├────────────┼────────────┼────────────┼──────────┤" << RESET << std::endl;
    std::cout << WHITE << "│  1 to 18   │ EVEN/ODD   │  19 to 36  │ " << RED << "RED" << WHITE << "/" << GREEN << "BLACK" << WHITE << "│" << RESET << std::endl;
    std::cout << WHITE << "└────────────┴────────────┴────────────┴──────────┘" << RESET << std::endl;
}

void roulette::displayBettingOptions() {
    std::cout << YELLOW << "Betting Options:" << RESET << std::endl;
    std::cout << CYAN << "1. Straight Up (single number): " << WHITE << "Pays 35 to 1" << RESET << std::endl;
    std::cout << CYAN << "2. Even/Odd: " << WHITE << "Pays 1 to 1" << RESET << std::endl;
    std::cout << CYAN << "3. Red/Black: " << WHITE << "Pays 1 to 1" << RESET << std::endl;
}

void roulette::process_bet(char game_type) {
    int number;
    char bet_choice;
    int random;
    
    // Process the bet based on type and get the bet details first
    if (game_type == 'N') {
        std::cout << YELLOW << "Enter the number you are betting on (0-36): " << RESET;
        while (true) {
            std::cin >> number;
            if (std::cin.fail() || number < 0 || number > 36) {
                std::cout << RED << "Invalid number. Please enter a number between 0 and 36: " << RESET;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
    } else if (game_type == 'E') {
        std::cout << YELLOW << "Choose (E)ven or (O)dd: " << RESET;
        while (true) {
            std::cin >> bet_choice;
            bet_choice = toupper(bet_choice);
            if (bet_choice == 'E' || bet_choice == 'O') {
                break;
            } else {
                std::cout << RED << "Invalid choice. Please enter E or O: " << RESET;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    } else if (game_type == 'R') {
        std::cout << YELLOW << "Choose (R)ed or (B)lack: " << RESET;
        while (true) {
            std::cin >> bet_choice;
            bet_choice = toupper(bet_choice);
            if (bet_choice == 'R' || bet_choice == 'B') {
                break;
            } else {
                std::cout << RED << "Invalid choice. Please enter R or B: " << RESET;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    
    // Get the result
    random = dealer_roulette.spin_wheel();
    
    // Show the animation of the spinning wheel 
    animateRouletteSpinning(random);
    
    // Set of red numbers - recreating it here to avoid scope issues
    std::unordered_set<int> redNumbersLocal = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
    
    // Process the result based on the bet type
    if (game_type == 'N') {
        if (number == random) {
            int winnings = bet_amount * 35;
            std::cout << GREEN << BOLD << "🎉 Congratulations! You win " << formatMoney(winnings) << "!" << RESET << std::endl;
            player->addBank(bet_amount * 36); // Return bet + winnings
        } else {
            std::cout << RED << "Sorry, you lose. The number was " << random << "." << RESET << std::endl;
            player->addBank(-bet_amount); // Deduct bet
        }
    } else if (game_type == 'E') {
        // Handle 0 as a special case (not even or odd)
        if (random == 0) {
            std::cout << RED << "Sorry, you lose. The number was 0 (neither even nor odd)." << RESET << std::endl;
            player->addBank(-bet_amount); // Deduct bet
        } else {
            // Check if the choice matches the result
            bool isEven = (random % 2 == 0);
            if ((bet_choice == 'E' && isEven) || (bet_choice == 'O' && !isEven)) {
                int winnings = bet_amount;
                std::cout << GREEN << BOLD << "🎉 Congratulations! You win " << formatMoney(winnings) << "!" << RESET << std::endl;
                player->addBank(winnings); // Add winnings
            } else {
                std::cout << RED << "Sorry, you lose. The number was " << (isEven ? "even" : "odd") << "." << RESET << std::endl;
                player->addBank(-bet_amount); // Deduct bet
            }
        }
    } else if (game_type == 'R') {
        // Handle 0 as a special case (neither red nor black)
        if (random == 0) {
            std::cout << RED << "Sorry, you lose. The number was 0 (green, neither red nor black)." << RESET << std::endl;
            player->addBank(-bet_amount); // Deduct bet
        } else {
            // Check if the choice matches the result
            bool is_red_number = redNumbersLocal.find(random) != redNumbersLocal.end();
            if ((bet_choice == 'R' && is_red_number) || (bet_choice == 'B' && !is_red_number)) {
                int winnings = bet_amount;
                std::cout << GREEN << BOLD << "🎉 Congratulations! You win " << formatMoney(winnings) << "!" << RESET << std::endl;
                player->addBank(winnings); // Add winnings
            } else {
                std::cout << RED << "Sorry, you lose. The number was " << (is_red_number ? "red" : "black") << "." << RESET << std::endl;
                player->addBank(-bet_amount); // Deduct bet
            }
        }
    }

    // Display updated balance
    std::cout << CYAN << player->getName() << "'s new balance: " << GREEN << formatMoney(player->getBank()) << RESET << std::endl;
}
