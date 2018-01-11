#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

struct PRNG
{
    std::mt19937 engine;
};
