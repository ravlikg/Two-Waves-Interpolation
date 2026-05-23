#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

int main() {
    constexpr sf::Vector2u windowSize{600, 600};
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode{windowSize}, "Wave Interference", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    sf::Image image(windowSize);
    sf::Texture texture(windowSize);
    sf::Sprite sprite(texture);

    //Амплитуда, частота, фаза
    float amp1 = 30.0f, freq1 = 0.12f, phase1 = 0.0f;
    float amp2 = 30.0f, freq2 = 0.12f, phase2 = 0.0f;
    float distance = 0.3f; //расстояние между двумя источниками

    sf::Vector2f source1(static_cast<float>(windowSize.x) * distance, static_cast<float>(windowSize.y) * 0.5f);
    sf::Vector2f source2(static_cast<float>(windowSize.x) * (1.0f - distance), static_cast<float>(windowSize.y) * 0.5f);

    float t = 0.0f;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        t += 0.2f;

        for (unsigned int y = 0; y < windowSize.y; y++) {
            for (unsigned int x = 0; x < windowSize.x; x++) {
                float fx = static_cast<float>(x);
                float fy = static_cast<float>(y);

                // расстояние к источникам
                float r1 = std::hypot(fx - source1.x, fy - source1.y);
                float r2 = std::hypot(fx - source2.x, fy - source2.y);

                // Формула волн
                float wave1 = amp1 * std::sin(r1 * freq1 - t + phase1);
                float wave2 = amp2 * std::sin(r2 * freq2 - t + phase2);
                float totalWave = wave1 + wave2;

                //Покраска волны
                sf::Color color = sf::Color::Black;
                if (totalWave > 0) {
                    //синий гребень
                    std::uint8_t g = static_cast<std::uint8_t>(std::min(255.0f, totalWave * 0.75f));
                    std::uint8_t b = static_cast<std::uint8_t>(std::min(255.0f, totalWave * 5.0f));
                    color = sf::Color(0, g, b);
                } else {
                    //красный впадина
                    std::uint8_t r = static_cast<std::uint8_t>(std::min(255.0f, -totalWave * 5.0f));
                    color = sf::Color(r, 0, 0);
                }

                image.setPixel({x, y}, color);
            }
        }

        texture.update(image);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
