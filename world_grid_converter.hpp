#ifndef _SOLSTICE_WORLD_GRID_CONVERTER_HPP_
#define _SOLSTICE_WORLD_GRID_CONVERTER_HPP_


#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


namespace sol{


/**
*** Grid is a utility class for converting world coordinates to a simple grid.
*** Here, grid is like a small version of the world.
*** The conversion methods will return sf::Vector2<T> but its x and y has no decimal value.
*** sf::Vector2<T> received and returned only for convenience since we usually deal with floats
*** rather than ints.
**/

class WorldGridConverter{
public:

    WorldGridConverter(int x = 32, int y = 32): _tile_size(x, y){}

    template <typename T>
    sf::Vector2<T> world_to_grid(const sf::Vector2<T>& world_position) const;

    template <typename T>
    sf::Vector2<T> world_to_world_topleft(const sf::Vector2<T>& world_position) const;

    template <typename T>
    sf::Vector2<T> grid_to_world_topleft(const sf::Vector2<T>& grid_position) const;

    template <typename T>
    sf::Vector2<T> grid_to_world_center(const sf::Vector2<T>& grid_position) const;

private:
    sf::Vector2i _tile_size;
}; // end class Grid()



template <typename T>
sf::Vector2<T> WorldGridConverter::world_to_grid(const sf::Vector2<T>& world_position) const{
    return sf::Vector2<T>(int(world_position.x) / _tile_size.x, int(world_position.y) / _tile_size.y);
}


template <typename T>
sf::Vector2<T> WorldGridConverter::world_to_world_topleft(const sf::Vector2<T>& world_position) const{
    auto res = world_to_grid(world_position);
    return grid_to_world_topleft(res);
}


template <typename T>
sf::Vector2<T> WorldGridConverter::grid_to_world_topleft(const sf::Vector2<T>& grid_position) const{
    return sf::Vector2<T>(int(grid_position.x) * _tile_size.x, int(grid_position.y) * _tile_size.y);
}


template <typename T>
sf::Vector2<T> WorldGridConverter::grid_to_world_center(const sf::Vector2<T>& grid_position) const{
    auto res = grid_to_world_topleft(grid_position);
    return sf::Vector2<T>(res.x + _tile_size.x / 2, res.y + _tile_size.y / 2);
}

} //  end namespace sol


#endif // _SOLSTICE_WORLD_GRID_CONVERTER_HPP_
