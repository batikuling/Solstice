
#ifndef SOL_GUI_SIMPLE_TEXTFIELD_HPP
#define SOL_GUI_SIMPLE_TEXTFIELD_HPP


#include "component.hpp"


namespace sol{

namespace gui{

class SimpleTextfield : public Component {
public:
    using Ptr = std::shared_ptr<SimpleTextfield>;

                    SimpleTextfield(int width, const sf::Font& font);
    void            update(sf::Time& time_passed);
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool            handle_event(sf::Event& event, sf::RenderWindow& window);
    sf::FloatRect   getGlobalBounds() const;
    std::string     get_string();

private:
    sf::Text            _text;
    sf::RectangleShape  _rect_shape;
    sf::RectangleShape  _cursor_rect;
};

} // end namespace gui
} // end namespace sol

#endif // SOL_GUI_SIMPLE_TEXTFIELD_HPP
