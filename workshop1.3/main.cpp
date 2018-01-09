#include <SFML/Graphics.hpp>

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Cat", sf::Style::Default, settings);
    sf::Image icon;
    icon.loadFromFile("cat.png");

    window.setIcon(38, 35, icon.getPixelsPtr());

    sf::Texture texture;
    texture.loadFromFile("cat.png");
    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(400, 300);

    while (window.isOpen())
    {
        pollEvents(window);
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
}