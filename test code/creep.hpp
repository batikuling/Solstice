#ifndef SOL_CREEP_HPP_
#define SOL_CREEP_HPP_


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "../Group/abstract_entity.hpp"

class Creep : public sol::AbstractEntity {
public:
    int id;

    Creep(sf::Texture& texture, sf::Vector2f pos, sf::IntRect world_bounds, int id, float speed = 120.f);
    ~Creep();
    void update(sf::Time passed);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::FloatRect getGlobalBounds() const;
    sf::Image& get_mask(){ return mask_;}
    const sf::Transform & 	getInverseTransform() {return sprite_.getInverseTransform();}

private:
    sf::Sprite          sprite_;
    sf::Vector2f        direction_;
    sf::IntRect         world_bounds_;
    float               speed_;
    sf::Time            counter_;
    sf::Image           mask_;

    void random_direction();

}; //end class Creep


#endif


