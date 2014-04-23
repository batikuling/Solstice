#include <iostream>
using namespace std;
#include "button.hpp"
#include "../utility.hpp"

namespace sol{

namespace gui{


Button::Button(const std::string& str, const sf::Font& font, const std::function<void(const Component::Ptr&)>& handler, const sf::Color& color):
    _handler(handler), _text(str, font), _type(_ButtonType::COLORED){

    _text.setColor(sf::Color::White);
    _text.move(5, 5);

    auto text_bounds = _text.getLocalBounds();
    _text.setOrigin(text_bounds.left, text_bounds.top);

    _rect_shape.setFillColor(color);
    _rect_shape.setOutlineColor(sf::Color(75, 75, 75));
    _rect_shape.setOutlineThickness(1);

    auto rect = _text.getGlobalBounds();
    _rect_shape.setSize(sf::Vector2f(rect.width + 10, rect.height + 10));


    _rect_shape_hover.setFillColor(color);
    _rect_shape_hover.setOutlineColor(sf::Color(75, 75, 75));
    _rect_shape_hover.setOutlineThickness(1);

    _rect_shape_hover.setSize(sf::Vector2f(rect.width + 10, rect.height + 10));
}


Button::Button(const std::string& str, const sf::Font& font, const std::function<void(const Component::Ptr&)>& handler, const sf::Texture& texture):
    _handler(handler), _text(str, font), _type(_ButtonType::TEXTURED), _sprite(texture), _sprite_hover(texture){

    _text.setColor(sf::Color::White);
    auto text_bounds = _text.getLocalBounds();
    _text.setOrigin(text_bounds.left, text_bounds.top);

    auto sprite_rect = _sprite.getGlobalBounds();
    auto text_rect = _text.getGlobalBounds();
    int x = (sprite_rect.width - text_rect.width) / 2;
    int y = (sprite_rect.height - text_rect.height) / 2;
    _text.move(x, y);
}

void Button::update(sf::Time& time_passed){
    return;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();

    if (_type == _ButtonType::COLORED){
        if (not has_hover())
            target.draw(_rect_shape, states);
        else
            target.draw(_rect_shape_hover, states);
    }
    else {
        if (not has_hover())
            target.draw(_sprite, states);
        else
            target.draw(_sprite_hover, states);
    }
    target.draw(_text, states);
}

bool Button::handle_event(sf::Event& event){

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
        _handler(shared_from_this());

    return true;
}

sf::FloatRect Button::getGlobalBounds() const{
    auto pos = getPosition();
    sf::FloatRect rect;

    if (_type == _ButtonType::COLORED)
        rect = _rect_shape.getGlobalBounds();
    else
        rect = _sprite.getGlobalBounds();
    return sf::FloatRect(pos.x, pos.y, rect.width, rect.height);
}


void Button::set_hover_texture(const sf::Texture& texture){
    _sprite_hover.setTexture(texture);
}

void Button::set_hover_color(const sf::Color& color){
    _rect_shape_hover.setFillColor(color);
}


} // end namespace gui
} // end namespace sol
