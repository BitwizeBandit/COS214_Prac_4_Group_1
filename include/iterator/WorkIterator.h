#ifndef WORKITERATOR_H
#define WORKITERATOR_H

class WorkComponent;

// Iterator participant. Defines how ANY traversal exposes itself to
// client code, regardless of which concrete strategy runs underneath
class WorkIterator 
{
    public:
        virtual ~WorkIterator() {}

        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool isDone() const = 0;
        virtual WorkComponent* currentItem() const = 0;
};

#endif // WORKITERATOR_H
