#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

// Структура для заполнения массива с шарами
struct Ball
{
    sf::Color color;
    sf::CircleShape shape;
    sf::Vector2f speed;
};

// Для случайного числа
struct PRNG
{
    std::mt19937 engine;
};

// Для случайного числа
void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

// Для случайного числа, в данной программе для скорости
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

// Для случайного значения цвета
unsigned random_color(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

//Для степени (-1) для получения случайного направления скорости
unsigned random_sign(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 1);
    return distribution(generator.engine);
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

// Проверка на отсутствие шаров в радиусе от нажатия мыши
bool itsNotShapeRadius(std::vector<Ball> &balls, sf::Vector2f clickPosition, const float BALL_SIZE)
{
    bool answer = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f delta = balls[i].shape.getPosition() - clickPosition;
        if (vectorLenght(delta) <= BALL_SIZE * 2)
        {
            answer = false;
        }
    }
    return answer;
}

void initBall(std::vector<Ball> &balls, sf::Vector2f clickPosition, const float BALL_SIZE)
{
    if (itsNotShapeRadius(balls, clickPosition, BALL_SIZE))
    {
        Ball bell; // Пустая структура для заполнения нового элемента
        balls.push_back(bell);

        PRNG generator;
        initGenerator(generator);
        sf::Color color;

        // Инициализируем новый шар если он не находится в зоне другого шара
        size_t i = balls.size() - 1;
        float signX = random_sign(generator);
        float signY = random_sign(generator);
        float randomSpeedX = random(generator, 50, 250) * pow(-1.0, signX);
        float randomSpeedY = random(generator, 50, 250) * pow(-1.0, signY);
        balls[i].speed = {randomSpeedX, randomSpeedY};
        balls[i].shape.setRadius(BALL_SIZE);
        color.r = random_color(generator);
        color.b = random_color(generator);
        color.g = random_color(generator);
        balls[i].shape.setFillColor(color);
        balls[i].shape.setPosition({clickPosition});
    }
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, const float BALL_SIZE)
{
    sf::Vector2f clickPosition;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        // Добавляем новый шар при клике мыши
        case sf::Event::MouseButtonReleased:
            clickPosition = {float(event.mouseButton.x) - BALL_SIZE / 2, float(event.mouseButton.y) - BALL_SIZE / 2};
            initBall(balls, clickPosition, BALL_SIZE);
            break;
        default:
            break;
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

// Скалярное произведение
float dot(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

// Обновление скорости про столкновении с другим шаром
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

// Проверка на столкновение шаров и обновление их скорости при его наличии
void checkBallCollision(std::vector<Ball> &balls, const float BALL_SIZE)
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

void checkWallCollision(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float BALL_SIZE, sf::Vector2f &speed, sf::Vector2f &position)
{
    if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((position.x < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, sf::Clock &clock, const float BALL_SIZE, std::vector<Ball> &balls)
{
    const float dt = clock.restart().asSeconds();
    checkBallCollision(balls, BALL_SIZE);
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        checkWallCollision(WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE, balls[i].speed, position);

        balls[i].shape.setPosition(position + balls[i].speed * dt);
    }
}

int main()
{
    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Bouncing Balls");
    sf::Clock clock;

    std::vector<Ball> balls;

    while (window.isOpen())
    {
        pollEvents(window, balls, BALL_SIZE);
        update(WINDOW_WIDTH, WINDOW_HEIGHT, clock, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}