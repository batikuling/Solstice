#include <iostream>

#include "../Particles/particle_system.hpp"
#include "../random.hpp"
#include "../vector2.hpp"
#include "../Particles/emitter.hpp"

using namespace std;

class Fireworks : public sol::Emitter {
public:

    Fireworks(sol::ParticleSystem& system) : sol::Emitter(system){}

    void update(sf::Time& time_passed){
        for (int i = 0; i < _emission_rate * time_passed.asSeconds(); i++){
            sol::Particle particle;
            particle.position = _position;
            particle.direction = _random_direction();
            particle.speed = 120.f;
            particle.total_lifetime = sf::seconds(3);
            particle.remaining_lifetime = sf::seconds(3);
            particle.color = sf::Color(255, 255, 255);

            _system.add_particle(particle);
        }
    } // end update()

    void set_position(sf::Vector2i pos){
        _position = sf::Vector2f(pos);
    }

private:
    sf::Vector2f _position;
    int _emission_rate = 500; // per second

    sf::Vector2f _random_direction(){

        sf::Vector2f vec;
        vec.x = sol::randint(-1, 1);
        vec.y = sol::randint(-1, 1);
        if (vec.x == 0 and vec.y == 0){
            vec.x = 1;
        }
        sol::normalize(vec);
        float rotation = sol::randint(1, 360);
        sol::rotate(vec, rotation);
        return vec;
    }
};


void fader(sol::Particle& particle, sf::Time time_passed){
    float ratio = particle.remaining_lifetime.asSeconds() / particle.total_lifetime.asSeconds();
    particle.color.a = static_cast<sf::Uint8>(255 * ratio);
}


int main(void){

    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(70);

    sf::Clock clock;

    sf::Texture texture;
    texture.loadFromFile("images/fire_large.png");
    sol::ParticleSystem system(texture);

    Fireworks fireworks(system);
    system.add_affector(fader);

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        } //end events


        sf::Time time_passed = clock.restart();

        fireworks.set_position(sf::Mouse::getPosition(window));
        fireworks.update(time_passed);
        system.update(time_passed);

        window.clear(sf::Color(221, 81, 26));
        window.draw(system);

        window.display();
    } // end main game loop


    return EXIT_SUCCESS;

} // end main()
