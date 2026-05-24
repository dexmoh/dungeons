#include "atoms/objects/object.hpp"

Object::Object(Game& ctx)
    : Atom(ctx, Atom::BaseType::OBJECT)
{
    _name = "Object";
}
