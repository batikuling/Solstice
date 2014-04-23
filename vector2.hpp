#ifndef SOL_VECTOR2_HPP_
#define SOL_VECTOR2_HPP_

#include <cmath>

#include <SFML/System.hpp>

#include "utility.hpp"


namespace sol{

template<typename Type>
Type get_length(const sf::Vector2<Type>& vec){
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}


template<typename Type>
Type get_magnitude(const sf::Vector2<Type>& vec){
    return get_length(vec);
}


template<typename Type>
void normalize(sf::Vector2<Type>& vec){

    Type magnitude = get_magnitude(vec);
    if (magnitude == 0){
        vec.x = 0;
        vec.y = 0;
        return;
    }
    vec.x /= magnitude;
    vec.y /= magnitude;
}


template<typename Type>
sf::Vector2<Type> get_normalized(const sf::Vector2<Type>& vec){
    sf::Vector2<Type> result(vec.x, vec.y);
    normalize(result);
    return result;
}


template<typename Type>
Type get_distance(const sf::Vector2<Type>& from, const sf::Vector2<Type>& to){

    Type dx, dy;
    dx = to.x - from.x;
    dy = to.y - from.y;

    return sqrt(dx * dx + dy * dy);
}


//Vec2d.get_angle() returns angle of x and y in degrees
template<typename Type>
Type get_angle(const sf::Vector2<Type>& vec){

    Type length_squared = vec.x * vec.x + vec.y * vec.y;
    if (length_squared == 0)
        return 0;
    Type radians = std::atan2(vec.y, vec.x);
    auto angle = radians_to_degrees(radians);

    //normalize angle
    if (angle < 0.f)
        angle += 360.f;

    return angle;
}


template<typename Type>
void rotate(sf::Vector2<Type>& vec, const Type angle_degrees){

    auto radians = degrees_to_radians(angle_degrees);
    auto cs = std::cos(radians);
    auto sn = std::sin(radians);
    float x = vec.x * cs - vec.y * sn;
    float y = vec.x * sn + vec.y * cs;

    vec.x = x;
    vec.y = y;
}


}// end namespace sol


#endif
