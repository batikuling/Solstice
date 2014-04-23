#include <iostream>

#include "particle_system.hpp"


namespace sol{


void ParticleSystem::update(const sf::Time& time_passed){

    // age all particles
    for (auto& particle : _particles)
        particle.remaining_lifetime -= time_passed;

    // delete particles with 0 of less lifetime
    while (not _particles.empty() and _particles.front().remaining_lifetime <= sf::Time::Zero)
        _particles.pop_front();


    // update position for active particles and apply affectors to it
    for (auto& particle : _particles){
        particle.position += particle.direction * time_passed.asSeconds() * particle.speed;
        for (auto& pair : _affectors)
            pair.second(particle, time_passed);
    } // end for

    // clear the vertex array so that the particles can be re-positioned
    _vertices.clear();
    for (auto& particle : _particles){
        sf::Vector2f pos = particle.position;
        sf::Vector2f size(_texture.getSize());
        sf::Vector2f half = size / 2.f;

        _add_vertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, particle.color);
        _add_vertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, particle.color);
        _add_vertex(pos.x + half.x, pos.y + half.y, size.x, size.y, particle.color);
        _add_vertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, particle.color);
    } // end for (auto& particle : _particles)

} //end update()


void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &_texture;
    target.draw(_vertices, states);
} //end draw()


void ParticleSystem::add_particle(Particle& particle){

    _particles.push_back(particle);
} // end add_particle()

ParticleSystem::affector_id ParticleSystem::add_affector(std::function<void(Particle&, sf::Time)> affector){
    _affectors.insert(std::make_pair(_last_id++, affector));
} // end add_affector()

void ParticleSystem::remove_affector(ParticleSystem::affector_id id){
    _affectors.erase(id);
} // end remove_affector()


void ParticleSystem::_add_vertex(float pos_x, float pos_y, float tex_x, float tex_y, sf::Color color){
    sf::Vertex vertex;
    vertex.position = sf::Vector2f(pos_x, pos_y);
    vertex.texCoords = sf::Vector2f(tex_x, tex_y);
    vertex.color = color;

    _vertices.append(vertex);
} // end _add_vertex()


} // end namespace sol
