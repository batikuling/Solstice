
#include "../Group/collision.hpp"
#include "../Group/group.hpp"
#include "creep.hpp"



int main(void){

    std::cout << std::boolalpha;

    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(40);

    std::vector<sf::Texture> creep_textures;

    creep_textures.push_back(sf::Texture());
    creep_textures.push_back(sf::Texture());
    creep_textures.push_back(sf::Texture());
    creep_textures[0].loadFromFile("images/green_creep.png");
    creep_textures[1].loadFromFile("images/red_creep.png");
    creep_textures[2].loadFromFile("images/blue_creep.png");

    sol::Group<std::shared_ptr<Creep>> creeps;
    std::shared_ptr<Creep> big_creep(new Creep(creep_textures[0], sf::Vector2f(50, 50), bounds, 0));


    std::shared_ptr<Creep> creep(nullptr);
    int id;
    for (id = 1; id < 5; id++){

        float x = std::rand() % 700 + 50;
        float y = std::rand() % 500 + 50;
        creep = std::shared_ptr<Creep>(new Creep(creep_textures[2], sf::Vector2f(x, y), bounds, id));
        creeps.add(creep);
    }


    sf::Clock clock;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            //else if (event.type == sf::Event::KeyPressed)
            //    if (event.key.code == sf::Keyboard::Space)
        } //end events

        sf::Time time_passed = clock.restart();

        creeps.update(time_passed);
        big_creep->update(time_passed);

        if (sol::entity_collide_any(big_creep, creeps))
            std::cout << "collision with at least 1 creep!" << std::endl;

        auto collide_list = sol::entity_collide(big_creep, creeps);
                            //sol::collide_pixel<std::shared_ptr<Creep>, std::shared_ptr<Creep>>);
        //decltype(collide_list) test_copy = collide_list; // tests group copy, this must fail!

        for (auto& creep : collide_list){
            creeps.remove(creep);
        }

        window.clear(sf::Color(221, 81, 26));
        window.draw(creeps);
        window.draw(*big_creep);

        window.display();
    } // end main game loop


    return EXIT_SUCCESS;


}
