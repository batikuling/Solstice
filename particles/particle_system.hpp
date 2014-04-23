#ifndef SOL_PARTICLE_SYSTEM_HPP
#define SOL_PARTICLE_SYSTEM_HPP

#include <functional>
#include <deque>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "particle.hpp"

namespace sol{

/**
*** This particle system is responsible for updating the remaining_lifetime of the particle,
*** applying the registered affectors to each particle and drawing the particles
**/

class ParticleSystem : public sf::Drawable, sf::Transformable{
public:
    using affector_id = int;

    ParticleSystem(sf::Texture& texture):
        _texture(texture),
        _vertices(sf::Quads){}

    void        update(const sf::Time& time_passed);
    void        draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void        add_particle(Particle& particle);
    affector_id add_affector(std::function<void(Particle&, sf::Time)> affector);
    void        remove_affector(affector_id id);


private:
    sf::Texture&            _texture;
    sf::VertexArray         _vertices;
    std::deque<Particle>    _particles;
    int                     _last_id = 0;
    std::unordered_map<affector_id, std::function<void(Particle&, sf::Time)>> _affectors;

    void _add_vertex(float pos_x, float pos_y, float tex_x, float tex_y, sf::Color color);

}; //end class ParticleSystem

} // end namespace sol


#endif // SOL_PARTICLE_SYSTEM_HPP
