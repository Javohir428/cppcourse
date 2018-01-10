#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

void init(std::vector<Ball> &balls, const float BALL_SIZE)
{
    balls[0].shape.setPosition({20, 300});
    balls[1].shape.setPosition({120, 300});
    balls[2].shape.setPosition({220, 300});
    balls[3].shape.setPosition({320, 300});
    balls[4].shape.setPosition({420, 300});

    balls[0].shape.setFillColor(sf::Color(0, 255, 255));
    balls[1].shape.setFillColor(sf::Color(255, 0, 255));
    balls[2].shape.setFillColor(sf::Color(255, 255, 0));
    balls[3].shape.setFillColor(sf::Color(0, 0, 255));
    balls[4].shape.setFillColor(sf::Color(0, 255, 0));

    balls[0].shape.setRadius(BALL_SIZE);
    balls[1].shape.setRadius(BALL_SIZE);
    balls[2].shape.setRadius(BALL_SIZE);
    balls[3].shape.setRadius(BALL_SIZE);
    balls[4].shape.setRadius(BALL_SIZE);

    balls[0].speed = {500.f, -100.f};
    balls[1].speed = {-400.f, 200.f};
    balls[2].speed = {300.f, -300.f};
    balls[3].speed = {-200.f, 400.f};
    balls[4].speed = {100.f, -500.f};
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].shape);
    }
    window.display();
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

float dot(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

void speedUpdate(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPos = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    float speedX = balls[fi].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    float speedY = balls[fi].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[fi].speed = {speedX, speedY};

    deltaPos = -deltaPos;
    deltaSpeed = -deltaSpeed;
    speedX = balls[si].speed.x - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    speedY = balls[si].speed.y - (dot(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[si].speed = {speedX, speedY};
}

void collisionCheck(std::vector<Ball> &balls, const float BALL_SIZE)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f delta = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
            if (vectorLenght(delta) <= BALL_SIZE * 2)
            {
                speedUpdate(balls, fi, si);
            }
        }
    }
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float dt, const float BALL_SIZE, std::vector<Ball> &balls)
{
    collisionCheck(balls, BALL_SIZE);
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].shape.setPosition(position + balls[i].speed * dt);
    }
}

int main()
{

    constexpr float BALL_SIZE = 40;
    constexpr int BALLS_COUNT = 5;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bouncing Balls");
    sf::Clock clock;

    std::vector<Ball> balls(BALLS_COUNT);

    init(balls, BALL_SIZE);

    while (window.isOpen())
    {
        pollEvents(window);
        const float dt = clock.restart().asSeconds();
        update(WINDOW_WIDTH, WINDOW_HEIGHT, dt, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}