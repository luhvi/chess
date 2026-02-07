#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

enum class Color
{
  white,
  black
};

struct Pos
{
  int x{};
  int y{};
};

class Pieces
{
  private:
    Color color;
    std::vector<Pos> pawns;
    std::vector<Pos> bishops;
    std::vector<Pos> knights;
    std::vector<Pos> rooks;
    std::vector<Pos> queens;
    Pos king;

  public:
    Pieces(int firstY, int secondY, Color teamColor)
      : color{teamColor}
      , king{5, firstY}
    {
      for (int x{1}; x <= 8; x++)
      {
        pawns.push_back({x, secondY});
      }

      for (int x : {3, 6})
      {
        bishops.push_back({x, firstY});
      }

      for (int x : {2, 7})
      {
        knights.push_back({x, firstY});
      }

      for (int x : {1, 8})
      {
        rooks.push_back({x, firstY});
      }

      queens.push_back({4, firstY});
    }

    const Color& getColor() const { return color; }

    const std::vector<Pos>& getPawns() const { return pawns; }
    const std::vector<Pos>& getBishops() const { return bishops; }
    const std::vector<Pos>& getKnights() const { return knights; }
    const std::vector<Pos>& getRooks() const { return rooks; }
    const std::vector<Pos>& getQueens() const { return queens; }
    const Pos& getKing() const { return king; }
};

std::vector<sf::Sprite> renderPawns(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : pieces.getPawns())
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.x - 1) *  squareSize};
    const float posY{offset + (8 - pos.y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

std::vector<sf::Sprite> renderBishops(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : pieces.getBishops())
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.x - 1) *  squareSize};
    const float posY{offset + (8 - pos.y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

std::vector<sf::Sprite> renderKnights(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : pieces.getKnights())
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.x - 1) *  squareSize};
    const float posY{offset + (8 - pos.y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

std::vector<sf::Sprite> renderRooks(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : pieces.getRooks())
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.x - 1) *  squareSize};
    const float posY{offset + (8 - pos.y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

std::vector<sf::Sprite> renderQueens(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : pieces.getQueens())
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.x - 1) *  squareSize};
    const float posY{offset + (8 - pos.y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

sf::Sprite renderKing(const Pieces& pieces, float squareSize, float offset, const sf::Texture& texture)
{
  sf::Sprite sprite(texture);

  const float scale{squareSize / texture.getSize().x};
  sprite.setScale({scale, scale}); 

  const float posX{offset + (pieces.getKing().x - 1) *  squareSize};
  const float posY{offset + (8 - pieces.getKing().y) *  squareSize};

  sprite.setPosition({posX, posY});

  return sprite;
}

int main()
{
  const int windowSize{900};

  sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Chess");
  window.setFramerateLimit(30);

  sf::Texture whitePawnTexture;
  whitePawnTexture.loadFromFile("pieces/white-pawn.png");

  sf::Texture whiteBishopTexture;
  whiteBishopTexture.loadFromFile("pieces/white-bishop.png");

  sf::Texture whiteKnightTexture;
  whiteKnightTexture.loadFromFile("pieces/white-knight.png");

  sf::Texture whiteRookTexture;
  whiteRookTexture.loadFromFile("pieces/white-rook.png");

  sf::Texture whiteQueenTexture;
  whiteQueenTexture.loadFromFile("pieces/white-queen.png");
  
  sf::Texture whiteKingTexture;
  whiteKingTexture.loadFromFile("pieces/white-king.png");

  sf::Texture blackPawnTexture;
  blackPawnTexture.loadFromFile("pieces/black-pawn.png");

  sf::Texture blackBishopTexture;
  blackBishopTexture.loadFromFile("pieces/black-bishop.png");

  sf::Texture blackKnightTexture;
  blackKnightTexture.loadFromFile("pieces/black-knight.png");

  sf::Texture blackRookTexture;
  blackRookTexture.loadFromFile("pieces/black-rook.png");

  sf::Texture blackQueenTexture;
  blackQueenTexture.loadFromFile("pieces/black-queen.png");

  sf::Texture blackKingTexture;
  blackKingTexture.loadFromFile("pieces/black-king.png");

  const int spaces{64};

  const float squareSize{100.f};
  const float boardSize{squareSize * 8.f};
  const float offset{(windowSize - boardSize) / 2.f};

  Pieces white{1, 2, Color::white};
  Pieces black{8, 7, Color::black};

  while (window.isOpen())
  {
    while (auto ev{window.pollEvent()})
    {
      if (ev->is<sf::Event::Closed>())
        window.close();
    }
    window.clear({44, 54, 82});

    for (int i{0}; i < spaces; i++)
    {
      const int row{i / 8};
      const int col{i % 8};

      const float posX{col * squareSize + offset};
      const float posY{row * squareSize + offset};

      sf::RectangleShape space(sf::Vector2f(squareSize, squareSize));
      space.setPosition(sf::Vector2f(posX, posY));

      if ((row + col) % 2 == 0)
        space.setFillColor({100, 113, 142});
      else
        space.setFillColor({157, 172, 204});

      window.draw(space);
    }

    auto whitePawns{renderPawns(white, squareSize, offset, whitePawnTexture)};
    for (const auto& pawn : whitePawns)
    {
      window.draw(pawn);
    }

    auto whiteBishops{renderBishops(white, squareSize, offset, whiteBishopTexture)};
    for (const auto& bishop : whiteBishops)
    {
      window.draw(bishop);
    }

    auto whiteKnights{renderKnights(white, squareSize, offset, whiteKnightTexture)};
    for (const auto& knight : whiteKnights)
    {
      window.draw(knight);
    }

    auto whiteRooks{renderRooks(white, squareSize, offset, whiteRookTexture)};
    for (const auto& rook : whiteRooks)
    {
      window.draw(rook);
    }

    auto whiteQueens{renderQueens(white, squareSize, offset, whiteQueenTexture)};
    for (const auto& queen : whiteQueens)
    {
      window.draw(queen);
    }

    auto whiteKing{renderKing(white, squareSize, offset, whiteKingTexture)};
    window.draw(whiteKing);

    auto blackPawns{renderPawns(black, squareSize, offset, blackPawnTexture)};
    for (const auto& pawn : blackPawns)
    {
      window.draw(pawn);
    }

    auto blackBishops{renderBishops(black, squareSize, offset, blackBishopTexture)};
    for (const auto& bishop : blackBishops)
    {
      window.draw(bishop);
    }

    auto blackKnights{renderKnights(black, squareSize, offset, blackKnightTexture)};
    for (const auto& knight : blackKnights)
    {
      window.draw(knight);
    }

    auto blackRooks{renderRooks(black, squareSize, offset, blackRookTexture)};
    for (const auto& rook : blackRooks)
    {
      window.draw(rook);
    }

    auto blackQueens{renderQueens(black, squareSize, offset, blackQueenTexture)};
    for (const auto& queen : blackQueens)
    {
      window.draw(queen);
    }
    auto blackKing{renderKing(black, squareSize, offset, blackKingTexture)};
    window.draw(blackKing);

    window.display();
  }

 return 0;
}
