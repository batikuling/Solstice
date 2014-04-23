
#include "label.hpp"


namespace sol{

namespace gui{

Label::Label(const std::string& str, sf::Font& font, const sf::Color& color):
    _string(str), _text(str, font){

    auto text_bounds = _text.getLocalBounds();
    _text.setOrigin(text_bounds.left, text_bounds.top);
    _text.setColor(color);
}

Label::Label(const std::string& str, sf::Font& font):
    Label::Label(str, font, sf::Color::White) {}


void Label::update(sf::Time& time_passed){
    return;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    //_text.transform *= getTransform();
    target.draw(_text, states);
}

bool Label::handle_event(sf::Event& event){
    return true;
}


std::string& Label::get_text(){
    return _string;
}

sf::FloatRect Label::getGlobalBounds() const{
    auto pos = getPosition();
    auto rect = _text.getGlobalBounds();
    return sf::FloatRect(pos.x, pos.y, rect.width, rect.height);
}


} // end namespace gui
} // end namespace sol
