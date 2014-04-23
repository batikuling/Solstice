#include <iostream>

#include "../world_grid_converter.hpp"


using namespace std;

int main(void){
    cout << "start test for class WorldGridConverter" << endl;
    sf::Vector2f sprite_pos(80, 100);
    sf::Vector2f sprite_grid(2, 3);
    sol::WorldGridConverter grid;

    auto res = grid.world_to_grid(sprite_pos);
    cout << "world_to_grid(80, 100) : " << res.x << " " << res.y << endl;

    res = grid.world_to_world_topleft(sprite_pos);
    cout << "world_to_world_topleft(80, 100) : " << res.x << " " << res.y << endl;

    res = grid.grid_to_world_center(sprite_grid);
    cout << "grid_to_world_center(2, 3) : " << res.x << " " << res.y << endl;

    res = grid.grid_to_world_topleft(sprite_grid);
    cout << "grid_to_world_topleft(2, 3) : " << res.x << " " << res.y << endl;
    cout << "end test for class Grid" << endl << endl;


}
