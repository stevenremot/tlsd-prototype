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

#include <iostream>

#include "Interpreter.h"

namespace Lua
{
    Interpreter::Interpreter(Vm& vm):
        thread_(vm.createThread()),
        running_(true)
    {}

    void Interpreter::run()
    {
        if (running_)
        {
            std::cout << ">> ";
            if (!std::cin.eof())
            {
                char command[256];
                std::cin.getline(command, sizeof(command));

                try
                {
                    thread_->doString(command);
                }
                catch(const Lua::Thread::CodeError& e)
                {
                    std::cout << "Error : " << e.what() << std::endl;
                }
            }
            else
            {
                running_ = false;
            }
        }
    }
}
