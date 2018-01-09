#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

using namespace std;

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
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &dt)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float timeRotation = 200 * dt;
    const float mouseRotation = abs(angle - arrow.getRotation());
    if (angle > arrow.getRotation())
    {
        if ((angle - 180) < arrow.getRotation())
        {
            arrow.setRotation(arrow.getRotation() + min(timeRotation, mouseRotation));
        }
        else
        {
            arrow.setRotation(arrow.getRotation() - min(timeRotation, mouseRotation));
        }
    }
    else
    {
        if ((angle + 180) > arrow.getRotation())
        {
            arrow.setRotation(arrow.getRotation() - min(timeRotation, mouseRotation));
        }
        else
        {
            arrow.setRotation(arrow.getRotation() + min(timeRotation, mouseRotation));
        }
    }

    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f direction = {
            delta.x / sqrt(delta.x * delta.x + delta.y * delta.y),
            delta.y / sqrt(delta.x * delta.x + delta.y * delta.y)};
        sf::Vector2f timePosition = direction * 100.f * dt;
        arrow.setPosition(arrow.getPosition() + timePosition);
    }
}
int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Follow Arrow", sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, arrow, dt);
        window.clear(sf::Color::White);
        window.draw(arrow);
        window.display();
    }
}