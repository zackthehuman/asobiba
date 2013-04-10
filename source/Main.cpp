#include "Main.hpp"
#include <cstdlib>
#include <iostream>

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

    // Game loop
    float t = 0.0f;
    float accumulator = 0.0f;
    const float dt = 1.0f/60.0f;

    sf::Time currentTime = clock.getElapsedTime();
    
    bool quit = false;
    sf::Event event;

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

            } // closes event processing loop

            accumulator -= dt;
            t += dt;

        } // closes integration loop

        window.clear(sf::Color::Magenta);
        window.display();

    } // closes !quit loop

    return EXIT_SUCCESS;
}