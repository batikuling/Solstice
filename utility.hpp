#ifndef SOL_UTILITY_HPP_
#define SOL_UTILITY_HPP_


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


namespace sol{


/**
*** constant directions
**/

const sf::Vector2f UP(0, -1);
const sf::Vector2f DOWN(0, 1);
const sf::Vector2f LEFT(-1, 0);
const sf::Vector2f RIGHT(1, 0);
const sf::Vector2f UPPER_LEFT(-0.7071067811865475f, -0.7071067811865475f);
const sf::Vector2f UPPER_RIGHT(0.7071067811865475f, -0.7071067811865475f);
const sf::Vector2f LOWER_LEFT(-0.7071067811865475f, 0.7071067811865475f);
const sf::Vector2f LOWER_RIGHT(0.7071067811865475f, 0.7071067811865475f);


const float PI = 3.14159f; //3.14159265358979f;

float radians_to_degrees(const float radians);

float degrees_to_radians(const float degrees);


/**
*** Takes an object and uses it's getLocalBounds() to set its origin
*** to the center
**/

template <typename T>
void center_origin(T& trans){
    auto local = trans.getLocalBounds();
    trans.setOrigin(local.width / 2, local.height / 2);
} // end center_origin()


template <typename T>
sf::Vector2<T> get_rect_center(sf::Rect<T> rect){
    sf::Vector2<T> center;
    center.x = rect.left + rect.width / 2;
    center.y = rect.top + rect.height / 2;
    return center;
}

template <typename T>
sf::Vector2<T> get_vectors_center(sf::Vector2<T> vec1, sf::Vector2<T> vec2){
    sf::Vector2<T> center;
    center.x = (vec1.x + vec2.x) / 2;
    center.y = (vec1.y + vec2.y) / 2;
    return center;
}


} //end namespace sol



namespace std {
  template <> struct hash<sf::Vector2i>{
    size_t operator()(const sf::Vector2i& vector) const{
      return vector.x * 100000 + vector.y;
    }
  };
}


#endif
