#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;
typedef int World;
typedef int EventQueue;
namespace Network{
class Synchronizer : public ThreadableInterface
{
    public:
        Synchronizer(World world, EventQueue eventqueue);
        virtual ~Synchronizer();
    protected:
    private:
};
}
#endif // SYNCHRONIZER_H
