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

#include "DirIterator.h"

namespace Core
{

    //////////////////////////////////////////////////////////////////////
    // Internal iterator /////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    DirIterator::InternalIterator::InternalIterator(
        const std::string& dirName,
        bool showHiddenFiles
    ): showHiddenFiles_(showHiddenFiles)
    {
        directory_ = opendir(dirName.c_str());
        if (directory_ == nullptr)
        {
            throw DirIterator::Error(
                std::string("Could not open directory ") + dirName
            );
        }
        getNextFile();
    }

    DirIterator::InternalIterator::InternalIterator():
        directory_(nullptr),
        currentFile_(nullptr),
        showHiddenFiles_(false)
    {}

    DirIterator::InternalIterator::InternalIterator(DirIterator::InternalIterator::InternalIterator&& other)
    {
        directory_ = other.directory_;
        currentFile_ = other.currentFile_;
        showHiddenFiles_ = other.showHiddenFiles_;
        other.directory_ = nullptr;
        other.currentFile_ = nullptr;
    }

    DirIterator::InternalIterator::~InternalIterator()
    {
        if (directory_ != nullptr)
        {
            closedir(directory_);
        }
    }

    DirIterator::InternalIterator& DirIterator::InternalIterator::operator++()
    {
        getNextFile();
        return *this;
    }

    bool DirIterator::InternalIterator::operator==(const DirIterator::InternalIterator& other) {
        return currentFile_ == other.currentFile_;
    }

    bool DirIterator::InternalIterator::operator!=(const DirIterator::InternalIterator& other) {
        return currentFile_ != other.currentFile_;
    }

    std::string DirIterator::InternalIterator::operator*()
    {
        return currentFile_->d_name;
    }

    void DirIterator::InternalIterator::getNextFile()
    {
        currentFile_ = readdir(directory_);
        if (!showHiddenFiles_ && currentFile_ != nullptr
            && currentFile_->d_name[0] == '.')
        {
            getNextFile();
        }
    }

    //////////////////////////////////////////////////////////////////////
    // Directory iterator ////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////


    DirIterator::DirIterator(const std::string& dirName, bool showHiddenFiles):
        dirName_(dirName),
        showHiddenFiles_(showHiddenFiles)
    {}


    DirIterator::DirIterator(const std::string& dirName):
        DirIterator(dirName, false)
    {}

    DirIterator::InternalIterator DirIterator::begin() const
    {
        return InternalIterator(dirName_, showHiddenFiles_);
    }

    DirIterator::InternalIterator DirIterator::end() const
    {
        return InternalIterator();
    }
}
