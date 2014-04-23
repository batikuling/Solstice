#ifndef SOL_COLLISION_HPP
#define SOL_COLLISION_HPP


#include <functional>
#include <iostream>
#include <memory>

#include "group.hpp"


namespace sol{

/**
*** uses the entities getGlobalBounds() method to get a reference to its rectangle representation
*** in the world and checks if the two rects collide
**/

template <typename E, typename S = E>
bool collide_rect(const E& left, const S& right){
    auto left_rect = left->getGlobalBounds();
    auto right_rect = right->getGlobalBounds();

    if (left_rect.intersects(right_rect))
        return true;
    return false;
} // end collide_rect(left right)



/**
*** The author and owner of this code is Ernesto Alejo (https://gist.github.com/ernestoalejo)
*** The interface is revised to fit the convention of this library but I do not claim ownership
***
*** Entity is any type that has methods getGlobalBounds() and getInverseTransform() like sf::Sprite,
*** and get_mask() which returns an const sf::Image& object representing the mask of the entity without
*** any transforms
**/


template <typename Entity, typename Other = Entity>
bool collide_pixel(const Entity& a, const Other& b){

    sf::Image imgA = a->get_mask();
    sf::Image imgB = b->get_mask();

	sf::IntRect boundsA(sf::IntRect(a->getGlobalBounds()));
	sf::IntRect boundsB(sf::IntRect(b->getGlobalBounds()));
	sf::IntRect intersection;

	if(boundsA.intersects(boundsB, intersection)) {
		const sf::Transform& inverseA(a->getInverseTransform());
		const sf::Transform& inverseB(b->getInverseTransform());

		const sf::Vector2u& sizeA(imgA.getSize());
		const sf::Vector2u& sizeB(imgB.getSize());

		const sf::Uint8* pixA = imgA.getPixelsPtr();
		const sf::Uint8* pixB = imgB.getPixelsPtr();

		sf::Vector2f vecA, vecB;
		int xMax = intersection.left + intersection.width;
		int yMax = intersection.top + intersection.height;

		for(int x = intersection.left; x < xMax; x++)
			for(int y = intersection.top; y < yMax; y++) {
				vecA = inverseA.transformPoint(x, y);
				vecB = inverseB.transformPoint(x, y);

				int idxA = ((int) vecA.x + ((int) vecA.y)*sizeA.x)*4 + 3;
				int idxB = ((int) vecB.x + ((int) vecB.y)*sizeB.x)*4 + 3;

				if(vecA.x > 0 && vecA.y > 0 &&
					 vecB.x > 0 && vecB.y > 0 &&
					 vecA.x < sizeA.x && vecA.y < sizeA.y &&
					 vecB.x < sizeB.x && vecB.y < sizeB.y &&
					 pixA[idxA] > 0 &&
					 pixB[idxB] > 0) {
					return true;
				}
			}
	}

	return false;
} // end pixel_collision()


/**
*** There are two typenames since the entity and the entities in the group might not be of the same
*** type, but has the needed interface for th collide function
**/

template <typename E, typename S = E, typename function = std::function<bool(E, S)>>
Group<S> entity_collide(E& entity, Group<S>& group, function collider = collide_rect<E, S>) {
    Group<S> collide_list;

    for (auto& other : group)
        if (collider(entity, other))
            collide_list.add(other);
    return std::move(collide_list);
}

template <typename E, typename S = E, typename function = std::function<bool(E, S)>>
bool entity_collide_any(E& entity, Group<S>& group, function collider = collide_rect<E, S>) {

    for (auto& other : group)
        if (collider(entity, other))
            return true;
    return false;
}


/*
//TODO: re-write that it reaturns like the pygame version. where {entity : collision list from other group}
//TODO: postpone making this since it is not needed as of yet
template <typename E, typename S = E, typename function = std::function<bool(E, S)>>
Group<E> group_collide(Group<E>& group_1, Group<S>& group_2, function collider = collide_rect<E, S>) {
    Group<S> collide_list;

    for (auto& entity_1 : group_1)
        for (auto& entity_2 : group_2)
        if (collider(entity_1, entity_2)){
            collide_list.add(entity_1);
            collide_list.add(entity_2);
        }
    return std::move(collide_list);
}

*/


} // end namespace sol


#endif // SOL_COLLISION_HPP
