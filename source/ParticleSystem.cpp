#include "ParticleSystem.hpp"

#include <algorithm>
#include <functional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

namespace aso {

    void ParticleSystem::removeDeadParticles() {
        // Remove dead particles
        particles.erase(
            std::remove_if(
                std::begin(particles),
                std::end(particles),
                [](const aso::Particle & particle) {
                    return particle.life <= 0;
                }
            ),
            std::end(particles)
        );
    }

    void ParticleSystem::destroyVertexArray() {
        vertices.clear();
    }

    void ParticleSystem::buildVertexArray() {
        std::for_each(
            std::begin(particles),
            std::end(particles),
            std::bind(&ParticleSystem::buildVerticies, this, std::placeholders::_1)
        );
    }

    void ParticleSystem::buildVerticies(const Particle & particle) {
        vertices.append(
            sf::Vertex(
                sf::Vector2f(particle.position) - sf::Vector2f(0.0f, particle.size / 2.0f),
                particle.color
            )
        );

        vertices.append(
            sf::Vertex(
                sf::Vector2f(
                    particle.position.x - particle.size / 2,
                    particle.position.y + particle.size) - sf::Vector2f(0.0f, particle.size / 2.0f),
                particle.color
            )
        );

        vertices.append(
            sf::Vertex(
                sf::Vector2f(
                    particle.position.x + particle.size / 2,
                    particle.position.y + particle.size) - sf::Vector2f(0.0f, particle.size / 2.0f),
                particle.color
            )
        );
    }

    void ParticleSystem::updateParticles(float dt) {
        std::for_each(
            std::begin(particles),
            std::end(particles),
            std::bind(&Particle::update, std::placeholders::_1, dt)
        );
    }

    ParticleSystem::ParticleSystem()
        : vertices(sf::PrimitiveType::Triangles)
    {
        particles.reserve(500);
    }

    void ParticleSystem::add(const aso::Particle & particle) {
        particles.push_back(particle);
    }

    void ParticleSystem::update(float dt) {
        removeDeadParticles();
        destroyVertexArray();
        updateParticles(dt);
        buildVertexArray();
    }

    void ParticleSystem::draw(
        sf::RenderTarget& renderTarget,
        sf::RenderStates renderStates
    ) const {
        renderTarget.draw(vertices, renderStates);
    }

    void ParticleSystem::clear() {
        particles.clear();
    }

} // aso
