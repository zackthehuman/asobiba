#include "Main.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdlib>

#include <squirrel.h>
#include <sqstdmath.h>
#include <sqrat.h>
#include <cstdarg>

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 240;
const int SCREEN_BPP = 32;

void squirrelPrintFunction(HSQUIRRELVM vm, const SQChar *s, ...) {
    va_list vl; 
    va_start(vl, s);
    vprintf(s, vl);
    va_end(vl);
    printf("\n");
}

void color_set_r(sf::Color * color, int value) {
    sf::Uint8 r = static_cast<sf::Uint8>(value);

    if(color) {
        color->r = r;
    }
}

int color_get_r(sf::Color * color) {
    if(color) {
        return static_cast<int>(color->r);
    }

    return -1;
}

void color_set_g(sf::Color * color, int value) {
    sf::Uint8 g = static_cast<sf::Uint8>(value);

    if(color) {
        color->g = g;
    }
}

int color_get_g(sf::Color * color) {
    if(color) {
        return static_cast<int>(color->g);
    }

    return -1;
}

void color_set_b(sf::Color * color, int value) {
    sf::Uint8 b = static_cast<sf::Uint8>(value);

    if(color) {
        color->b = b;
    }
}

int color_get_b(sf::Color * color) {
    if(color) {
        return static_cast<int>(color->b);
    }

    return -1;
}

void color_set_a(sf::Color * color, int value) {
    sf::Uint8 a = static_cast<sf::Uint8>(value);

    if(color) {
        color->a = a;
    }
}

int color_get_a(sf::Color * color) {
    if(color) {
        return static_cast<int>(color->a);
    }

    return -1;
}

Sqrat::Table translateSFMLEventToSquirrelTable(HSQUIRRELVM vm, const sf::Event & sfmlEvent) {
    Sqrat::Table eventTable(vm);

    if(sfmlEvent.type == sf::Event::MouseButtonPressed) {
        eventTable
            .SetValue("type", "mouseButtonPressed");
    } else if(sfmlEvent.type == sf::Event::MouseButtonReleased) {
        eventTable
            .SetValue("type", "mouseButtonReleased");
    } else if(sfmlEvent.type == sf::Event::KeyPressed) {
        eventTable
            .SetValue("type", "keyPressed");
    } else if(sfmlEvent.type == sf::Event::KeyReleased) {
        eventTable
            .SetValue("type", "keyReleased");
    } else {
        eventTable
            .SetValue("type", "unknown");
    }

    return eventTable;
}

