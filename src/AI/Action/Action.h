#ifndef ACTION_H
#define ACTION_H

#include <string>

namespace AI
{
    namespace Action
    {
        /**
         * Base class for actions. Overload it to define custom actions.
         */
        class Action
        {
        public:

            typedef std::string ActionType;

            Action(const ActionType& type) : type_(type){}

            const ActionType& getType() const {return type_;}

            bool isFinished() const {return finished_;}
            void setFinished(bool finished) {finished_ = finished;}

        private:
            ActionType type_;
            bool finished_;
        };
    }
}

#endif // ACTION_H
