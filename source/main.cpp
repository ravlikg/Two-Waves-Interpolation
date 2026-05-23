#include <SFML/Graphics.hpp>

int main() {
    constexpr sf::Vector2u windowSize{1920, 1080};
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode{windowSize}, "Wave Interference", sf::Style::Default, sf::State::Fullscreen, settings);
    window.setFramerateLimit(60);

    sf::Texture texture(windowSize);
    sf::Sprite sprite(texture);

    sf::Shader shader;
    if (!shader.loadFromFile("wave.frag", sf::Shader::Type::Fragment)) {
        return -1;
    }

    //Амплитуда, частота, фаза
    float amp1 = 30.0f, freq1 = 0.12f, phase1 = 0.0f;
    float amp2 = 30.0f, freq2 = 0.12f, phase2 = 0.0f;
    float distance = 0.3f; //расстояние между двумя источниками

    // координата y внизу!!!
    sf::Vector2f source1(static_cast<float>(windowSize.x) * distance, static_cast<float>(windowSize.y) * 0.5f);
    sf::Vector2f source2(static_cast<float>(windowSize.x) * (1.0f - distance), static_cast<float>(windowSize.y) * 0.5f);

    float t = 0.0f;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        t += 0.2f;

        // Передаем в видеокарту
        shader.setUniform("t", t);
        shader.setUniform("amp1", amp1);
        shader.setUniform("freq1", freq1);
        shader.setUniform("amp2", amp2);
        shader.setUniform("freq2", freq2);
        shader.setUniform("source1", source1);
        shader.setUniform("source2", source2);

        window.clear();
        window.draw(sprite, &shader);
        window.display();
    }

    return 0;
}