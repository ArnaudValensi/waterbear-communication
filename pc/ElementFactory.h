#ifndef ELEMENTFACTORY_H
#define ELEMENTFACTORY_H

#include <QMap>
#include <QDebug>
#include "AElement.h"
#include "Singleton.hpp"

template<typename Base>
struct IElemBuilder
{
    virtual Base *create() = 0;
};

template<typename Derived, typename Base>
struct ElemBuilder : public IElemBuilder<Base>
{
    ElemBuilder() {}
    Base *create()
    {
        return new Derived();
    }
};

class ElementFactory
{
public:
    ElementFactory();
    ~ElementFactory();

    template <class U>
    void registerElem();
    AElement *createById(int id);

private:
    QMap<int, IElemBuilder<AElement> *> builderMap;
};

template <class U>
void ElementFactory::registerElem()
{
    U elem;
    int id;

    qRegisterMetaType<U*>((elem.getName() + "*").toStdString().c_str());
    id = qMetaTypeId<U*>();

    qDebug() << "Register " << (elem.getName() + "*").toStdString().c_str()
             << " Id: " << id;

    builderMap[id] = new ElemBuilder<U, AElement>();
}

typedef Singleton<ElementFactory> ElementFactorySingleton;

#endif // ELEMENTFACTORY_H
