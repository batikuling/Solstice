#ifndef SOL_GUI_COMPONENT_HPP
#define SOL_GUI_COMPONENT_HPP


#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace sol{

namespace gui{

class Component : public sf::Drawable, public sf::Transformable, public sf::NonCopyable, public std::enable_shared_from_this<Component>{
public:
    using Ptr = std::shared_ptr<Component>;

    virtual                 ~Component();
    virtual void            update(sf::Time& time_passed) = 0;
    virtual void            draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual bool            handle_event(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual sf::FloatRect   getGlobalBounds() const = 0;
    void                    set_focus(bool focus);
    bool                    has_focus() const;
    void                    set_hover(bool hover);
    bool                    has_hover() const ;

private:
    bool    _focus;
    bool    _hover;
};

} // end namespace gui
} // end namespace sol


#endif // SOL_GUI_COMPONENT_HPP
