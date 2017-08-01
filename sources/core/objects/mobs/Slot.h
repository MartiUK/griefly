#pragma once

#include "representation/ViewInfo.h"

#include "core/Hashes.h"
#include "core/SaveableOperators.h"

namespace kv
{
class Item;

using SlotTypeBase = quint32;

enum class SlotType : SlotTypeBase
{
    DEFAULT = 0,
    SUIT,
    HEAD,
    ANYTHING,
    FEET,
    UNIFORM
};

inline FastSerializer& operator<<(FastSerializer& serializer, const SlotType& slot_type)
{
    serializer << static_cast<SlotTypeBase>(slot_type);
    return serializer;
}

inline FastDeserializer& operator>>(FastDeserializer& deserializer, SlotType& slot_type)
{
    SlotTypeBase chunk;
    deserializer >> chunk;
    slot_type = static_cast<SlotType>(chunk);
    return deserializer;
}

struct Slot
{
    ViewInfo view;
    // TODO (?): append ViewInfo to ViewInfo as layer
    QString overlay_sprite;
    QString overlay_state_postfix;
    IdPtr<Item> item;
    QPair<int, int> position;
    SlotType type;
    QString name;
};

inline bool IsTypeMatch(const Slot& slot, const /*SlotType*/QString& type)
{
    // TODO: return everything back once item type will be made SlotType
    KvAbort("IsTypeMatch: fix me!");
    return false;
    // return slot.type == type;
}

inline FastSerializer& operator<<(FastSerializer& serializer, const Slot& slot)
{
    serializer << slot.view;
    serializer << slot.item;
    serializer << slot.position;
    serializer << slot.type;
    serializer << slot.name;
    return serializer;
}

inline FastDeserializer& operator>>(FastDeserializer& deserializer, Slot& slot)
{
    deserializer >> slot.view;
    deserializer >> slot.item;
    deserializer >> slot.position;
    deserializer >> slot.type;
    deserializer >> slot.name;
    return deserializer;
}

inline unsigned int Hash(const SlotType& slot_type)
{
    return Hash(static_cast<SlotTypeBase>(slot_type));
}

inline unsigned int Hash(const Slot& slot)
{
    unsigned int retval = 0;
    retval += Hash(slot.view);
    retval += Hash(slot.item);
    retval += Hash(slot.position);
    retval += Hash(slot.type);
    retval += Hash(slot.name);
    return retval;
}

}