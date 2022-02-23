#include <iostream>
#include <pick-a-number.hpp>

int RandomNumber()
{
    int randomInt = random() * 100;
    std::cout << randomInt << std::endl;
    return randomInt;
}

int PlayersGuess()
{
    int Guess = 0;
    std::cout << " Hey the goal is to find a mysterious integer between 0 and 100 sooo... " << std::endl;
    std::cout << " What's your guess ? " << std::endl;
    std::cin >> Guess;
    return Guess;
}

int main()
{
    RandomNumber();
    return 0;
}