#include "SpaceTurf.h"

#include "../SyncRandom.h"

#include "Item.h"
#include "Materials.h"
#include "Lattice.h"
#include "../ObjectFactory.h"
#include "../Game.h"

Space::Space(size_t id) : ITurf(id)
{
    SetAtmosState(SPACE);

    SetPassable(D_ALL, Passable::FULL);
    transparent = true;
    
    SetFriction(0);

    SetSprite("icons/space.png"); 
    SetState("10");
    name = "Space";
}

void Space::AfterWorldCreation()
{
    std::stringstream conv;
    size_t value = GetRand() % 25 + 1;
    conv << value;
    SetState(conv.str());
}

void Space::AttackBy(IdPtr<Item> item)
{
    if (IdPtr<Rod> rod = item)
    {
        rod->Delete();
        Create<IOnMapObject>(Lattice::T_ITEM_S(), GetOwner());
    }
}
