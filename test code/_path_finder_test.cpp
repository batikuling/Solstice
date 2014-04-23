#include <iostream>

#include "../path_finder.hpp"

using namespace std;

int main(void){

    sol::GridMap gridmap(sf::Vector2i(7, 5));
    sol::PathFinder finder([&gridmap](sf::Vector2i& point){return std::move(gridmap.get_adjacents(point));},
                           [&gridmap](sf::Vector2i& from, sf::Vector2i& goal){return gridmap.get_move_cost(from, goal);},
                           [&gridmap](sf::Vector2i& from, sf::Vector2i& goal){return gridmap.get_heuristics_cost(from, goal);});
    /*
    gridmap.set_blocked(sf::Vector2i(3, 1), true);
    gridmap.set_blocked(sf::Vector2i(3, 2), true);
    gridmap.set_blocked(sf::Vector2i(3, 3), true);
    gridmap.set_blocked(sf::Vector2i(3, 0), true);
    gridmap.set_blocked(sf::Vector2i(3, 4), true);
    */

    /*
    auto path = finder.find_path(sf::Vector2i(1, 2), sf::Vector2i(5, 2));

    int cost = 0;
    sf::Vector2i prev;
    for (int i = 0; i < path.size(); i++){
        auto point = path[i];
        cout << point.x << " " << point.y << endl;
        if (i == 0){ // if first item
            prev = point;
            continue;
        }
        cost += gridmap.get_move_cost(prev, point);
        prev = point;
    }
    cout << "total cost is: " << cost << endl << endl;
    if (cost != 40)
        cout << "ERROR" << endl;
    */

    cout << "test what happens if both start and end is the same (1, 1) to (1, 1):" << endl;
    auto path = finder.find_path(sf::Vector2i(1, 1), sf::Vector2i(1, 1));
    for (auto& point : path){
        cout << point.x << " " << point.y << endl;
    }

    cout << "test what happens if start and end has only 1 square in between (1, 1) to (3, 1):" << endl;
    path = finder.find_path(sf::Vector2i(1, 1), sf::Vector2i(3, 1));
    for (auto& point : path){
        cout << point.x << " " << point.y << endl;
    }

}
