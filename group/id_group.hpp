#ifndef SOL_ID_GROUP_HPP_
#define SOL_ID_GROUP_HPP_


#include <unordered_map>
#include <stdexcept>

#include "group.hpp"


namespace sol{

/**
*** template class IDGroup is an entity group where you access entities through the given ID
*** upon adding the entity to the group. Has the methods begin, end, has, is_empty, update and
*** draw from Group<>
*/


template <typename E>
class IDGroup : public Group<E>{
public:
    //replaces Group<>.add(E)
    void add(E& entity, unsigned int id);

    void remove(E& entity);
    void remove_by_id(unsigned int id);
    void clear();
    bool has_id(unsigned int id);
    E&   get_by_id(unsigned int id);

private:
    std::unordered_map<unsigned int, E> _entity_map;
};


template <typename E>
void IDGroup<E>::add(E& entity, unsigned int id){
    Group<E>::add(entity);
    _entity_map.insert(std::make_pair(id, entity));
}


template <typename E>
void IDGroup<E>::remove(E& entity){
    Group<E>::remove(entity);

    unsigned int id;
    for (auto& pair : _entity_map){
        if (pair.second == entity){
            _entity_map.erase(pair.first);
            return;
        }
        else
            throw std::out_of_range("\nKey does not exist!\n");
    }
}


template <typename E>
void IDGroup<E>::remove_by_id(unsigned int id){
    if (_entity_map.count(id)){
        Group<E>::remove(_entity_map[id]);
        _entity_map.erase(id);
    }
    else
        throw std::out_of_range("\nKey does not exist!\n");
}

template <typename E>
bool IDGroup<E>::has_id(unsigned int id){
    if (_entity_map.count(id))
        return true;
    return false;
}

template <typename E>
E& IDGroup<E>::get_by_id(unsigned int id){
    return _entity_map.at(id);
}

template <typename E>
void IDGroup<E>::clear(){
    Group<E>::clear();
    _entity_map.clear();
}


}//end namespace sol
#endif // SOL_ID_GROUP_HPP_
