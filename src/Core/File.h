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

#ifndef DEF_CORE_FILE_H
#define DEF_CORE_FILE_H

#include <string>
#include <sys/stat.h>

namespace Core
{
    class File
    {
    public:
        File(const std::string& name):
            name_(name)
        {}

        inline const std::string& getName() const
        {
            return name_;
        }

        inline bool exists() const
        {
            struct stat buffer;
            return stat(name_.c_str(), &buffer) == 0;
        }

        static std::string joinPaths(const std::string& dir, const std::string& relativePath);
    private:
        std::string name_;
    };
}

#endif
