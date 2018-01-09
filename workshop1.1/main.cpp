#include <SFML/Graphics.hpp>
#include <cmath>

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition(400, 300);
    arrow.setFillColor(sf::Color::Yellow);
    arrow.setPointCount(7);
    arrow.setPoint(0, {50, 0});
    arrow.setPoint(1, {0, -50});
    arrow.setPoint(2, {0, -25});
    arrow.setPoint(3, {-50, -25});
    arrow.setPoint(4, {-50, 25});
    arrow.setPoint(5, {0, 25});
    arrow.setPoint(6, {0, 50});
    arrow.setOutlineColor(sf::Color::Black);
    arrow.setOutlineThickness(2);
    arrow.setRotation(-70);
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arrow", sf::Style::Default, settings);
    sf::ConvexShape arrow;
    initArrow(arrow);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(arrow);
        window.display();
    }
}