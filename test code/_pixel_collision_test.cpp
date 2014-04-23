#include <iostream>

#include "../pixel_collision.hpp"
#include "../utility.hpp"

using namespace std;

class TestEntity : public sf::Sprite{
public:
    TestEntity(sf::Texture& texture) : sf::Sprite(texture){
        _mask = texture.copyToImage();
    }

    const sf::Image& get_mask() const{
        return _mask;
    }

private:
    sf::Image _mask;
};

int main(void){
    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(40);

    sf::Texture tex1;
    sf::Texture tex2;
    tex1.loadFromFile("images/pixel_2.png");
    tex2.loadFromFile("images/pixel_1.png");

    TestEntity sprite1(tex1);
    TestEntity sprite2(tex2);
    sprite1.setPosition(300, 300);
    sol::center_origin(sprite1);
    sol::center_origin(sprite2);


    sf::Clock clock;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    sprite1.rotate(45);
                    sprite2.rotate(45);
                }
                //else if (event.key.code == sf::Keyboard::Return)
                //    anim.rotate(45);
            }
        } //end events

        if (sol::pixel_collision(sprite1, sprite2))
            cout << "collision!!" << endl;
        else
            cout << "no collision" << endl;

        sf::Time time_passed = clock.restart();

        sprite2.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

        window.clear(sf::Color(221, 81, 26));
        window.draw(sprite1);
        window.draw(sprite2);

        window.display();
    } // end main game loop


    return EXIT_SUCCESS;
}

