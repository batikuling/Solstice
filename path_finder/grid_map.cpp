#include <functional>
#include <iostream>
#include <stdexcept>

#include "grid_map.hpp"
#include "../random.hpp"

namespace sol{

GridMap::GridMap(const sf::Vector2i& size) : _size(size){
    for (int x = 0; x < size.x; x++)
        for (int y = 0; y < size.y; y++){
            sf::Vector2i point(x, y);
            _blocked_map[point] = false;
        }
}


void GridMap::set_blocked(const sf::Vector2i& point, bool blocked){
    _blocked_map[point] = blocked;
}


bool GridMap::is_blocked(const sf::Vector2i& point){
    if (point.x > _size.x or point.y > _size.y)
        throw std::runtime_error("GridMap::is_blocked(const sf::Vector2i& point) error: Given point does not exist in the grid map.");
    return _blocked_map[point];
}


int GridMap::get_move_cost(const sf::Vector2i& from, const sf::Vector2i& goal) const{
    sf::Vector2i distance(goal - from);
    if (distance.x == 0 or distance.y == 0)
        return 10;
    else
        return 14;
}

int GridMap::get_heuristics_cost(const sf::Vector2i& from, const sf::Vector2i& goal) const{
    int move_cost = 0;
    int x = from.x;
    int y = from.y;
    int x_movement = x < goal.x ? 1 : -1;
    int y_movement = y < goal.y ? 1 : -1;

    while (x != goal.x){
        move_cost++;
        x += x_movement;
    }

    while (y != goal.y){
        move_cost++;
        y += y_movement;
    }

    return move_cost * 10;
}

bool GridMap::_is_cutting_corner(const sf::Vector2i& point, const sf::Vector2i& movement) {
    if (movement.x == 0 or movement.y == 0)
        return false;

    if (movement == sf::Vector2i(-1, -1)){
        if (_blocked_map[point + sf::Vector2i(-1, 0)] or _blocked_map[point + sf::Vector2i(0, -1)])
            return true;
    }

    else if (movement == sf::Vector2i(1, 1)){
        if (_blocked_map[point + sf::Vector2i(0, 1)] or _blocked_map[point + sf::Vector2i(1, 0)])
            return true;
    }

    else if (movement == sf::Vector2i(1, -1)){
        if (_blocked_map[point + sf::Vector2i(0, -1)] or _blocked_map[point + sf::Vector2i(1, 0)])
            return true;
    }

    else if (movement == sf::Vector2i(-1, 1)){
        if (_blocked_map[point + sf::Vector2i(-1, 0)] or _blocked_map[point + sf::Vector2i(0, 1)])
            return true;
    }

    return false;
}


std::vector<sf::Vector2i> GridMap::get_adjacents(const sf::Vector2i& point) {
    std::vector<sf::Vector2i> adjacents;

    for (int x = -1; x < 2; x++)
        for (int y = -1; y < 2; y++){
            if (x == 0 and y == 0)
                continue;

            sf::Vector2i adjacent_point(point.x + x, point.y + y);
            if (0 <= adjacent_point.x and adjacent_point.x <= _size.x -1 and
                0 <= adjacent_point.y and adjacent_point.y <= _size.y -1 and
                not _blocked_map[adjacent_point]){

                if (not _is_cutting_corner(point, sf::Vector2i(x, y)))
                    adjacents.push_back(adjacent_point);
            }
        }
    shuffle(adjacents.begin(), adjacents.end());
    return std::move(adjacents);
}

} // end namespace sol
