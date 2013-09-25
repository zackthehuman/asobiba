#include "Main.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 32;

int main(int argc, char** argv) {

    sf::Clock clock;
    sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    sf::RenderWindow window;

    window.create(videoMode, title);
    window.setActive(true);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    // Set up random number generator
    srand(time(0));

    // Game loop
    float t = 0.0f;
    float accumulator = 0.0f;
    const float dt = 1.0f/60.0f;

    sf::Time currentTime = clock.getElapsedTime();
    
    bool quit = false;
    bool emitParticle = false;
    sf::Vector2f emissionPosition;
    sf::Event event;

    aso::ParticleSystem particleSystem;

    particleSystem.add(aso::Particle());

    while(!quit) {

        sf::Time newTime = clock.getElapsedTime();
        float frameTime = newTime.asSeconds() - currentTime.asSeconds();
        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator >= dt) {

            while(window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    quit = true;
                }

                if(event.type == sf::Event::MouseButtonPressed) {
                    // std::cout << "Mouse pressed!" << std::endl;
                    emitParticle = true;
                }

                if(event.type == sf::Event::MouseButtonReleased) {
                    // std::cout << "Mouse released!" << std::endl;
                    emitParticle = false;
                }

                if(event.type == sf::Event::MouseMoved) {
                    // std::cout << "Mouse moved!" << std::endl;
                    emissionPosition = window.mapPixelToCoords(
                        sf::Vector2i(
                            event.mouseMove.x,
                            event.mouseMove.y
                        ),
                        window.getView()
                    );
                }

            } // closes event processing loop

            accumulator -= dt;
            t += dt;

            if(emitParticle) {
                aso::Particle particle;

                particle.position = emissionPosition;
                particle.velocity = sf::Vector2f(
                    static_cast<float>(rand() % 200) - 100.0f,
                    static_cast<float>(rand() % 200) - 100.0f
                );
                particle.size = static_cast<float>(rand() % 100);
                // particle.color = sf::Color(
                //     rand() % 256,
                //     rand() % 256,
                //     rand() % 256
                // );

                particleSystem.add(particle);
            }

            particleSystem.update(dt);

        } // closes integration loop

        window.clear(sf::Color::Magenta);
        window.draw(particleSystem);
        window.display();

    } // closes !quit loop

    return EXIT_SUCCESS;
}