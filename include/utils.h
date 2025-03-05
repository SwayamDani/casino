#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

extern const char* RESET;
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* MAGENTA;
extern const char* CYAN;
extern const char* WHITE;
extern const char* BOLD;
extern const char* BLACK;

std::string formatMoney(int amount);
std::string centerText(const std::string& text, int width);
void getIntInput(int& input);
void clearScreen();
void printCardFormatted(int card);
void printCard(int card);


#endif // UTILS_H 