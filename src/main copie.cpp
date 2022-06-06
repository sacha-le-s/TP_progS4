
//#include <guess-the-number.hpp>

#include <algorithm>
#include <iostream>
#include <optional>
#include <p6/p6.h>

/*
-----------------------------
Quelques tests pour prendre en main l'affichage sur mac...

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
-----------------------------
-----------------------------
      Ici ma tentative de tracer une ligne de carrés, mais la boucle for tourne
      indéfiniment j'ai essayé d'incrémenter le paramètre "l" de mon "for" à la
      main en l'affichant dans la console, il s'incrémentait bien mais repartait
      de 0 après avoir atteint 3 :

      for (int l = 0; l < 3; l++) {
        std::cout << l << "début" << std::endl;
        // float color = 1.f;
        ctx.fill = p6::Color{1.f, 1.f, 1.f};
        float posx = -0.65f;
        float posy = 0.65f;
        std::cout << posx << std::endl;
        ctx.square(p6::Center{posx, posy}, p6::Radius{0.3f});
        posx = posx + 0.65f;
        l = l + 1;
        std::cout << posx << std::endl;
        std::cout << l << "après" << std::endl;
        // On passe à la colonne suivante
      }
-----------------------------


      int size = 3;

      for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
          ctx.square(
              p6::BottomLeftCorner{p6::map(
                  glm::vec2{static_cast<float>(x), static_cast<float>(y)},
                  glm::vec2{0.2f}, glm::vec2{static_cast<float>(size)},
                  glm::vec2{0.9f}, glm::vec2{0.7f})},
              p6::Radius{1.f / static_cast<float>(size)});
        }
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

*/

// Structure qui représente une cellule (première cellule : (x=0, y=0)) )
struct CellIndex {
  int x;
  int y;
};

// Adapte la taille d'une cellule à celle du tableau
float cell_radius(int board_size) {
  return 1.f / static_cast<float>(board_size);
}

glm::vec2 cell_bottom_left_corner(CellIndex index, int board_size) {
  const auto idx =
      glm::vec2{static_cast<float>(index.x), static_cast<float>(index.y)};
  return p6::map(idx, glm::vec2{0.f}, glm::vec2{static_cast<float>(board_size)},
                 glm::vec2{-1.f}, glm::vec2{1.f});
}

glm::vec2 cell_center(CellIndex index, int board_size) {
  return cell_bottom_left_corner(index, board_size) + cell_radius(board_size);
}

/// Draws a cell at the position specified by `index`
/// It uses the current context's fill, stroke and stroke_weight
void draw_cell(CellIndex index, int board_size, p6::Context &ctx) {
  ctx.square(p6::BottomLeftCorner{cell_bottom_left_corner(index, board_size)},
             p6::Radius{cell_radius(board_size)});
}

void draw_nought(CellIndex index, int board_size, p6::Context &ctx) {
  ctx.stroke = {0.1f, 0.8f, 0.6f};
  ctx.fill = {0.1f, 0.8f, 0.6f, 1};
  ctx.stroke_weight = 0.4f * cell_radius(board_size);
  ctx.circle(p6::Center{cell_center(index, board_size)},
             p6::Radius{0.9f * cell_radius(board_size)});
}

void draw_cross(CellIndex index, int board_size, p6::Context &ctx) {
  ctx.stroke = {0.1f, 0.8f, 0.6f};
  ctx.fill = {0.1f, 0.8f, 0.6f, 1};
  ctx.stroke_weight = 0.4f * cell_radius(board_size);
  const auto center = p6::Center{cell_center(index, board_size)};
  const auto radii = p6::Radii{glm::vec2{1.f, 0.2f} * cell_radius(board_size)};
  const auto rotation = p6::Rotation{0.125_turn};
  ctx.rectangle(center, radii, rotation);
  ctx.rectangle(center, radii, -rotation);
}

// Traçage du tableau de taillz size*size :
void draw_board(int size, p6::Context &ctx) {
  for (int x = 0; x < size; ++x) {
    for (int y = 0; y < size; ++y) {
      ctx.square(p6::BottomLeftCorner{p6::map(
                     glm::vec2{static_cast<float>(x), static_cast<float>(y)},
                     glm::vec2{0.f}, glm::vec2{static_cast<float>(size)},
                     glm::vec2{-1.0f}, glm::vec2{1.f})},
                 p6::Radius{1.f / static_cast<float>(size)});
    }
  }
}

enum class Player {
  Noughts,
  Crosses,
};

template <int size> class Board {
public:
  std::optional<Player> &operator[](CellIndex index) {
    assert(index.x >= 0 && index.x < size && index.y >= 0 && index.y < size);
    return _cells[index.x + index.y * size];
  }

  const std::optional<Player> &operator[](CellIndex index) const {
    assert(index.x >= 0 && index.x < size && index.y >= 0 && index.y < size);
    return _cells[index.x + index.y * size];
  }
  auto begin() { return _cells.begin(); }
  auto begin() const { return _cells.begin(); }
  auto end() { return _cells.end(); }
  auto end() const { return _cells.end(); }

private:
  std::array<std::optional<Player>, size * size> _cells;
};

