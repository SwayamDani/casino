# 🎰 Casino Project

## 🎮 Game Selection
- 🃏 **Blackjack**: Classic card game where players try to get a higher hand value than the dealer without exceeding 21
- 🎲 **Poker**: Texas Hold'em style poker game with betting rounds and hand evaluation
- 🔴 **Roulette**: European roulette with number, color, and even/odd betting options
- 🎰 **Slot Machine**: Digital slot machine with different symbol combinations and jackpot system

## 📋 Project Description
The casino project simulates a real-life casino experience in a terminal-based environment. It features multiple popular casino games with authentic rules, betting systems, and visually appealing terminal-based graphics using ASCII art and ANSI color codes.

### Why We Created This
- To implement advanced C++ concepts including object-oriented programming, data structures, and game logic
- To create an engaging interactive application that demonstrates software design principles
- To practice collaborative development using Git and GitHub
- To gain experience with testing frameworks like Google Test

### Technologies Used
- **Programming Language**: C++11
- **Build System**: CMake
- **Version Control**: Git & GitHub
- **CI/CD**: GitHub Actions
- **Testing Framework**: Google Test (GTest)
- **Development Environment**: Visual Studio Code, CLion

## 🎮 Game Features

### 🃏 Blackjack
- Player vs. dealer gameplay
- Card visualization with suits and colors
- Betting system with proper payouts
- Hit or stand game mechanics
- Dealer AI that follows casino rules

### 🎲 Poker
- Multiplayer Texas Hold'em style gameplay
- Complete poker hand evaluation system
- Betting rounds: pre-flop, flop, turn, and river
- Visual card representation
- Win detection for all poker hand ranks

### 🔴 Roulette
- European roulette wheel (single zero)
- Multiple betting options:
  - Single number (35:1 payout)
  - Red/Black (1:1 payout)
  - Even/Odd (1:1 payout)
- Animated wheel spinning
- Color-coded terminal visualization

### 🎰 Slot Machine
- Three-reel slot machine with various symbols
- Dynamic jackpot that grows with each play
- Different symbol combinations with varying payouts
- Animated spinning reels
- Win statistics tracking

## 🏗️ Architecture
The project follows object-oriented design principles with separate classes for:
- Game components (Blackjack, Poker, Roulette, Slot Machine)
- Players (tracking bets, cards, and bankroll)
- Dealer (handling card distribution and game management)
- Utilities (display formatting, input handling, etc.)

## 🚀 Installation & Usage

### Prerequisites
- C++11 compatible compiler (GCC, Clang, MSVC)
- CMake (version 3.2 or higher)
- Git (for cloning the repository)

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/SwayamDani/casino.git
   cd casino
   ```

2. Build using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the casino application:
   ```bash
   ./casino
   ```

## 🧪 Testing
The project includes comprehensive unit tests for game logic components using Google Test.

To run the tests:
```bash
./poker_tests
```

## 👥 Contributors
- [Swayam Dani](https://github.com/SwayamDani) - Project Lead, Core Architecture
- [Akaash](https://github.com/asagi003) - Game Mechanics, Testing
- [Tanisha](https://github.com/tanishajha0608) - User Interface, Documentation
- [Jasmine](https://github.com/jasmineptel/Jasmine-Patel) - Game Design, Quality Assurance

## 📜 License
This project is licensed under the MIT License - see the LICENSE file for details.

## 🔮 Future Improvements
- Add additional casino games (Baccarat, Craps, etc.)
- Implement a persistent player database with leaderboards
- Create a graphical user interface using a C++ GUI library
- Add multiplayer support via network play
- Enhance game AI and strategies
