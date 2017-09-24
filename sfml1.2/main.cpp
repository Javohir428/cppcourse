#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({750, 600}), "JAVO");

    window.clear(sf::Color::White);

    sf::RectangleShape shape1;
    shape1.setSize({10, 100});
    shape1.setRotation(0);
    shape1.setPosition({150, 250});
    shape1.setFillColor(sf::Color(250, 128, 114));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({10, 40});
    shape2.setRotation(60);
    shape2.setPosition({155, 340});
    shape2.setFillColor(sf::Color(250, 128, 114));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({10, 40});
    shape3.setRotation(-30);
    shape3.setPosition({102, 330});
    shape3.setFillColor(sf::Color(250, 128, 114));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({10, 120});
    shape4.setRotation(20);
    shape4.setPosition({250, 250});
    shape4.setFillColor(sf::Color(0, 191, 255));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({10, 120});
    shape5.setRotation(-20);
    shape5.setPosition({250, 252});
    shape5.setFillColor(sf::Color(0, 191, 255));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({10, 50});
    shape6.setRotation(90);
    shape6.setPosition({280, 310});
    shape6.setFillColor(sf::Color(0, 191, 255));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({10, 120});
    shape7.setRotation(-20);
    shape7.setPosition({350, 250});
    shape7.setFillColor(sf::Color(127, 255, 0));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({10, 120});
    shape8.setRotation(20);
    shape8.setPosition({430, 245});
    shape8.setFillColor(sf::Color(127, 255, 0));
    window.draw(shape8);

    sf::CircleShape shape9(63);
    shape9.setPosition({485, 240});
    shape9.setFillColor(sf::Color(106, 90, 205));
    window.draw(shape9);

    sf::CircleShape shape10(53);
    shape10.setPosition({495.5, 251});
    shape10.setFillColor(sf::Color::White);
    window.draw(shape10);

    window.display();

    sf::sleep(sf::seconds(5));
}