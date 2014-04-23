#include <iostream>
#include <cstdlib>

#include "../vector2.hpp"
#include "creep.hpp"

Creep::Creep(sf::Texture& texture, sf::Vector2f pos, sf::IntRect world_bounds, int i, float speed /* = 120.f */):
    sprite_(texture), world_bounds_(world_bounds), id(i), speed_(speed){

    sprite_.setPosition(pos);
    random_direction();
    auto local = sprite_.getLocalBounds();
    sprite_.setOrigin(sf::Vector2f(local.width/2.f, local.height/2.f));

    mask_ = texture.copyToImage();

}//end constructor

Creep::~Creep(){
    std::cout << "ID number " << id << " is dead" <<std::endl;
}

void Creep::update(sf::Time passed){
    counter_ += passed;

    if (counter_.asSeconds() > rand() % 3 + 2){
        random_direction();
        counter_ = sf::Time::Zero;
    }

    sf::Vector2f movement(0.f, 0.f);
    movement.x = passed.asSeconds() * speed_ * direction_.x;
    movement.y = passed.asSeconds() * speed_ * direction_.y;
    sprite_.move(movement);

    //cout << "movement: " << movement.x << " " << movement.y << endl;

    auto local_rect = sprite_.getLocalBounds();
    auto rect = sprite_.getGlobalBounds();
    auto pos = sprite_.getPosition();

    //std::cout << "global: " << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << std::endl;
    //std::cout << "local: " <<local_rect.left << " " << local_rect.top << " " << local_rect.width << " " << local_rect.height << std::endl;

    if (rect.left < 0){
        sprite_.setPosition(rect.width / 2, pos.y);
        direction_.x *= -1;
    }
    else if (rect.left > world_bounds_.width - local_rect.width){
        sprite_.setPosition(world_bounds_.width - local_rect.width / 2, pos.y);
        direction_.x *= -1;
    }
    else if (rect.top < 0){
        sprite_.setPosition(pos.x, rect.height / 2);
        direction_.y *= -1;
    }
    else if (rect.top > world_bounds_.height - local_rect.height){
        sprite_.setPosition(pos.x, world_bounds_.height - local_rect.height / 2);
        direction_.y *= -1;
    }

    sprite_.setRotation(sol::get_angle(direction_));

    //cout << pos.x << " " << rect.left  << " " << pos.y << " " << rect.top << endl;
}//end update()

void Creep::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite_, states);
}// end draw()



void Creep::random_direction(){
    direction_.x = rand() % 3 - 1;
    direction_.y = rand() % 3 - 1;
    if (direction_.x == 0 and direction_.y == 0){
        direction_.x = 1;
    }
    sol::normalize(direction_);

}


sf::FloatRect Creep::getGlobalBounds() const{
    return sprite_.getGlobalBounds();
}
