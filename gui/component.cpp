
#include "component.hpp"


namespace sol{

namespace gui{

Component::~Component(){}

void Component::set_focus(bool focus){
    _focus = focus;
}

bool Component::has_focus() const{
    return _focus;
}

void Component::set_hover(bool hover){
    _hover = hover;
}

bool Component::has_hover() const{
    return _hover;
}

}
}
