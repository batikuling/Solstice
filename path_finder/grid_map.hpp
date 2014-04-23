#ifndef SOL_GRID_MAP_HPP
#define SOL_GRID_MAP_HPP


#include <unordered_map>

#include <SFML/System.hpp>

#include "../random.hpp"
#include "../utility.hpp"


namespace sol{

class GridMap{
public:
    GridMap(const sf::Vector2i& size);
    void set_blocked(const sf::Vector2i& point, bool blocked);
    bool is_blocked(const sf::Vector2i& point);
    int get_move_cost(const sf::Vector2i& from, const sf::Vector2i& goal) const;
    int get_heuristics_cost(const sf::Vector2i& from, const sf::Vector2i& goal) const;
    std::vector<sf::Vector2i> get_adjacents(const sf::Vector2i& point);

private:
    std::unordered_map<sf::Vector2i, bool> _blocked_map;
    sf::Vector2i _size; // the number of rows and columns denoted by x and y

    bool _is_cutting_corner(const sf::Vector2i& point, const sf::Vector2i& movement);
};

} // end namespace sol

#endif // SOL_GRID_MAP_HPP
