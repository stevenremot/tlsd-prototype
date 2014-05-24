#ifndef SYNCHROAPPLIER_H
#define SYNCHROAPPLIER_H

#include "../Threading/Channel.h"
#include "../Threading/Thread.h"
using Threading::ThreadableInterface;


typedef int World;
typedef int EventQueue;
namespace Network{
class SynchroApplier : public ThreadableInterface
{
    public:
        SynchroApplier(World world, EventQueue eventqueue);
        virtual ~SynchroApplier();

    protected:
    private:
};
}
#endif // SYNCHROAPPLIER_H
