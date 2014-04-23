#include <iostream>

#include "../animation.hpp"
#include "../utility.hpp"

using namespace std;

int main(void){

    sf::IntRect bounds(0, 0, 800, 600);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(40);

    sf::Clock clock;

    sf::Texture sheet;
    sheet.loadFromFile("images/test.png");
    sol::Animation anim(sheet, 5, 4, 10, 5, sf::milliseconds(1000));

    sol::center_origin(anim);
    anim.setPosition(200, 200);


    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space)
                    anim.reset();
                else if (event.key.code == sf::Keyboard::Return)
                    anim.rotate(45);
            }
        } //end events


        sf::Time time_passed = clock.restart();

        anim.update(time_passed);

        window.clear(sf::Color(221, 81, 26));
        window.draw(anim);

        auto current_frame = anim.get_frame();
        current_frame.setPosition(400, 50);
        window.draw(current_frame);
        window.display();

        cout << anim.get_num_loops() << endl;
    }


    return EXIT_SUCCESS;

}
