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

#ifndef DEF_CORE_ERROR_H
#define DEF_CORE_ERROR_H

#include <exception>
#include <string>

namespace Core
{
    class Error: public std::exception
    {
    public:
        Error(const std::string& errorMsg):
            errorMsg_(errorMsg)
        {}

        virtual const char* what() const noexcept
        {
            return errorMsg_.c_str();
        }
    private:
        std::string errorMsg_;
    };
}

#endif
