#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

using namespace sf;
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 40;
    constexpr float AMPLITUDE = 80.f;
    constexpr float PERIOD = 1.f;

    float speed = 600.f;
    float time = 0;
    float x = 0;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Wave Ball");
    Clock clock;

    Vector2f position = {0, WINDOW_HEIGHT / 2 - AMPLITUDE / 2};

    CircleShape ball(BALL_SIZE);
    ball.setFillColor(Color::Black);

    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();

        time = time + deltaTime;
        x = x + speed * deltaTime;

        const float wavePhase = time * float(2 * M_PI);
        const float y = AMPLITUDE * std::sin(wavePhase / PERIOD);
        const sf::Vector2f offset = {x, y};

        if ((x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed > 0))
        {
            speed = -speed;
        }
        if ((x < 0) && (speed < 0))
        {
            speed = -speed;
        }

        ball.setPosition(position + offset);

        window.clear(Color::White);
        window.draw(ball);
        window.display();
    }
}