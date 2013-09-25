#include "Particle.hpp"
#include "MathHelpers.hpp"

namespace aso {

    Particle::Particle()
        : position(0.0f, 0.0f)
        , velocity(0.0f, 0.0f)
        , color(64, 128, 255)
        , size(100.0f)
        , life(1.0f)
        , maxLife(1.0f)
        , alpha(1.0f)
    {

    }

    Particle::Particle(
        const sf::Vector2f & position,
        const sf::Vector2f & velocity,
        sf::Color color,
        float size,
        float life,
        float maxLife,
        float alpha
    )
        : position(position)
        , velocity(velocity)
        , color(color)
        , size(size)
        , life(life)
        , maxLife(maxLife)
        , alpha(alpha)
    {

    }

    void Particle::update(float dt) {
        life -= dt;
        color.a = math::clamp<float>(255.0f * (life / maxLife) * alpha, 0.0f, 255.0f);
        position += velocity * dt;
    }

} // aso