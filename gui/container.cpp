#include <iostream>
using namespace std;

#include "container.hpp"

namespace sol{

namespace gui{

void Container::update(sf::Time& time_passed){

    for (auto& item : _components){
        item.second->update(time_passed);
    }
}


bool Container::handle_event(sf::Event& event, sf::RenderWindow& window){

    sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
    sf::Vector2f world_position = window.mapPixelToCoords(pixel_pos);

    if (event.type == sf::Event::KeyPressed or event.type == sf::Event::KeyPressed or
        event.type == sf::Event::TextEntered){
        if (_focused_child){
            _focused_child->handle_event(event, window);
            return true;
        }
    }

    else if (event.type == sf::Event::MouseButtonPressed or event.type == sf::Event::MouseButtonReleased or
             event.type == sf::Event::MouseWheelMoved){

        bool found_clicked_child = false;

        for (auto& item : _components){
            auto widget_rect = item.second->getGlobalBounds();

            if (widget_rect.contains(world_position)){
                // take care of focuses
                if (_focused_child)
                    _focused_child->set_focus(false);

                item.second->set_focus(true);
                _focused_child = item.second;
                item.second->handle_event(event, window);
                found_clicked_child = true;
                return true;
            }
        }

        if (not found_clicked_child){
            if (_focused_child){
                _focused_child->set_focus(false);
                _focused_child = nullptr;
                return false;
            }
        }
    }

    else if (event.type == sf::Event::MouseMoved){

        bool found_hovered_child = false;

        for (auto& item : _components){
            auto widget_rect = item.second->getGlobalBounds();
            if (widget_rect.contains(world_position)){
                if (_hovered_child and item.second != _hovered_child)
                    _hovered_child->set_hover(false);
                _hovered_child = item.second;
                _hovered_child->set_hover(true);
                found_hovered_child = true;
                return true;
            }
        }

        if (not found_hovered_child){
            if (_hovered_child)
                _hovered_child->set_hover(false);
            _hovered_child = nullptr;
            return false;
        }

    }


    return false;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //states.transform *= getTransform();
    for (auto& item : _components){
        item.second->draw(target, states);
    }
}

void Container::grid(Component::Ptr& component, int col, int row){
    auto rect = component->getGlobalBounds();
    sf::Vector2i component_size(rect.width, rect.height);

    if (_col_sizes.count(col)){
        if (_col_sizes[col] < component_size.x){
            _col_sizes[col] = component_size.x;
            for (auto& item : _components){
                if (item.first.x == col){
                    item.second->setPosition(0, 0);
                    grid(item.second, item.first.x, item.first.y);
                }
            }
        }
    }
    else
        _col_sizes[col] = component_size.x;

    if (_row_sizes.count(row)){
        if (_row_sizes[row] < component_size.y){
            _row_sizes[row] = component_size.y;
            for (auto& item : _components){
                if (item.first.y == row){
                    item.second->setPosition(0, 0);
                    grid(item.second, item.first.x, item.first.y);
                }
            }
        }
    }
    else
        _row_sizes[row] = component_size.y;

    sf::Vector2f pos;
    for (auto& item : _col_sizes){
        if (item.first < col){
            pos.x += item.second;
        }
    }
    for (auto& item : _row_sizes){
        if (item.first < row){
            pos.y += item.second;
        }
    }

    pos.x += (_col_sizes[col] - component_size.x) / 2;
    pos.y += (_row_sizes[row] - component_size.y) / 2;
    component->setPosition(getPosition());
    component->move(pos);
    //_components.insert(std::make_pair(sf::Vector2i(col, row), component));
    _components[sf::Vector2i(col, row)] = component;

} // end grid()


sf::FloatRect Container::getGlobalBounds() const{

    sf::FloatRect rect;
    for (auto item : _col_sizes)
        rect.width += item.second;
    for (auto item : _row_sizes)
        rect.height += item.second;

    auto position = getPosition() - getOrigin();
    rect.left = position.x;
    rect.top = position.y;

    return rect;
}


void Container::move(const sf::Vector2f& vec){
    sf::Transformable::move(vec);

    for (auto& item : _components){
        item.second->move(vec);
    }
}

void Container::move(float x, float y){
    sf::Transformable::move(x, y);
    for (auto& item : _components){
        item.second->move(x, y);
    }
}

void Container::setPosition(const sf::Vector2f& vec){
    sf::Transformable::setPosition(vec);

    for (auto& item : _components){
        item.second->move(vec - getPosition());
    }
}

void Container::setPosition(float x, float y){
    sf::Transformable::setPosition(x, y);
    sf::Vector2f vec(x, y);

    for (auto& item : _components){
        item.second->move(vec - getPosition());
    }
}

} // end namespace gui
} // end namespace sol
