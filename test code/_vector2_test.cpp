#include <iostream>

#include "../vector2.hpp"

using namespace std;

int main()
{

    sf::Vector2f vec(1, 1);

    cout << "x and y values: " << vec.x << " " << vec.y << endl;
    //cout << "vec.get_length() & vec.get_magnitude(): " << vec.get_length() << " " << vec.get_magnitude() << endl;
    sol::normalize(vec);
    cout << "normalize(vec): " << vec.x << " " << vec.y << endl;


    cout << "resetting values to (1, 1)" << endl;
    vec.x = 1;
    vec.y = 1;
    auto other = sol::get_normalized(vec);
    cout << "get_normalized(vec)'s x and y: " << other.x << " " << other.y << endl;

    cout << "resetting values to (1, 1)" << endl;
    vec.x = 1;
    vec.y = 1;
    cout << "get_angle(vec): " << sol::get_angle(vec) << endl;

    cout << "sol::get_distance(sf::Vector2f(10, 10), sf::Vector2f(20, 10)): " << sol::get_distance(sf::Vector2f(10, 10), sf::Vector2f(20, 10)) << endl;

    cout << "getting directions " << endl << endl;
    sf::Vector2f start(1, 1);
    sf::Vector2f goal(2, 2);

    auto direction = sol::get_normalized(goal - start);
    cout << direction.x << " " << direction.y << endl;

}
