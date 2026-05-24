#include "atoms/terrains/terrain.hpp"

Terrain::Terrain(Game& ctx)
    : Atom(ctx, Atom::BaseType::TERRAIN)
{
    _name = "Terrain";
}
