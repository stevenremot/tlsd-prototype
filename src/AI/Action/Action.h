#ifndef ACTION_H
#define ACTION_H

#include <string>

namespace AI
{
    namespace Action
    {
        class Action
        {
        public:

            typedef std::string ActionType;

            Action(const ActionType& type) : type_(type){}

            const ActionType& getType() const {return type_;}

        private:
            ActionType type_;
        };
    }
}

#endif // ACTION_H
