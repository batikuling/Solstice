
#ifndef SOL_GUI_LABEL_HPP
#define SOL_GUI_LABEL_HPP


#include <string>

#include "component.hpp"

namespace sol{

namespace gui{

class Label : public Component{
public:
    using Ptr = std::shared_ptr<Label>;
    Label(const std::string& text, sf::Font& font, const sf::Color& color);
    Label(const std::string& text, sf::Font& font);
    void            update(sf::Time& time_passed);
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool            handle_event(sf::Event& event, sf::RenderWindow& window);
    sf::FloatRect   getGlobalBounds() const;
    //void            set_text(const std::string& text);
    std::string&    get_text();

private:
    std::string _string;
    sf::Text    _text;

}; // end class Label


}
}


#endif // SOL_GUI_LABEL_HPP
