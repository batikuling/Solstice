#include <iostream>
using namespace std;

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include "../GUI/container.hpp"
#include "../GUI/label.hpp"
#include "../GUI/button.hpp"
#include "../GUI/simple_textfield.hpp"

int main(void){

    sf::IntRect bounds(0, 0, 800, 576);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(60);

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("fonts/calibri.ttf");

    sf::Texture button_texture;
    button_texture.loadFromFile("images/button.png");
    sf::Texture button_texture_hover;
    button_texture_hover.loadFromFile("images/button_hover.png");

    sol::gui::Container root;
    sol::gui::Label::Ptr label1(new sol::gui::Label("Hello world!", font));
    sol::gui::Label::Ptr label2(new sol::gui::Label("Oh my        !", font, sf::Color::Blue));
    sol::gui::Label::Ptr label3(new sol::gui::Label("A text? How exciting!", font, sf::Color::Magenta));
    sol::gui::Button::Ptr button1(new sol::gui::Button("Press Me many many times!", font,
                                [](const sol::gui::Component::Ptr& component){std::cout << "handler called!" << std::endl;},
                                sf::Color(255, 0, 0)));
    sol::gui::Button::Ptr button2(new sol::gui::Button("Continue", font,
                                [](const sol::gui::Component::Ptr& component){std::cout << "handler called!" << std::endl;},
                                button_texture));
    sol::gui::Button::Ptr button3(new sol::gui::Button("New Game!", font,
                                [](const sol::gui::Component::Ptr& component){std::cout << "handler called!" << std::endl;},
                                button_texture));
    sol::gui::Button::Ptr button4(new sol::gui::Button("Settings!", font,
                                [](const sol::gui::Component::Ptr& component){std::cout << "handler called!" << std::endl;},
                                button_texture));
    sol::gui::Label::Ptr label4(new sol::gui::Label("Another!!", font));
    sol::gui::Label::Ptr label5(new sol::gui::Label("A!", font));

    sol::gui::SimpleTextfield::Ptr textfield1(new sol::gui::SimpleTextfield(200, font));

    /*
    root.grid(label1, 0, 0);
    root.grid(label2, 0, 1);
    root.grid(label3, 1, 1);
    root.grid(label5, 0, 2);
    root.grid(button1, 2, 1);
    root.grid(button2, 1, 2);
    root.grid(label4, 1, 3);
    */

    //sol::gui::Button& button2_ref = static_cast<sol::gui::Button&>(*button2);
    //button2_ref.set_hover_texture(button_texture_hover);
    static_cast<sol::gui::Button&>(*button2).set_hover_texture(button_texture_hover);
    static_cast<sol::gui::Button&>(*button3).set_hover_texture(button_texture_hover);
    static_cast<sol::gui::Button&>(*button4).set_hover_texture(button_texture_hover);

    root.grid(button2, 0, 0);
    root.grid(button3, 0, 1);
    root.grid(button4, 0, 2);
    root.grid(textfield1, 0, 3);

    root.move(200, 200);

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            root.handle_event(event, window);
        } // end events

    sf::Time time_passed = clock.restart();

    root.update(time_passed);

    window.clear(sf::Color(88, 240, 136));

    sol::gui::SimpleTextfield& tf = static_cast<sol::gui::SimpleTextfield&>(*textfield1);
    //cout << tf.get_string() << endl;

    window.draw(root);
    window.display();
    } // end main game loop
} // end main())
