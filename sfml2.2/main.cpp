#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

using namespace sf;
using namespace std;
int main()
{
    constexpr int DEFAULT_RADIUS = 150;
    constexpr int POINT_COUNT = 200;
    constexpr float AMPLITUDE = 80.f;
    constexpr float PERIOD = 2.f;

    float time = 0;

    ContextSettings settings;
    settings.antialiasingLevel = 7;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Polar Rose", Style::Default, settings);
    Clock clock;

    Vector2f position = {(WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2)};

    ConvexShape rose;
    rose.setFillColor(sf::Color::Red);

    rose.setPointCount(POINT_COUNT);
    for (int i = 0; i < POINT_COUNT; ++i)
    {
        float angle = (2 * M_PI * i) / (POINT_COUNT);
        float RADIUS = DEFAULT_RADIUS * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{RADIUS * std::sin(angle), RADIUS * std::cos(angle)};
        rose.setPoint((i), point);
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();

        time += deltaTime;

        const float wavePhase = time * float(2 * M_PI);
        const float x = DEFAULT_RADIUS * cos(wavePhase / PERIOD);
        const float y = DEFAULT_RADIUS * sin(wavePhase / PERIOD);
        const Vector2f offset = {x, y};

        rose.setPosition(position + offset);

        window.clear(Color::White);
        window.draw(rose);
        window.display();
    }
}