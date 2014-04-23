#ifndef SOL_ANIMATION_HPP
#define SOL_ANIMATION_HPP

#include <vector>

#include <SFML/Graphics.hpp>


namespace sol{


/**
*** class Animation is a represents an animation from a sprite sheet.
*** You can draw it into render targets and treat it like sf::Sprite.
*** You can also set transform attributes.
**/


class Animation : public sf::Drawable, public sf::Transformable {
public:

    Animation(sf::Texture& texture, int cols, int rows, int num_frames = 0,
              int num_frames_exclude = 0, sf::Time scroll_period = sf::milliseconds(100),
              bool infinite= true);

    void            update(const sf::Time& time_passed);
    void            draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void            reset();

    // always returns true if infinite
    bool            is_alive();
    void            set_infinite(bool infinite);
    bool            get_infinite();

    // returns a sprite set to the given frame; if no argument given, returns current
    // the returned sprite does not have the transforms of the animation
    // also, if the animation is dead and is called without args, it returns the last frame
    sf::Sprite      get_frame(int index = -1);

    // returns the number of loops since client's last call to reset; always 0 if not infinite
    int             get_num_loops();

    // returns current index of rect used in displaying the frame
    int             get_current_index();
    int             get_num_frames();
    sf::FloatRect   getGlobalBounds();
    sf::FloatRect   getLocalBounds();


private:
    sf::Sprite                  _sprite;
    sf::Time                    _scroll_period;
    sf::Time                    _accumulated_time;
    int                         _current_index = 0;
    int                         _num_loops = 0;
    bool                        _infinite;
    bool                        _alive = true;
    std::vector<sf::IntRect>    _rects;
}; // end class Animation



} // end namespace sol


#endif // SOL_ANIMATION_HPP
