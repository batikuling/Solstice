#include <iostream>

#include "../grid_map.hpp"

using namespace std;

int main(void){
    cout << boolalpha;

    sol::GridMap gridmap(sf::Vector2i(20, 20));

    cout << gridmap.is_blocked(sf::Vector2i(6, 6)) << endl;
    gridmap.set_blocked(sf::Vector2i(6, 6), true);
    cout << gridmap.is_blocked(sf::Vector2i(6, 6)) << endl;

    cout << "cost of moving to lower left: " << gridmap.get_move_cost(sf::Vector2i(2, 2), sf::Vector2i(3, 3)) << endl;
    cout << "cost of moving to the right: " << gridmap.get_move_cost(sf::Vector2i(2, 2), sf::Vector2i(3, 2)) << endl;
    cout << "heuristic cost of moving from (1, 1) to (5, 5): " << gridmap.get_heuristics_cost(sf::Vector2i(1, 1), sf::Vector2i(5, 5)) << endl;
    cout << endl;

    // test what happens if vector is at 0, 0
    auto adjacents = gridmap.get_adjacents(sf::Vector2i(0, 0));
    for (auto& point : adjacents)
        cout << point.x << " " << point.y << endl;
    cout << endl;

    // test what happens if vector is at 19, 19
    adjacents = gridmap.get_adjacents(sf::Vector2i(19, 19));
    for (auto& point : adjacents)
        cout << point.x << " " << point.y << endl;
    cout << endl;

    gridmap.set_blocked(sf::Vector2i(2, 1), true);
    gridmap.set_blocked(sf::Vector2i(2, 2), true);
    gridmap.set_blocked(sf::Vector2i(2, 3), true);

    adjacents = gridmap.get_adjacents(sf::Vector2i(0, 2));
    for (auto& point : adjacents)
        cout << point.x << " " << point.y << endl;
    cout << endl;
}
