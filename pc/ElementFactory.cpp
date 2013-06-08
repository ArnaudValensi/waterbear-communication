#include "ElementFactory.h"

ElementFactory::ElementFactory()
{
}

AElement *ElementFactory::createById(int id)
{
    if (this->builderMap.contains(id))
        return this->builderMap[id]->create();
    else
        return NULL;
}
