#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({220, 530}), "Svetafor");

    window.clear(sf::Color::White);

    sf::RectangleShape shape1;
    shape1.setSize({200, 500});
    shape1.setRotation(0);
    shape1.setPosition({10, 15});
    shape1.setFillColor(sf::Color(105, 105, 105));
    window.draw(shape1);

    sf::CircleShape shape2(65);
    shape2.setPosition({45, 50});
    shape2.setFillColor(sf::Color::Red);
    window.draw(shape2);

    sf::CircleShape shape3(65);
    shape3.setPosition({45, 200});
    shape3.setFillColor(sf::Color::Yellow);
    window.draw(shape3);

    sf::CircleShape shape4(65);
    shape4.setPosition({45, 350});
    shape4.setFillColor(sf::Color::Green);
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}