int main(int argc, char** argv) {

    HSQUIRRELVM vm = sq_open(1024);

    if(vm) {
        // Set print function
        sq_setprintfunc(vm, squirrelPrintFunction, squirrelPrintFunction);

        // Set up root table and standard libs
        sq_pushroottable(vm);
        sqstd_register_mathlib(vm); 
        sq_pop(vm, 1);

        // Set up Sqrat bindings
        Sqrat::DefaultVM::Set(vm);

        // Export classes
        Sqrat::RootTable().Bind(
            _SC("Vector2f"),  
            Sqrat::Class<sf::Vector2f>()
                .Var<float>(_SC("x"), &sf::Vector2f::x)
                .Var<float>(_SC("y"), &sf::Vector2f::y)
        );

        Sqrat::RootTable().Bind(
            _SC("Color"),  
            Sqrat::Class<sf::Color>()
                .GlobalFunc(_SC("getR"), &color_get_r)
                .GlobalFunc(_SC("setR"), &color_set_r)
                .GlobalFunc(_SC("getG"), &color_get_g)
                .GlobalFunc(_SC("setG"), &color_set_g)
                .GlobalFunc(_SC("getB"), &color_get_b)
                .GlobalFunc(_SC("setB"), &color_set_b)
                .GlobalFunc(_SC("getA"), &color_get_a)
                .GlobalFunc(_SC("setA"), &color_set_a)
        ); 

        Sqrat::RootTable().Bind(
            _SC("Particle"),  
            Sqrat::Class<aso::Particle>()
                .Var<sf::Vector2f>(_SC("position"), &aso::Particle::position)
                .Var<sf::Vector2f>(_SC("velocity"), &aso::Particle::velocity)
                .Var<sf::Color>(_SC("color"), &aso::Particle::color)
                .Var<float>(_SC("size"), &aso::Particle::size)
        );

        Sqrat::RootTable().Bind(
            _SC("ParticleSystem"),  
            Sqrat::Class<aso::ParticleSystem>()
                .Func(_SC("add"), &aso::ParticleSystem::add)
                .Func(_SC("update"), &aso::ParticleSystem::update)
        );

        Sqrat::Script script;
        Sqrat::Function scriptedUpdateFunc;
        Sqrat::Function scriptedEventHandlerFunc;

        try {
            script.CompileFile("resources/scripts/hello.nut");
            script.Run();

            script.CompileFile("resources/scripts/gameloop.nut");
            script.Run();
        } catch(Sqrat::Exception & ex) {
            std::cout << "Sqrat Exception! " << ex.Message() << std::endl;
        } catch(std::exception & stdEx) {
            std::cout << "std::exception! " << stdEx.what() << std::endl;            
        }

        scriptedUpdateFunc = Sqrat::Function(Sqrat::RootTable(vm), "update");
        scriptedEventHandlerFunc = Sqrat::Function(Sqrat::RootTable(vm), "handleEvent");
            
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

        Sqrat::RootTable(vm)
            .SetValue("particleSystem", &particleSystem)
            .SetValue("width", SCREEN_WIDTH)
            .SetValue("height", SCREEN_HEIGHT);

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

                    if(event.type == sf::Event::KeyPressed) {
                        if(event.key.code == sf::Keyboard::R) {
                            std::cout << "Reloading game loop file..." << std::endl;

                            try {
                                script.CompileFile("resources/scripts/gameloop.nut");
                                script.Run();
                            } catch(Sqrat::Exception & ex) {
                                std::cout << "Sqrat Exception! " << ex.Message() << std::endl;
                            } catch(std::exception & stdEx) {
                                std::cout << "std::exception! " << stdEx.what() << std::endl;            
                            }

                            scriptedUpdateFunc = Sqrat::Function(Sqrat::RootTable(vm), "update");
                        }
                    }

                    if(event.type == sf::Event::MouseButtonPressed) {
                        emitParticle = true;
                        Sqrat::RootTable(vm).SetValue("emitParticle", emitParticle);
                    }

                    if(event.type == sf::Event::MouseButtonReleased) {
                        emitParticle = false;
                        Sqrat::RootTable(vm).SetValue("emitParticle", emitParticle);
                    }

                    if(event.type == sf::Event::MouseMoved) {
                        emissionPosition = window.mapPixelToCoords(
                            sf::Vector2i(
                                event.mouseMove.x,
                                event.mouseMove.y
                            ),
                            window.getView()
                        );

                        Sqrat::RootTable(vm)
                            .SetValue("mouseX", emissionPosition.x)
                            .SetValue("mouseY", emissionPosition.y);
                    }

                    if(!scriptedEventHandlerFunc.IsNull()) {
                        Sqrat::Table translatedEvent = translateSFMLEventToSquirrelTable(vm, event);
                        Sqrat::Object & objectEventTable = translatedEvent;
                        scriptedEventHandlerFunc.Evaluate<Sqrat::Object>(objectEventTable);
                    }

                } // closes event processing loop

                accumulator -= dt;
                t += dt;

                if(!scriptedUpdateFunc.IsNull()) {
                    scriptedUpdateFunc.Execute(dt);
                }

            } // closes integration loop

            window.clear(sf::Color::Magenta);
            window.draw(particleSystem);
            window.display();

        } // closes !quit loop
    }

    sq_close(vm);

    return EXIT_SUCCESS;
}