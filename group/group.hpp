#ifndef SOL_GROUP_HPP_
#define SOL_GROUP_HPP_

#include <unordered_set>
#include <memory>
#include <utility>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


namespace sol{

/**
*** template class Group is the basic group used to update and draw entities in a batch
*** There are also methods for a range of entities, checking for membership, clearing
*** the group and checking if the group is empty.
*** This group assumes that it will be storing smart pointers, preferably shared_ptr so that
*** many groups may own a single entity
*** A group object may be moved but it cannot be copied
*/

template <typename E>
class Group: public sf::Drawable, sf::NonCopyable{
public:

    using iterator = typename std::unordered_set<E>::iterator;
    //friend Group<E>;

    Group() {}
    Group(const Group<E>&& group){_entities = std::move(group._entities);}
    void operator=(const Group<E>&& group){_entities = std::move(group._entities);}

    virtual             ~Group() {}

            iterator    begin();
            iterator    end();
            void        add(const E& entity);
            void        remove(const E& entity);
            bool        has(const E& entity);
            void        clear();
            bool        is_empty();
    virtual void        update(sf::Time& time_passed);
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:

    std::unordered_set<E> _entities;

};//end class Group

template <typename E>
typename Group<E>::iterator Group<E>::begin(){
    return _entities.begin();
}

template <typename E>
typename Group<E>::iterator Group<E>::end(){
    return _entities.end();
}

template <typename E>
void Group<E>::add(const E& entity){
    _entities.insert(entity);
}//end add(Entity::ptr entity)


template <typename E>
void Group<E>::remove(const E& entity){
    _entities.erase(entity);
}//end remove(Entity::ptr entity)

template <typename E>
bool Group<E>::has(const E& entity){
    iterator found = _entities.find(entity);
    if (found == end())
        return false;
    return true;
}//end has()

template <typename E>
void Group<E>::clear(){
    _entities.clear();
}//end clear()

template <typename E>
bool Group<E>::is_empty(){
    return _entities.empty();
}//end clear()

template <typename E>
void Group<E>::update(sf::Time& time_passed){
    for (auto entity : _entities)
        entity->update(time_passed);
}//end clear()

template <typename E>
void Group<E>::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (auto entity : _entities)
        entity->draw(target, states);
}//end clear()

}//end namespace sol
#endif
