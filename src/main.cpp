
//#include <guess-the-number.hpp>
#include <hangman2.hpp>
#include <iostream>

/*
int main() {
  std::cout << "Hello World\n";
  play_hangman();
}
*/

#include <iostream>
#include <p6/p6.h>

int main() {
  try {
    // Create the Context by giving the initial size and name of our window
    auto ctx = p6::Context{{720, 720, "p6 Basic Example"}};
    // Draws an initial background.
    // Since we don't clear the background in our update loop this one will be
    // visible throughout the execution of the program. And objects that are
    // drawn during the update() will remain there too.
    // ctx.background({0.5f, 0.3f, 0.8f});
    // Define the update function. It will be called repeatedly.
    ctx.update = [&]() {
      ctx.background({0.2f, 0.9f, 0.7f});
      //  Uncomment this if you want to clear the objects that were drawn during
      //  the previous update: ctx.background({0.5f, 0.3f, 0.8f});

      // Set the colors and size of the stroke that will be used to draw our
      // objects
      ctx.fill = p6::Color{1.f, 0.f, 0.f};        // Red interior
      ctx.stroke = p6::Color{0.f, 0.f, 0.f, 1.f}; // Black outline
      ctx.stroke_weight = 0.f;                    // Size of the outline
      // Draw our first square
      // Draw a white square

      // ctx.square(p6::Center{-0.7f, 0.7f}, // Center on the middle of the
      // window
      //            p6::Radius{0.25f});      // A radius of 1 would fit the
      //            entire
      //  window so this is quite a big square
      // p6::Rotation{0.01_turn}); // Slightly tilt the square

      for (int l = 0; l < 3; l++) {
        float color = 1.f;
        ctx.fill = p6::Color{color, 1.f, 1.f};
        float posx = -0.7f;
        float posy = 0.7f;
        ctx.square(p6::Center{posx, posy}, p6::Radius{0.25f});
        posx = posx + 0.15f;
        color = color - 0.2f;

        // On passe à la colonne suivante
      }
    };
    // Start the program
    ctx.start();
  }
  // Log any error that might occur
  catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
