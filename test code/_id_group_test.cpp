#include <iostream>
#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../entity.hpp"
#include "../id_group.hpp"
#include "../vector2.hpp"
#include "../creep.hpp"


int main(){

    std::cout << std::boolalpha;

    std::srand(time(0));
    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(40);

    sf::Clock clock;

    std::vector<sf::Texture> creep_textures;

    creep_textures.push_back(sf::Texture());
    creep_textures.push_back(sf::Texture());
    creep_textures.push_back(sf::Texture());
    creep_textures[0].loadFromFile("images/green_creep.png");
    creep_textures[1].loadFromFile("images/red_creep.png");
    creep_textures[2].loadFromFile("images/blue_creep.png");

    sol::IDGroup<std::shared_ptr<Creep>> creeps;

    std::shared_ptr<Creep> creep(nullptr);
    int id;
    for (id = 0; id < 4; id++){

        float x = std::rand() % 700 + 50;
        float y = std::rand() % 500 + 50;
        int t = std::rand() % 3;
        creep = std::shared_ptr<Creep>(new Creep(creep_textures[t], sf::Vector2f(x, y), bounds, id));
        creeps.add(creep, id);
    }



    //start sol::IDGroup tests
    std::cout << "range based for loop test, printing ids: ";
    for (auto entity : creeps){
        std::cout << entity->id_ << " ";
    }
    std::cout << std::endl;

    std::cout << "group.get_by_id(0) returns creep with id: " << creeps.get_by_id(0)->id_ << std::endl;

    //add(Entity::ptr) works if window opens with creeps
    std::cout << "remove(creep) works if creep dies: ";
    creeps.remove(creep);
    creep = nullptr;

    std::cout << "remove_by_id(id) for id 2 works if creep dies: ";
    creeps.remove_by_id(2);

    creep = *creeps.begin();
    std::cout << "creeps has creep: " << creeps.has(creep) << std::endl;
    std::cout << "clear() will kill lots of creeps: " << std::endl;
    creeps.clear();
    //Group::IDGroup() and draw() obviously works if there are creeps in the window!
    //end sol::IDGroup tests

    creep = std::shared_ptr<Creep>(new Creep(creep_textures[0], sf::Vector2f(200, 222), bounds, ++id));
    //some deleted/replace functions that should not work:
    //creeps.add(creep); //success on deleting this! compiler reports that this is a deleted function

    std::cout << "end of tests!" << std::endl << std::endl;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    float x = std::rand() % 700 + 50;
                    float y = std::rand() % 500 + 50;
                    int t = std::rand() % 3;
                    creep = std::shared_ptr<Creep>(new Creep(creep_textures[t], sf::Vector2f(x, y), bounds, ++id));
                    creeps.add(creep, id);
                    creep = nullptr;
                }//end if pressed Space
                else if (event.key.code == sf::Keyboard::BackSpace){

                    if (not creeps.is_empty()){
                        auto unlucky = *creeps.begin();
                        creeps.remove(unlucky);
                    }
                }//end if pressed BackSpace
            }// end if keypressed
        } //end events


        sf::Time time_passed = clock.restart();

        creeps.update(time_passed);
        //group.update(time_passed);
        window.clear(sf::Color(221, 81, 26));
        window.draw(creeps);
        //window.draw(group);
        window.display();
    }

    return 0;

}

