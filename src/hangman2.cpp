#include <array>
#include <get_input_from_user.h>
#include <iostream>
#include <list>
#include <random>
#include <string>

std::array wordsList = {
    "engrenage", "ecrevice",          "voyage",    "celeri",  "pain",
    "housse",    "mdrtutrouveraspas", "publicite", "brrrrrr", "bravo"};

int rand2(int min, int max) {
  static std::default_random_engine generator{std::random_device{}()};
  std::uniform_int_distribution<int> distribution{min, max};
  return distribution(generator);
}

// FREE FUNCTIONS

const char *pick_a_random_word() { return (wordsList[rand2(0, 9)]); }

void show_number_of_lives(int number_of_lives) {
  if (number_of_lives == 1) {
    std::cout
        << "Careful, this is your last life, you might die this time around :d"
        << std::endl;
  } else {
    std::cout << "You have " << number_of_lives << "lives left !" << std::endl;
  }
}
// Je ne comprend pas pourquoi il me met qu'il
// manque un ";" je ne vois pas où ça pourrait manquer

bool player_is_alive(int number_of_lives) {
  if (number_of_lives > 0) {
    return true;
  } else {
    return false;
  }
}

bool player_has_won(const std::vector<bool> &letters_guessed) {
  int number_of_invalid_letters = 0;
  for (int i = 0; i < size(letters_guessed); i++) {
    if (letters_guessed[i] == false) {
      number_of_invalid_letters += 1;
    }
  }
  if (number_of_invalid_letters == 0) {
    return true;
  } else {
    return false;
  }
}

void show_word_to_guess_with_missing_letters(
    const std::string &word, const std::vector<bool> &letters_guessed) {
  std::string word_shown = "";
  for (int i = 0; i < size(letters_guessed); i++) {
    if (letters_guessed[i] == false) {
      word_shown + "_";
    } else {
      word_shown + word[i];
    }
  } // On réécrit le mot lettre par lettre avec des "_"
  // quand la lettre est manquante
  std::cout << word_shown << std::endl;
}

bool word_contains(char letter, std::string_view word) {
  for (int i = 0; i < size(word); i++) {
    if (word[i] == letter) {
      return true;
    }
  }
  return false;
}

void mark_as_guessed(char guessed_letter, std::vector<bool> &letters_guessed,
                     std::string_view word_to_guess) {
  if (word_contains(guessed_letter, word_to_guess) ==
      true) // On vérifie d'abord si la lettre est dans le mot
  {
    for (int i = 0; i < size(word_to_guess); i++) {
      if (guessed_letter == word_to_guess[i]) {
        letters_guessed[i] = true;
      }
    }
  }
  /* On aurait pu croire que dans le cas ou la lettre y est plusieurs fois il y
  aurait des manipulations supplémentaires à faire mais le loop va checker
  chaque lettre une par une et donc valider toutes les occurences de la lettre
  directement */
}

void remove_one_life(int &lives_count) { lives_count = lives_count - 1; }

void show_congrats_message(std::string_view word_to_guess) {
  std::cout << "Congrats on guessing the word " << word_to_guess << " !"
            << std::endl;
}

void show_defeat_message(std::string_view word_to_guess) {
  std::cout << "Ugh.. the word was " << word_to_guess
            << " you dumb trash -_- (take it with a grain of salt pls)"
            << std::endl;
}

void play_hangman() {
  /* ______À RÉARRANGER POUR QUE ÇA FONCTIONNE______

  pick_a_word_to_guess();
  while (player_is_alive() && !player_has_won()) {
  show_number_of_lives();
  show_word_to_guess_with_missing_letters();
  const auto guess = get_char_from_user();
  if (word_to_guess_contains(guess)) {
      mark_as_guessed(guess);
  } else {
      remove_one_life();
  }
  }
  if (player_has_won()) {
  show_congrats_message();
  } else {
  show_defeat_message();
  } */
}
