#ifndef SOL_PATH_FINDER_HPP
#define SOL_PATH_FINDER_HPP


#include <functional>
#include <unordered_map>
#include <memory>

#include <SFML/System.hpp>

namespace sol{

class _Node{
public:
    using Ptr = std::shared_ptr<_Node>;
    sf::Vector2i    coord;
    Ptr             parent = nullptr;
    int             g_cost = 0;
    int             f_cost = 0;

    _Node(sf::Vector2i c) : coord(c){}
    bool operator==(const _Node& other) const ;
    bool operator<(const _Node& other) const ;
    bool operator>(const _Node& other) const ;
};


class PathFinder{
public:
    PathFinder(std::function<std::vector<sf::Vector2i>(sf::Vector2i&)> get_neighbors,
        std::function<int(sf::Vector2i&, sf::Vector2i&)> get_move_cost,
        std::function<int(sf::Vector2i&, sf::Vector2i&)> get_heuristics_cost):
        _get_neighbors(get_neighbors),
        _get_move_cost(get_move_cost),
        _get_heuristics_cost(get_heuristics_cost){}

    std::vector<sf::Vector2i> find_path(const sf::Vector2i& start, const sf::Vector2i& goal);


private:
    std::function<std::vector<sf::Vector2i>(sf::Vector2i&)>  _get_neighbors;
    std::function<int(sf::Vector2i&, sf::Vector2i&)>          _get_move_cost;
    std::function<int(sf::Vector2i&, sf::Vector2i&)>          _get_heuristics_cost;
    //std::vector<sf::Vector2i> _reconstruct_path(_Node& end_node);

    int _compute_g_cost(_Node& from, _Node& to) const;
    int _compute_f_cost(_Node& from, _Node& to) const;
};


} // end namespace sol



namespace std {
  template <> struct hash<sol::_Node>{
    size_t operator()(const sol::_Node& node) const{
      return node.coord.x * 100000 + node.coord.y;
    }
  };


  template <> struct hash<std::shared_ptr<sol::_Node>>{
    size_t operator()(const std::shared_ptr<sol::_Node>& vector) const{
      return vector->coord.x * 100000 + vector->coord.y;
    }
  };

  template <> struct greater<std::shared_ptr<sol::_Node>>{
    bool operator()(const std::shared_ptr<sol::_Node>& left, const std::shared_ptr<sol::_Node>& right) const{
      return *left > *right;
    }
  };
}


template <typename T>
class equal_shared_ptr{
public:
bool operator()(const std::shared_ptr<T>& left, const std::shared_ptr<T>& right) const{
  return *left == *right;
}
};


#endif // SOL_PATH_FINDER_HPP
