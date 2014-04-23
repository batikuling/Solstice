#ifndef SOL_GUI_BUTTON_HPP
#define SOL_GUI_BUTTON_HPP

#include <string>
#include <functional>

#include "component.hpp"


namespace sol{

namespace gui{

class Button : public Component{
public:
    Button(const std::string& str, const sf::Font& font, const std::function<void(const Component::Ptr&)>& handler, const sf::Color& = sf::Color::Blue);
    Button(const std::string& str, const sf::Font& font, const std::function<void(const Component::Ptr&)>& handler, const sf::Texture& texture);
    void            set_handler(std::function<void(Component::Ptr&)>& handler);
    void            update(sf::Time& time_passed);
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool            handle_event(sf::Event& event);
    sf::FloatRect   getGlobalBounds() const;

    void            set_hover_texture(const sf::Texture& texture);
    void            set_hover_color(const sf::Color& color);

public:
    enum class _ButtonType {TEXTURED, COLORED};

    std::function<void(const Component::Ptr&)>   _handler;
    _ButtonType                             _type;
    sf::Text                                _text;
    sf::RectangleShape                      _rect_shape;
    sf::RectangleShape                      _rect_shape_hover;
    sf::Sprite                              _sprite;
    sf::Sprite                              _sprite_hover;


};

} // end namespace gui
} // end namespace sol


#endif // SOL_GUI_BUTTON_HPP
