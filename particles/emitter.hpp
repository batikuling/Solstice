#ifndef SOL_EMITTER_HPP
#define SOL_EMITTER_HPP

#include "particle_system.hpp"

namespace sol{

/**
*** This is the base class for emitters.
**/

class Emitter{
public:

    Emitter(ParticleSystem& system) : _system(system) {}
    virtual void update(sf::Time& time_passed) = 0;

protected:
    ParticleSystem& _system;

}; // end class Emitter


} // end namespace sol


#endif // SOL_EMITTER_HPP
