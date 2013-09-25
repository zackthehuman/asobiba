#ifndef ASOBIBA_PARTICLESYSTEM_INCLUDED
#define ASOBIBA_PARTICLESYSTEM_INCLUDED

#include "Particle.hpp"

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace aso {

    class ParticleSystem : public sf::Drawable {
    private:
        sf::VertexArray vertices;
        std::vector<Particle> particles;

        void removeDeadParticles();
        void destroyVertexArray();
        void buildVertexArray();
        void buildVerticies(const Particle & particle);
        void updateParticles(float dt);

    public:
        ParticleSystem();
        
        void add(const aso::Particle & particle);
        
        void update(float dt);
        
        virtual void draw(
            sf::RenderTarget& renderTarget,
            sf::RenderStates renderStates
        ) const;

        void clear();
};

} // aso

#endif // ASOBIBA_PARTICLESYSTEM_INCLUDED