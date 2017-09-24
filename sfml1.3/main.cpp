#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Domik");

    window.clear(sf::Color::White);

    sf::CircleShape shape1(22.5);
    shape1.setPosition({490, 60});
    shape1.setFillColor(sf::Color(156, 156, 156));
    window.draw(shape1);

    sf::CircleShape shape2(20);
    shape2.setPosition({480, 90});
    shape2.setFillColor(sf::Color(156, 156, 156));
    window.draw(shape2);

    sf::CircleShape shape3(17.5);
    shape3.setPosition({470, 120});
    shape3.setFillColor(sf::Color(156, 156, 156));
    window.draw(shape3);

    sf::CircleShape shape4(15);
    shape4.setPosition({465, 145});
    shape4.setFillColor(sf::Color(156, 156, 156));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({400, 250});
    shape5.setRotation(0);
    shape5.setPosition({200, 320});
    shape5.setFillColor(sf::Color(139, 69, 19));
    window.draw(shape5);

    sf::ConvexShape shape6;
    shape6.setFillColor(sf::Color(139, 0, 0));
    shape6.setPosition(400, 210);
    shape6.setPointCount(4);
    shape6.setPoint(0, {-100, 0});
    shape6.setPoint(1, {+100, 0});
    shape6.setPoint(2, {+250, 110});
    shape6.setPoint(3, {-250, 110});
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({80, 180});
    shape7.setRotation(0);
    shape7.setPosition({250, 390});
    shape7.setFillColor(sf::Color(28, 28, 28));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({50, 35});
    shape8.setRotation(0);
    shape8.setPosition({450, 170});
    shape8.setFillColor(sf::Color(54, 54, 54));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({30, 70});
    shape9.setRotation(0);
    shape9.setPosition({460, 190});
    shape9.setFillColor(sf::Color(54, 54, 54));
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(5));
}