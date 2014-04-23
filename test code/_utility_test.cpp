#include <iostream>

#include "../utility.hpp"

using namespace std;

int main(void){

    cout << "start test for centering rect and 2 vectors" << endl;
    sf::IntRect rect(50, 50, 50, 50);
    sf::Vector2f one(0, 0);
    sf::Vector2f two(80, 50);

    auto rect_center = sol::get_rect_center(rect);
    cout << "calling sol::get_rect_center(50, 50, 50, 50): " << rect_center.x
    <<" " << rect_center.y << endl;

    auto vector_center = sol::get_vectors_center(one, two);
    cout << "calling sol::get_vectors_center((0, 0), (80, 50)): " << vector_center.x
    << " " << vector_center.y << endl;

    cout << "end test for centering rect and 2 vectors" << endl;


    cout << endl << "test direction constants: UP" << endl;
    cout << sol::UP.x << " " << sol::UP.y << endl;

} // end main()
