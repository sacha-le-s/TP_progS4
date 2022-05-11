#include <iostream>
#include <p6/p6.h>
/*
void draw_board(int size, p6::Context &ctx) {
  // Create the Context by giving the initial size and name of our window
  auto ctx = p6::Context{{1280, 720, "p6 Basic Example"}};
  // Define the update function. It will be called repeatedly.
  ctx.update = [&]() {
    // Clear the objects that were drawn during the previous update
    ctx.background({0.5f, 0.3f, 0.8f});
    // Draw board
    for (int c = 0; c < 3; c++) {
      for (int l = 0; l < 3; l++) {
        ctx.square(
            p6::Center{-0.5f, 0.5f}, // Center on the middle of the window
            p6::Radius{0.98f},       // A radius of 1 would fit the entire
                                     // window so this is quite a big square
            // p6::Rotation{0.01_turn}  // Slightly tilt the square
        );
        // On passe à la colonne suivante
      }
      // On passe à la ligne d'après
    }
  };
  // Start the program
  ctx.start();
}
*/