#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

enum class Color
{
  white,
  black,
};

struct PieceTextures
{
  sf::Texture pawn, bishop, knight, rook, queen, king;
  
  void loadForColor(const std::string& colorPrefix)
  {
    pawn.loadFromFile("pieces/" + colorPrefix + "-pawn.png");
    bishop.loadFromFile("pieces/" + colorPrefix + "-bishop.png");
    knight.loadFromFile("pieces/" + colorPrefix + "-knight.png");
    rook.loadFromFile("pieces/" + colorPrefix + "-rook.png");
    queen.loadFromFile("pieces/" + colorPrefix + "-queen.png");
    king.loadFromFile("pieces/" + colorPrefix + "-king.png");
  }
};

struct Pos
{
  int m_x{};
  int m_y{};
};

class Pieces
{
  private:
    Color m_color;
    std::vector<Pos> m_pawns;
    std::vector<Pos> m_bishops;
    std::vector<Pos> m_knights;
    std::vector<Pos> m_rooks;
    std::vector<Pos> m_queens;
    Pos m_king;

  public:
    Pieces(int firstY, int secondY, Color color)
      : m_color{color}
      , m_king{5, firstY}
    {
      for (int x{1}; x <= 8; x++)
      {
        m_pawns.push_back({x, secondY});
      }

      for (int x : {3, 6})
      {
        m_bishops.push_back({x, firstY});
      }

      for (int x : {2, 7})
      {
        m_knights.push_back({x, firstY});
      }

      for (int x : {1, 8})
      {
        m_rooks.push_back({x, firstY});
      }

      m_queens.push_back({4, firstY});
    }

    const Color& getColor() const { return m_color; }
    const std::vector<Pos>& getPawns() const { return m_pawns; }
    const std::vector<Pos>& getBishops() const { return m_bishops; }
    const std::vector<Pos>& getKnights() const { return m_knights; }
    const std::vector<Pos>& getRooks() const { return m_rooks; }
    const std::vector<Pos>& getQueens() const { return m_queens; }
    const Pos& getKing() const { return m_king; }
};

std::vector<sf::Sprite> renderPieces(const std::vector<Pos>& positions, float squareSize, float offset, const sf::Texture& texture)
{
  std::vector<sf::Sprite> spriteArr;

  for (const auto& pos : positions)
  {
    sf::Sprite sprite(texture);

    const float scale{squareSize / texture.getSize().x};
    sprite.setScale({scale, scale}); 

    const float posX{offset + (pos.m_x - 1) *  squareSize};
    const float posY{offset + (8 - pos.m_y) *  squareSize};

    sprite.setPosition({posX, posY});

    spriteArr.push_back(sprite);
  }

  return spriteArr;
}

sf::Sprite renderKing(const Pos& pos, float squareSize, float offset, const sf::Texture& texture)
{
  sf::Sprite sprite(texture);

  const float scale{squareSize / texture.getSize().x};
  sprite.setScale({scale, scale}); 

  const float posX{offset + (pos.m_x - 1) *  squareSize};
  const float posY{offset + (8 - pos.m_y) *  squareSize};

  sprite.setPosition({posX, posY});

  return sprite;
}

int main()
{
  const int windowSize{900};

  sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Chess");
  window.setFramerateLimit(30);
  
  PieceTextures whiteTextures, blackTextures;
  whiteTextures.loadForColor("white");
  blackTextures.loadForColor("black");

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
    for (const auto& sprite : renderPieces(white.getPawns(), squareSize, offset, whiteTextures.pawn))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(white.getBishops(), squareSize, offset, whiteTextures.bishop))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(white.getKnights(), squareSize, offset, whiteTextures.knight))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(white.getRooks(), squareSize, offset, whiteTextures.rook))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(white.getQueens(), squareSize, offset, whiteTextures.queen))
      window.draw(sprite);
    window.draw(renderKing(white.getKing(), squareSize, offset, whiteTextures.king));

    for (const auto& sprite : renderPieces(black.getPawns(), squareSize, offset, blackTextures.pawn))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(black.getBishops(), squareSize, offset, blackTextures.bishop))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(black.getKnights(), squareSize, offset, blackTextures.knight))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(black.getRooks(), squareSize, offset, blackTextures.rook))
      window.draw(sprite);
    for (const auto& sprite : renderPieces(black.getQueens(), squareSize, offset, blackTextures.queen))
      window.draw(sprite);
    window.draw(renderKing(black.getKing(), squareSize, offset, blackTextures.king));

    window.display();
  }

 return 0;
}
