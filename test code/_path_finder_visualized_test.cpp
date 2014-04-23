#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../path_finder.hpp"
#include "../grid_map.hpp"
#include "../utility.hpp"


void clear_path(sf::Vector2i start, sf::Vector2i goal, std::vector<sf::Vector2i>& path, sol::GridMap& gridmap,
                std::vector<std::vector<sf::RectangleShape>>& matrix){
    for (auto& pos : path){
        if (pos == start or pos == goal or gridmap.is_blocked(pos))
            continue;
        matrix[pos.x][pos.y].setFillColor(sf::Color::Black);
    }
}

using namespace std;

int main(void){

    sol::GridMap gridmap(sf::Vector2i(25, 18));
    sol::PathFinder finder([&gridmap](sf::Vector2i& point){return std::move(gridmap.get_adjacents(point));},
                           [&gridmap](sf::Vector2i& from, sf::Vector2i& goal){return gridmap.get_move_cost(from, goal);},
                           [&gridmap](sf::Vector2i& from, sf::Vector2i& goal){return gridmap.get_heuristics_cost(from, goal);});

    sf::IntRect bounds(0, 0, 800, 576);
    sol::WorldGridConverter wg_converter;

    std::vector<std::vector<sf::RectangleShape>> rect_matrix;
    for (int col = 0; col < bounds.left + bounds.width; col += 32){
        std::vector<sf::RectangleShape> line;
        for (int row = 0; row < bounds.top + bounds.height; row += 32){
            sf::RectangleShape rect(sf::Vector2f(32, 32));

            rect.setFillColor(sf::Color::Black);
            rect.setPosition(col, row);
            line.push_back(rect);
        }
        rect_matrix.push_back(line);
    }

    sf::Vector2i start(2, 3);
    sf::Vector2i goal(20, 15);
    std::vector<sf::Vector2i> path;

    rect_matrix[start.x][start.y].setFillColor(sf::Color::Green);
    rect_matrix[goal.x][goal.y].setFillColor(sf::Color::Red);

    sf::RenderWindow window(sf::VideoMode(bounds.width, bounds.height), "Creeps!");
    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;
                sf::Vector2i grid(wg_converter.world_to_grid(sf::Vector2f(mouse_x, mouse_y)));

                if (event.mouseButton.button == sf::Mouse::Right){
                    rect_matrix[goal.x][goal.y].setFillColor(sf::Color::Black);
                    goal.x = grid.x;
                    goal.y = grid.y;
                    rect_matrix[grid.x][grid.y].setFillColor(sf::Color::Red);
                    clear_path(start, goal, path, gridmap, rect_matrix);
                }
                else if (event.mouseButton.button == sf::Mouse::Left){
                    if (gridmap.is_blocked(grid)){
                        gridmap.set_blocked(grid, false);
                        rect_matrix[grid.x][grid.y].setFillColor(sf::Color::Black);
                    }
                    else{
                        gridmap.set_blocked(grid, true);
                        rect_matrix[grid.x][grid.y].setFillColor(sf::Color::Blue);
                    }
                    clear_path(start, goal, path, gridmap, rect_matrix);
                }
                else if (event.mouseButton.button == sf::Mouse::Middle){
                    rect_matrix[start.x][start.y].setFillColor(sf::Color::Black);
                    start.x = grid.x;
                    start.y = grid.y;
                    rect_matrix[start.x][start.y].setFillColor(sf::Color::Green);
                    clear_path(start, goal, path, gridmap, rect_matrix);
                }
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Return){
                    clear_path(start, goal, path, gridmap, rect_matrix);
                    std::cout << "searching path with " << start.x << " " << start.y <<
                    " " << goal.x << " " << goal.y << std::endl;
                    path = finder.find_path(start, goal);
                    for (int i = 0; i < path.size(); i++){
                        if (i == 0 or i == path.size() - 1){
                            std::cout << "skipped first item or last!" << endl;
                            continue;
                        }
                        auto& pos = path[i];
                        rect_matrix[pos.x][pos.y].setFillColor(sf::Color::White);
                    }
                }
            }
        } //end events


        //sf::Time time_passed = clock.restart();

        /*
        for (auto& pos : path){
            if (pos == start or pos == end)
                continue;
            rect_matrix[pos.x][pos.y].setFillColor(sf::Color::Black);
        }
        std::cout << "done erasing prev path" << std::endl;
        std::cout << "searching path" << std::endl;
        path = finder.find_path(start, end);
        std::cout << "found path" << std::endl;
        for (int i = 0; i < path.size(); i++){
            if (i == 0 or i == path.size() - 1)
                continue;
            auto& pos = path[i];
            rect_matrix[pos.x][pos.y].setFillColor(sf::Color::White);
        }
        */


        window.clear();

        for (auto& line : rect_matrix){
            for (auto& rect : line){
                window.draw(rect);
            }
        }
        //window.draw(system);

        window.display();
    } // end main game loop


    return EXIT_SUCCESS;

}
