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
    std::vector<Pos> ponds;

  public:
    Pieces(int firstY, int secondY, Color teamColor) : color{teamColor}
    {
      for (int x{1}; x <= 8; x++)
      {
        ponds.push_back({x, secondY});
      }
    }

    const Color& getColor() const
    {
      return color;
    }

    const std::vector<Pos>& getPonds() const
    {
      return ponds;
    }
};

std::vector<sf::CircleShape> getPonds(const Pieces& pieces, float squareSize, float offset)
{
  std::vector<sf::CircleShape> result;

  const float radius{squareSize * 0.25f};
  const float centerOffset{(squareSize - radius * 2.f) / 2.f};

  for (const auto& pos : pieces.getPonds())
  {
    sf::CircleShape pond(radius);

    switch (pieces.getColor())
    {
      case Color::white:
        pond.setFillColor(sf::Color::White);
        break;

      case Color::black:
        pond.setFillColor(sf::Color::Black);
        break;
    }
    
    const float posX{offset + (pos.x - 1) *  squareSize + centerOffset};
    const float posY{offset + (8 - pos.y) *  squareSize + centerOffset};

    pond.setPosition(sf::Vector2f(posX, posY));
    result.push_back(pond);
  }

  return result;
}

int main()
{
  const int windowSize{900};

  sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Chess");
  window.setFramerateLimit(30);

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

    auto whitePonds{getPonds(white, squareSize, offset)};
    auto blackPonds{getPonds(black, squareSize, offset)};

    for (const auto& pond : whitePonds)
    {
      window.draw(pond);
    }

    for (const auto& pond : blackPonds)
    {
      window.draw(pond);
    }

    window.display();
  }

 return 0;
}
