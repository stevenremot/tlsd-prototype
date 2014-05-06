#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <string>

namespace Ecs
{
    class Component
    {
    public:
        typedef std::string Type;

        Component(Type type): type_(type)
        {}

        virtual ~Component()
        {}

        const Type & getType() const
        {
            return type_;
        }

        // virtual std::string serialize() const;

    private:
        Type type_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
