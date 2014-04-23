#include <iostream>


#include "animation.hpp"


namespace sol{


Animation::Animation(sf::Texture& texture, int cols, int rows, int num_frames,
                     int num_frames_exclude, sf::Time scroll_period, bool infinite):

                     _sprite(texture), _scroll_period(scroll_period), _infinite(infinite){

    auto size = texture.getSize();
    sf::IntRect rect(0, 0, size.x / cols, size.y / rows);

    //deduce the number of frames if not given
    if (num_frames == 0)
        num_frames = cols * rows;

    //create the rects that represent a frame
    _rects.push_back(rect);
    for (int i = 0; i < num_frames - 1; i++){
        if (rect.left == size.x - rect.width){
            rect.top += rect.height;
            rect.left = 0;
        }
        else
            rect.left += rect.width;
        _rects.push_back(rect);
    }

    //for testing the contents of _rects
    //for (auto rect : _rects)
    //    std::cout << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << std::endl;

    for (int i = 0; i < num_frames_exclude; i++)
        _rects.erase(_rects.begin());

    _sprite.setTextureRect(_rects[0]); // always set current texture rect of sprite to first on list on construction

    //auto r = _sprite.getGlobalBounds();
    //auto l = _sprite.getLocalBounds();
    //std::cout << r.left << " " << r.top << " " << r.width << " " << r.height << std::endl;
    //std::cout << l.left << " " << l.top << " " << l.width << " " << l.height << std::endl;

} // end Animation::Animation()


void Animation::update(const sf::Time& time_passed){

    if (_alive){
        _accumulated_time += time_passed;

        if (_accumulated_time >= _scroll_period){
            _current_index++;
            _accumulated_time -= _scroll_period;

            if (_current_index == _rects.size() and not _infinite){
                _alive = 0;
                //_sprite.setTextureRect(_rects[0]);
            }

            else if (_current_index == _rects.size() and _infinite){
                // since reset sets _num_loops to 0, make a reference first
                _num_loops += 1;
                int nloops = _num_loops;
                reset();
                _num_loops = nloops;
            }

            else
                _sprite.setTextureRect(_rects[_current_index]);

        } // end if (_accumulated_time >= _scroll_period)
    } //  end if (alive)
} // end update()


void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (_alive){
        states.transform *= getTransform();
        target.draw(_sprite, states);
    }
} // end draw()

void Animation::reset(){
    _current_index = 0;
    _sprite.setTextureRect(_rects[_current_index]);

    _accumulated_time = sf::Time::Zero;
    _alive = true;
    _num_loops = 0;
} //  end reset()


bool Animation::is_alive(){
    return _alive;
} // end is_alive()


void Animation::set_infinite(bool infinite){
    _infinite = infinite;
} // end set_infinite()


bool Animation::get_infinite(){
    return _infinite;
}

sf::Sprite Animation::get_frame(int index){
    if (index == -1){
        return _sprite;
    }
    else {
        sf::Sprite sprite(*_sprite.getTexture());
        sprite.setTextureRect(_rects[index]);
        return sprite;
    }
} // end get_frame()


int Animation::get_num_loops(){
    return _num_loops;
}

int Animation::get_current_index(){
    return _current_index;
}

int Animation::get_num_frames(){
    return _rects.size();
}


sf::FloatRect Animation::getLocalBounds(){

    auto local = _sprite.getLocalBounds();
    sf::FloatRect rect(0, 0, local.width, local.height);
    return rect;
} // end getLocalBounds()


sf::FloatRect Animation::getGlobalBounds(){

    return getTransform().transformRect(getLocalBounds());
} // end getLocalBounds()

} // end namespace sol
