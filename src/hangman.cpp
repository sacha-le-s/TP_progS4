#include <iostream>
#include <list>
#include <random>
#include <string>

std::vector wordsList = {
    "engrenage", "ecrevice",          "voyage",    "celeri",  "pain",
    "housse",    "mdrtutrouveraspas", "publicite", "brrrrrr", "bravo"};

bool isAlive = true;
bool hasWon = false;

int rand2(int min, int max) {
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_int_distribution<int> distribution{min, max};
  return distribution(generator);
}

int set_life() { return 8; }

int lose_one_life(int life) { return life - 1; }

char get_players_letter() {
  char ChosenLetter = ' ';
  std::cout << " What's your guess ? " << std::endl;
  std::cin >> ChosenLetter;
  return ChosenLetter;
}

std::string get_a_word(std::vector<std::string> list) {
  int randomPos = rand2(0, size(list));
  return list[randomPos];
}

void CheckTheLetter(char letter) {}