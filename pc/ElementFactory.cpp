#include "ElementFactory.h"

ElementFactory::ElementFactory()
{
}

ElementFactory::~ElementFactory()
{
    // TODO: Free list.
}

AElement *ElementFactory::createById(int id)
{
    if (this->builderMap.contains(id))
        return this->builderMap[id]->create();
    else
        return NULL;
}
