#include <SFML\Graphics.hpp>
#include <cmath>

using namespace std;

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, bool &laserDraw)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition);
            laserDraw = true;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &laser, float &dt)
{
    const sf::Vector2f delta = mousePosition - cat.getPosition();
    if (delta.x > 0)
    {
        cat.setScale(1, 1);
    }
    if (delta.x < 0)
    {
        cat.setScale(-1, 1);
    }
    float deltaDistance = sqrt(delta.x * delta.x + delta.y * delta.y);
    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f direction = {
            delta.x / deltaDistance,
            delta.y / deltaDistance};
        float speed = min(deltaDistance, 200.f * dt);
        sf::Vector2f timePosition = direction * speed;
        cat.setPosition(cat.getPosition() + timePosition);
    }

    laser.setPosition(mousePosition);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &laser, bool &laserDraw)
{
    window.clear(sf::Color::White);
    window.draw(cat);
    if (laserDraw)
    {
        window.draw(laser);
    }
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Follow Cat");
    sf::Clock clock;
    sf::Image icon;
    icon.loadFromFile("cat.png");

    window.setIcon(38, 35, icon.getPixelsPtr());

    sf::Texture textureCat;
    textureCat.loadFromFile("cat.png");

    sf::Sprite cat;
    cat.setTexture(textureCat);
    cat.setOrigin(textureCat.getSize().x / 2, textureCat.getSize().y / 2);
    cat.setPosition(400, 300);

    sf::Texture textureLaser;
    textureLaser.loadFromFile("red_pointer.png");

    sf::Sprite laser;
    laser.setTexture(textureLaser);
    laser.setOrigin(textureLaser.getSize().x / 2, textureLaser.getSize().y / 2);

    bool laserDraw = false;

    sf::Vector2f mousePosition = {400, 300};

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, laserDraw);
        float dt = clock.restart().asSeconds();
        update(mousePosition, cat, laser, dt);
        redrawFrame(window, cat, laser, laserDraw);
    }
}