// Honêtement, je n'avais auuuucune idée de comment coder cette partie ^_^'
std::optional<CellIndex> cell_hovered_by(glm::vec2 position, int board_size) {
  const auto pos =
      p6::map(position, glm::vec2{-1.f}, glm::vec2{1.f}, glm::vec2{0.f},
              glm::vec2{static_cast<float>(board_size)});
  const auto index = CellIndex{static_cast<int>(std::floor(pos.x)),
                               static_cast<int>(std::floor(pos.y))};
  if (index.x >= 0 && index.x < board_size && index.y >= 0 &&
      index.y < board_size) {
    return std::make_optional(index);
  } else {
    return std::nullopt;
  }
}

void draw_player(Player player, CellIndex index, int board_size,
                 p6::Context &ctx) {
  if (player == Player::Noughts) {
    draw_nought(index, board_size, ctx);
  } else {
    draw_cross(index, board_size, ctx);
  }
}

template <int size>
void draw_noughts_and_crosses(const Board<size> &board, p6::Context &ctx) {
  for (int x = 0; x < size; ++x) {
    for (int y = 0; y < size; ++y) {
      const auto cell = board[{x, y}];
      if (cell.has_value()) {
        draw_player(*cell, {x, y}, size, ctx);
      }
    }
  }
}

void change_player(Player &player) {
  if (player == Player::Noughts) {
    player = Player::Crosses;
  } else {
    player = Player::Noughts;
  }
}

template <int board_size>
void try_to_play(std::optional<CellIndex> cell_index, Board<board_size> &board,
                 Player &current_player) {
  if (cell_index.has_value()) {
    const auto cell_is_empty = !board[*cell_index].has_value();
    if (cell_is_empty) {
      board[*cell_index] = current_player;
      change_player(current_player);
    }
  }
}

template <int board_size> bool board_is_full(const Board<board_size> &board) {
  return std::all_of(board.begin(), board.end(),
                     [](const auto &cell) { return cell.has_value(); });
}

template <int board_size>
void try_draw_player_on_hovered_cell(Player player, Board<board_size> board,
                                     p6::Context &ctx) {
  const auto hovered_cell = cell_hovered_by(ctx.mouse(), board_size);
  if (hovered_cell.has_value() && !board[*hovered_cell].has_value()) {
    draw_player(player, *hovered_cell, board_size, ctx);
  }
}

template <int board_size>
std::optional<Player>
check_for_winner_on_line(const Board<board_size> &board,
                         std::function<CellIndex(int)> index_generator) {
  const bool are_all_equal = [&]() {
    for (int position = 0; position < board_size - 1; ++position) {
      if (board[index_generator(position)] !=
          board[index_generator(position + 1)]) {
        return false;
      }
    }
    return true;
  }();
  if (are_all_equal && board[index_generator(0)].has_value()) {
    return *board[index_generator(0)];
  } else {
    return std::nullopt;
  }
}

template <int board_size>
std::optional<Player> check_for_winner(const Board<board_size> &board) {
  std::optional<Player> winner = std::nullopt;
  // Columns
  for (int x = 0; x < board_size && !winner.has_value(); ++x) {
    winner = check_for_winner_on_line(board, [x](int position) {
      return CellIndex{x, position};
    });
  }
  // Rows
  for (int y = 0; y < board_size && !winner.has_value(); ++y) {
    winner = check_for_winner_on_line(board, [y](int position) {
      return CellIndex{position, y};
    });
  }
  // Diagonal
  if (!winner.has_value()) {
    winner = check_for_winner_on_line(board, [](int position) {
      return CellIndex{position, position};
    });
  }
  // Anti-diagonal
  if (!winner.has_value()) {
    winner = check_for_winner_on_line(board, [](int position) {
      return CellIndex{position, board_size - position - 1};
    });
  }
  return winner;
}

template <int board_size>
bool game_is_finished(const Board<board_size> &board) {
  if (const auto winner = check_for_winner(board); winner.has_value()) {
    if (*winner == Player::Noughts) {
      std::cout << "Noughts have won!\n";
    } else {
      std::cout << "Crosses have won!\n";
    }
    return true;
  } else if (board_is_full(board)) {
    std::cout << "This is a draw!\n";
    return true;
  } else {
    return false;
  }
}

int main() {
  // show_menu();
  static constexpr int board_size = 3;
  auto board = Board<board_size>{};
  auto current_player = Player::Crosses;
  auto ctx = p6::Context{{800, 800, "Noughts and Crosses"}};

  ctx.mouse_pressed = [&](p6::MouseButton event) {
    try_to_play(cell_hovered_by(event.position, board_size), board,
                current_player);
  };
  ctx.update = [&]() {
    ctx.background({0.2f, 0.9f, 0.7f});
    ctx.stroke_weight = 0.01f;
    ctx.stroke = {1.f, 1.f, 1.f, 1.f};
    ctx.fill = {0.f, 0.f, 0.f, 0.f};
    draw_board(board_size, ctx);
    draw_noughts_and_crosses(board, ctx);
    try_draw_player_on_hovered_cell(current_player, board, ctx);
    if (game_is_finished(board)) {
      ctx.stop();
    }
  };
  ctx.start();
}
