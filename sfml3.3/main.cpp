#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

struct Eye
{
    sf::ConvexShape sclera;
    sf::ConvexShape pupil;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidian(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * float(cos(angle)),
        radiusY * float(sin(angle))};
}

float isInside(const sf::Vector2f &mousePosition, const sf::Vector2f &center, float X, float Y)
{
    return ((pow(mousePosition.x - center.x, 2) / pow(X, 2)) + (pow(mousePosition.y - center.y, 2) / pow(Y, 2)));
}

void updateEye1(Eye &eye1)
{
    constexpr float rotationRadiusX = 40.f;
    constexpr float rotationRadiusY = 80.f;

    const sf::Vector2f sclera1Offset = toEuclidian(rotationRadiusX, rotationRadiusY, eye1.rotation);
    eye1.pupil.setPosition(eye1.position + sclera1Offset);
}

void updateEye2(Eye &eye2)
{
    constexpr float rotationRadiusX = 40.f;
    constexpr float rotationRadiusY = 80.f;

    const sf::Vector2f sclera1Offset = toEuclidian(rotationRadiusX, rotationRadiusY, eye2.rotation);
    eye2.pupil.setPosition(eye2.position + sclera1Offset);
}

void initEyes(Eye &eye1, Eye &eye2)
{
    const sf::Vector2f scleraRadius = {80.f, 140.f};
    const sf::Vector2f pupilRadius = {25.f, 40.f};
    constexpr int pointCount = 200;

    eye1.position = {300, 300};
    eye2.position = {500, 300};

    eye1.sclera.setPosition(eye1.position);
    eye1.sclera.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye1.sclera.setPointCount(pointCount);
    eye2.sclera.setPosition(eye2.position);
    eye2.sclera.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye2.sclera.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            scleraRadius.x * sin(angle),
            scleraRadius.y * cos(angle)};
        eye1.sclera.setPoint(pointNo, point);
        eye2.sclera.setPoint(pointNo, point);
    }

    eye1.pupil.setPointCount(pointCount);
    eye1.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye2.pupil.setPointCount(pointCount);
    eye2.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * sin(angle),
            pupilRadius.y * cos(angle)};
        eye1.pupil.setPoint(pointNo, point);
        eye2.pupil.setPoint(pointNo, point);
    }

    updateEye1(eye1);
    updateEye2(eye2);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
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
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            window.close();
            break;
        default:
            break;
        }
    }
}

void updateEyes(const sf::Vector2f &mousePosition, Eye &eye1, Eye &eye2)
{
    const sf::Vector2f radXY = {40.f, 80.f};

    const float isInsideEye1 = isInside(mousePosition, eye1.sclera.getPosition(), radXY.x, radXY.y);

    const float isInsideEye2 = isInside(mousePosition, eye2.sclera.getPosition(), radXY.x, radXY.y);

    if (isInsideEye1 > 1.f)
    {
        const sf::Vector2f firstEyeDelta = mousePosition - eye1.position;
        eye1.rotation = atan2(firstEyeDelta.y, firstEyeDelta.x);
        updateEye1(eye1);
    }
    else
    {
        eye1.pupil.setPosition(mousePosition);
    }

    if (isInsideEye2 > 1.f)
    {
        const sf::Vector2f secondEyeDelta = mousePosition - eye2.position;
        eye2.rotation = atan2(secondEyeDelta.y, secondEyeDelta.x);
        updateEye2(eye2);
    }
    else
    {
        eye2.pupil.setPosition(mousePosition);
    }
}

void redrawFrame(sf::RenderWindow &window, Eye &eye1, Eye &eye2)
{
    window.clear(sf::Color(255, 165, 0));
    window.draw(eye1.sclera);
    window.draw(eye1.pupil);
    window.draw(eye2.sclera);
    window.draw(eye2.pupil);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye eye1;
    Eye eye2;
    sf::Vector2f mousePosition;
    sf::Clock clock;
    window.setFramerateLimit(60);
    initEyes(eye1, eye2);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateEyes(mousePosition, eye1, eye2);
        redrawFrame(window, eye1, eye2);
    }
}