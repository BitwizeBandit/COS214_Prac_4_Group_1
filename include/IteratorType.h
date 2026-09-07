#ifndef ITERATORTYPE_H
#define ITERATORTYPE_H

// Selects which traversal strategy ProductionUnit::createIterator()
// should hand back.
enum class IteratorType {
    FULL_TRAVERSAL,
    VFX_PENDING
};

#endif // ITERATORTYPE_H
