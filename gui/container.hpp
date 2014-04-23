#ifndef SOL_GUI_CONTAINER_HPP
#define SOL_GUI_CONTAINER_HPP

#include <unordered_map>


#include "component.hpp"
#include "../utility.hpp"

namespace sol{

namespace gui{


class Container : public Component {
public:
    void            grid(Component::Ptr& component, int col, int row);
    void            update(sf::Time& time_passed);
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool            handle_event(sf::Event& event);
    sf::FloatRect   getGlobalBounds() const;

    void            move(const sf::Vector2f& vec);
    void            move(float x, float y);
    void            setPosition(const sf::Vector2f& vec);
    void            setPosition(float x, float y);

private:
    std::unordered_map<sf::Vector2i, Component::Ptr>    _components;
    std::unordered_map<int, int>                        _col_sizes;
    std::unordered_map<int, int>                        _row_sizes;
    Component::Ptr                                      _focused_child = nullptr;
    Component::Ptr                                      _hovered_child = nullptr;
    sf::Vector2i                                        _size;
};


} // end namespace gui
} // end namespace sol

#endif // SOL_GUI_CONTAINER_HPP
