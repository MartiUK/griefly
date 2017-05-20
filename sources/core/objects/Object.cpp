#include "Object.h"
#include "../Map.h"
#include "../ObjectFactory.h"
#include "../Game.h"
#include "representation/Representation.h"

using namespace kv;

void Object::PlayMusic(const QString& name, float volume)
{
    GetGame().PlayMusic(name, volume);
}

void Object::Delete()
{
    GetGame().GetFactory().DeleteLater(id_);
}

void Object::Save(FastSerializer& serializer)
{
    serializer.WriteType(GetType());
    serializer << id_;
    serializer << how_often_;
}

void Object::Load(FastDeserializer& deserializer)
{
    // It is mainly empty because all data is loaded by
    // the outer function

    deserializer >> how_often_;

    SetFreq(GetFreq());
}

void Object::SetFreq(int freq)
{
    if (game_ == nullptr)
    {
        KvAbort("SetFreq is called in constructor");
    }

    how_often_ = freq;

    // TODO: Why is it here?
    if (!GetId())
    {
        KvAbort("GetId() is zero");
    }

    if (how_often_ != 0)
    {
        GetGame().GetFactory().AddProcessingItem(GetId());
    }
}

const GameInterface& Object::GetGame() const
{
    if (game_ == nullptr)
    {
        KvAbort("Object::GetGame() is called during construction of object");
    }
    return *game_;
}

ObjectFactoryInterface& Object::GetFactory()
{
    return GetGame().GetFactory();
}

GameInterface& Object::GetGame()
{
    if (game_ == nullptr)
    {
        KvAbort("Object::GetGame() is called during construction of object");
    }
    return *game_;
}

unsigned int Object::GetRand()
{
    return GetGame().GetRandom().GetRand();
}

quint32 Object::CreateImpl(const QString& type, quint32 owner)
{
    return GetFactory().CreateImpl(type, owner);
}