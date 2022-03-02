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

int GetPlayersGuess() {
  int ChosenNumber = 0;
  std::cout << " What's your guess ? " << std::endl;
  std::cin >> ChosenNumber;
  return ChosenNumber;
}

int FindTheNumber() {
  bool answer = false;
  int randomInt = rand(0, 100);
  std::cout << " Hey the goal is to find a mysterious integer between 0 and "
               "100 sooo... "
            << std::endl;

  while (answer != true) {
    int Guess = GetPlayersGuess();
    if (Guess == randomInt) {
      answer = true;
    } else {
      std::cout << "BRRRRRRRR !!! ---Wrong---" << std::endl;
      if (Guess < randomInt) {
        std::cout << "Hint : the number is greater ;)" << std::endl;
      } else {
        std::cout << "Hint : the number is smaller ;)" << std::endl;
      }
    }
  }
  std::cout << "OH DEAR LORD ---You made it---" << std::endl;
  return 0;
}