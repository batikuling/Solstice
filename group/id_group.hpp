#ifndef SOL_ID_GROUP_HPP_
#define SOL_ID_GROUP_HPP_


#include <unordered_map>
#include <stdexcept>
#include <string>

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
    void add(E& entity, int id);

    void remove(E& entity);
    void remove_by_id(int id);
    void clear();
    bool has_id(int id);
    E&   get_by_id(int id);

private:
    std::unordered_map<int, E> _entity_map;
};


template <typename E>
void IDGroup<E>::add(E& entity, int id){
    if (_entity_map.count(id))
        throw std::runtime_error("IDGroup<E>::add(E& entity, int id) error: "
            "Creep with id number " + std::to_string(id) + " already exist.");
    Group<E>::add(entity);
    _entity_map.insert(std::make_pair(id, entity));
}


template <typename E>
void IDGroup<E>::remove(E& entity){
    Group<E>::remove(entity);

    int id;
    for (auto& pair : _entity_map){
        if (pair.second == entity){
            _entity_map.erase(pair.first);
            return;
        }
        else
            throw std::runtime_error("IDGroup<E>::remove(E& entity) error: entity does not exist");
    }
}


template <typename E>
void IDGroup<E>::remove_by_id(int id){
    if (_entity_map.count(id)){
        Group<E>::remove(_entity_map[id]);
        _entity_map.erase(id);
    }
    else
        throw std::runtime_error("IDGroup<E>::remove_by_id error: id " + std::to_string(id) + " does not exist.");
}

template <typename E>
bool IDGroup<E>::has_id(int id){
    if (_entity_map.count(id))
        return true;
    return false;
}

template <typename E>
E& IDGroup<E>::get_by_id(int id){
    if (_entity_map.count(id)){
        return _entity_map.at(id);
    }
    else
        throw std::runtime_error("IDGroup<E>::remove_by_id error: id " + std::to_string(id) + " does not exist.");
}

template <typename E>
void IDGroup<E>::clear(){
    Group<E>::clear();
    _entity_map.clear();
}


}//end namespace sol
#endif // SOL_ID_GROUP_HPP_
