#include <string>

#include "simple_textfield.hpp"


namespace sol{

namespace gui{

SimpleTextfield::SimpleTextfield(int width, const sf::Font& font):
    _rect_shape(sf::Vector2f(width, 45)), _text("", font){

    _rect_shape.setFillColor(sf::Color(40, 40, 40));
    _rect_shape.setOutlineColor(sf::Color(100, 100, 100));
    _text.setColor(sf::Color::White);

    auto text_bounds = _text.getLocalBounds();
    _text.setOrigin(text_bounds.left, text_bounds.top);

}

void SimpleTextfield::update(sf::Time& time_passed){
    if (has_focus())
        _rect_shape.setOutlineThickness(2);
    else
        _rect_shape.setOutlineThickness(0);
}

void SimpleTextfield::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();

    target.draw(_rect_shape, states);
    target.draw(_text, states);
}


bool SimpleTextfield::handle_event(sf::Event& event){

    if (event.type == sf::Event::TextEntered){
        if (event.text.unicode >= 32 and event.text.unicode <= 126){
            std::string prev_str = _text.getString();
            _text.setString(prev_str + static_cast<char>(event.text.unicode));

            if (_text.getGlobalBounds().width >= _rect_shape.getGlobalBounds().width){
                std::string str = _text.getString();
                _text.setString(str.substr(0, str.size() - 1));
            }
        }
    }

    else if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::BackSpace){
            std::string str = _text.getString();
            _text.setString(str.substr(0, str.size() - 1));
        }
    }

    return true;
}

sf::FloatRect SimpleTextfield::getGlobalBounds() const{
    auto pos = getPosition();
    auto rect = _rect_shape.getGlobalBounds();
    return sf::FloatRect(pos.x, pos.y, rect.width, rect.height);
}


std::string SimpleTextfield::get_string(){
    return _text.getString();
}

} // end namespace gui
} // end namespace sol
