#ifndef ENTITY_COMPONENT
#define ENTITY_COMPONENT

#include "pch.h"

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

#if DEBUG
const Entity MAX_ENTITIES = 10;         // Used to define the size of arrays
const ComponentType MAX_COMPONENTS = 5; // Used to define the size of arrays

#else
const Entity MAX_ENTITIES = 5000;        // Used to define the size of arrays
const ComponentType MAX_COMPONENTS = 32; // Used to define the size of arrays
#endif

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // ENTITY_COMPONENT
