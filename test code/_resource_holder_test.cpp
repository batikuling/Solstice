#include <iostream>
#include <string>
#include <fstream>

#include "../particles.hpp"
#include "../random.hpp"
#include "../vector2.hpp"
#include "../resource_holder.hpp"

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
    int _emission_rate = 300; // per second

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


enum class Textures{fire_large, blue_creep, large_creep};

int main(void){

    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(40);

    sf::Clock clock;

    // ResourceHolder test start
    sol::ResourceHolder<Textures, sf::Texture> texture_holder;
    texture_holder.load(Textures::fire_large, "images/fire_large.png");
    texture_holder.load(Textures::blue_creep, "images/blue_creep.png");
    texture_holder.load(Textures::large_creep, "images/layer_2.png", sf::IntRect(20, 20, 70, 70));

    sol::ParticleSystem system(texture_holder.get(Textures::fire_large));

    // ResourceHolder test end


    sol::ResourceHolder<string, fstream> file_holder;
    file_holder.load("simple_text", "files/test.txt");
    string line;
    getline(file_holder.get("simple_text"), line);
    cout << line << endl;



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
