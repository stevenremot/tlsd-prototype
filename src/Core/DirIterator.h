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

#ifndef DEF_CORE_DIR_ITERATOR_H
#define DEF_CORE_DIR_ITERATOR_H

#include <iterator>
#include <string>

#include <dirent.h>

#include "File.h"

namespace Core
{
    /**
     * An iterator that returns all file names in a directory.
     */
    class DirIterator
    {
    public:

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

        class InternalIterator: public std::iterator<std::forward_iterator_tag, File>
        {
        public:
            InternalIterator(const std::string& dirName, bool showHiddenFiles);
            InternalIterator();
            InternalIterator(InternalIterator&&);
            ~InternalIterator();

            InternalIterator(const InternalIterator&) = delete;
            InternalIterator& operator=(const InternalIterator&) = delete;

            InternalIterator& operator++();
            bool operator==(const InternalIterator&);
            bool operator!=(const InternalIterator&);
            File operator*();
        private:
            DIR* directory_;
            std::string dirName_;
            struct dirent* currentFile_;
            bool showHiddenFiles_;

            void getNextFile();
        };

        DirIterator(const std::string& dirName, bool showHiddenFiles);
        DirIterator(const std::string& dirName);
        InternalIterator begin() const;
        InternalIterator end() const;

    private:
        const std::string dirName_;
        bool showHiddenFiles_;
    };
}

#endif
