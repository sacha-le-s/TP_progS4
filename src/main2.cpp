/*
----------

//#include <guess-the-number.hpp>
#include <hangman2.hpp>
#include <iostream>

----------
*/

/*
int main() {
  std::cout << "Hello World\n";
  play_hangman();
}
*/

/* -----------

#include <iostream>
#include <p6/p6.h>

int main() {
  try {
    // Create the Context by giving the initial size and name of our window
    auto ctx = p6::Context{{1280, 720, "p6 Basic Example"}};
    // Draws an initial background.
    // Since we don't clear the background in our update loop this one will be
    // visible throughout the execution of the program. And objects that are
    // drawn during the update() will remain there too.
    ctx.background({0.5f, 0.3f, 0.8f});
    // Define the update function. It will be called repeatedly.
    ctx.update = [&]() {
      // Clear the objects that were drawn during the previous update

      // Draw a red square
      ctx.fill = p6::Color{1.f, 0.f, 0.f};
      ctx.square(p6::Center{-0.5f, 0.5f}, // Center on the middle of the window
                 p6::Radius{0.98f}, // A radius of 1 would fit the entire window
                                    // so this is quite a big square
                 p6::Rotation{0.01_turn}); // Slightly tilt the square
----------- */

/*
for (int c = 0; c < 3; c++) {
  for (int l = 0; l < 3; l++) {

  // On passe à la colonne suivante
  }

  // On passe à la ligne d'après
}*/

/*
-----------

};
// Start the program
ctx.start();
}
// Log any error that might occur
catch (const std::exception &e) {
std::cerr << e.what() << '\n';
}
}

----------
*/