cmake_minimum_required(VERSION 3.2)

# Set the project name
project(casino)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(casino
    main.cpp
    ./lib/dealer.cpp
    ./lib/player.cpp
    ./lib/utils.cpp
    ./poker/pokerGame.cpp
    ./poker/declareWinner.cpp
    ./poker/handEvaluator.cpp
    ./poker/pokerOutput.cpp
    ./poker/pokerBetting.cpp
    ./roulette/roulette.cpp
    ./blackjack/blackjack.cpp
    ./blackjack/blackjack.h
    ./slot/slotMachine.cpp
)

# Add a custom target to run Valgrind
add_custom_target(run_valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./PokerGame
    DEPENDS PokerGame
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add the executable for the tests
add_executable(poker_tests 
    tests/poker_tests.cpp
    ./poker/declareWinner.cpp
    ./poker/handEvaluator.cpp
    ./poker/pokerOutput.cpp
    ./lib/utils.cpp
)

# Link the Google Test libraries
target_link_libraries(poker_tests gtest gtest_main)

# Add the test to CMake's testing framework
add_test(NAME PokerTests COMMAND poker_tests)