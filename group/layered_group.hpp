#ifndef SOL_LAYERED_GROUP_HPP
#define SOL_LAYERED_GROUP_HPP


#include <map>
#include <iostream>

#include "group.hpp"


namespace sol{

template <typename E, typename L = int>
class LayeredGroup : public Group<E>{
public:

    void add(E& entity, L layer = L());
    void remove(E& entity);
    void clear();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void draw_layer(L layer, sf::RenderTarget& target, sf::RenderStates states) const;

private:

    std::multimap<L, E> _multimap;

};

template <typename E, typename L>
void LayeredGroup<E, L>::add(E& entity, L layer){
    Group<E>::add(entity);
    _multimap.insert(std::make_pair(layer, entity));
}

template <typename E, typename L>
void LayeredGroup<E, L>::remove(E& entity){
    Group<E>::remove(entity);

    for (auto iter = _multimap.begin(); iter != _multimap.end(); iter++)
        if (iter->second == entity)
            _multimap.erase(iter);
}

template <typename E, typename L>
void LayeredGroup<E, L>::clear(){
    Group<E>::clear();
    _multimap.clear();
}


template <typename E, typename L>
void LayeredGroup<E, L>::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (auto& item : _multimap){
        item.second->draw(target, states);
    }
}

template <typename E, typename L>
void LayeredGroup<E, L>::draw_layer(L layer, sf::RenderTarget& target, sf::RenderStates states) const{
    auto entities = _multimap.equal_range(layer);
    for (auto iter = entities.first; iter != entities.second; iter++){
        iter->second->draw(target, states);
    }
}

} // end namespace sol


#endif // SOL_LAYERED_GROUP_HPP
