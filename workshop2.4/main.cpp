#include "main.hpp"
#include <iostream>

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

unsigned random_sign(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(1, 200);
    return distribution(generator.engine);
}

unsigned random_color(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

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

void initBalls(std::vector<Ball> &balls)
{
    PRNG generator;
    initGenerator(generator);
    sf::Color color;

    const std::vector<sf::Vector2f> speeds = {
        {65.f, 30.f},
        {-120.f, 130.f},
        {100.f, -150.f},
        {170.f, 300.f},
        {110.f, 80.f}};
    const std::vector<sf::Vector2f> position = {
        {80, 250},
        {160, 250},
        {240, 250},
        {320, 250},
        {400, 250}};

    for (size_t i = 0; i < balls.size(); ++i)
    {
        float signX = random_sign(generator);
        float signY = random_sign(generator);
        float randomSpeedX = random(generator, 100, 300) * pow(-1.0, signX);
        float randomSpeedY = random(generator, 100, 300) * pow(-1.0, signY);
        color.r = random_color(generator);
        color.b = random_color(generator);
        color.g = random_color(generator);
        balls[i].speed = {randomSpeedX, randomSpeedY};
        balls[i].shape.setPosition(position[i]);
        balls[i].shape.setRadius(30);
        balls[i].shape.setFillColor(color);
    }
}

void update(const float dt, std::vector<Ball> &balls)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f direction = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
            float distance1 = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
            float distance2 = 60;
            if (distance1 <= distance2)
            {
                sf::Vector2f acceleration = balls[fi].speed - balls[si].speed;
                float direction2 = acceleration.x * direction.x + acceleration.y * direction.y;
                balls[fi].speed = balls[fi].speed - direction2 / float(std::pow(distance1, 2)) * direction;
                balls[si].speed = balls[si].speed + direction2 / float(std::pow(distance1, 2)) * direction;
            }
        }
    }

    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        if ((position.x + 60 >= 800) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 60 >= 600) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        const float x = balls[i].speed.x * dt;
        const float y = balls[i].speed.y * dt;
        sf::Vector2f offset = {x, y};

        balls[i].shape.setPosition(position + offset);
    }
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Balls");
    sf::Clock clock;

    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(40, 40, icon.getPixelsPtr());

    std::vector<Ball> balls(5);
    initBalls(balls);

    while (window.isOpen())
    {
        pollEvents(window);
        const float dt = clock.restart().asSeconds();
        update(dt, balls);
        window.clear();
        for (size_t i = 0; i < balls.size(); ++i)
        {
            window.draw(balls[i].shape);
        }
        window.display();
    }
}
