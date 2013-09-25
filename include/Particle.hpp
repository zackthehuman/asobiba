#ifndef ASOBIBA_PARTICLE_INCLUDED
#define ASOBIBA_PARTICLE_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

namespace aso {

    class Particle {
    public:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Color color;
        float size;
        float life;
        float maxLife;
        float alpha;

    public:
        Particle();
        Particle(
            const sf::Vector2f & position,
            const sf::Vector2f & velocity,
            sf::Color color,
            float size,
            float life,
            float maxLife,
            float alpha
        );

        void update(float dt);
    };

} // aso

#endif // ASOBIBA_PARTICLE_INCLUDED