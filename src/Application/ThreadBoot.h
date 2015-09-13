/*
   This file is part of The Lost Souls Downfall prototype.

    The Lost Souls Downfall prototype is free software: you can
    redistribute it and/or modify it under the terms of the GNU
    General Public License as published by the Free Software
    Foundation, either version 3 of the License, or (at your option)
    any later version.

    The Lost Souls Downfall prototype is distributed in the hope that
    it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Lost Souls Downfall prototype.  If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef APPLICATION_THREAD_BOOT_H
#define APPLICATION_THREAD_BOOT_H

#include <memory>

#include "../Threading/Thread.h"
#include "BootInterface.h"

namespace Application
{
    class Application;

    /**
     * Interface for objects that boots threads.
     */
    class ThreadBoot: public BootInterface
    {
    public:
        ThreadBoot(Application& application):
            thread_(nullptr),
            application_(application)
        {}

        virtual ~ThreadBoot()
        {
            if (thread_ != nullptr)
            {
                thread_->stop();
                cleanUp();
            }
        }

        Threading::Thread& getThread()
        {
            return *thread_;
        }

        Application& getApplication()
        {
            return application_;
        }

    protected:
        void setThread(Threading::Thread* thread)
        {
            thread_ = std::unique_ptr<Threading::Thread>(thread);
        }

        virtual void cleanUp() {};

    private:
        std::unique_ptr<Threading::Thread> thread_;
        Application& application_;
    };
}

#endif

// Emacs local variables
// Local variables:
// mode: c++
// End:
