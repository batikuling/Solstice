#ifndef SOL_ENTITY_HPP_
#define SOL_ENTITY_HPP_


#include <unordered_set>
#include <memory>


namespace sol{


/**
*** class AbstractEntity is a baseclass for an entity that cannot be copied, is drawable and has
*** methods like update and draw
**/

class AbstractEntity : public sf::Drawable, public sf::NonCopyable{
public:
    virtual void update(sf::Time time_passed) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};



}//end namespace sol


#endif
