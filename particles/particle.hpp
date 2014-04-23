#ifndef SOL_PARTICLE_HPP
#define SOL_PARTICLE_HPP


namespace sol{

/**
*** Particle represents a single particle in a system. remaining_life and total_lifetime
*** is set to the same value by an emitter when it creates a particle. ParticleSystem
*** will deduct time_passed to particle.remaining_lifetime on particle_system.update()
*** and if it reaches 0, it will be removed. The type attribute will be used by affectors
*** to determine whether it should affect the certain particle
**/

struct Particle{
    sf::Vector2f    position;
    sf::Vector2f    direction;
    sf::Time        remaining_lifetime;
    sf::Time        total_lifetime;
    sf::Color       color;
    float           speed;
    int             type;
};


} //end namespace sol


#endif // SOL_PARTICLE_HPP
