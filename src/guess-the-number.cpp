#include <iostream>
#include <random>

/// Returns a random int between min (included) and max (included)
int rand(int min, int max) {
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_int_distribution<int> distribution{min, max};
  return distribution(generator);
}

/*
int InitRandomInt() {
  int randomInt = random() * 100;
  return randomInt;
}
*/

int PlayersGuess() {
  int Guess = 0;
  std::cout << " What's your guess ? " << std::endl;
  std::cin >> Guess;
  return Guess;
}

int FindTheNumber() {
  int randomInt = rand(0, 100);
  std::cout << " Hey the goal is to find a mysterious integer between 0 and "
               "100 sooo... "
            << std::endl;
  while (PlayersGuess() != randomInt) {
    std::cout << "BRRRRRRRR !!! ---Wrong---" << std::endl;
  }
  std::cout << "OH DEAR LORD :o ---You made it---" << std::endl;
  std::cout << randomInt << std::endl;
  return 0;
}