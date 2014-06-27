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

#include "RenderEvents.h"

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type RenderMeshFileEvent::Type = "render_mesh_file";
        const Event::Event::Type RenderAnimatedMeshFileEvent::Type = "render_animated_mesh_file";
        const Event::Event::Type RenderModel3DEvent::Type = "render_model_3d";
        const Event::Event::Type RenderCameraEvent::Type = "render_camera";
        const Event::Event::Type CameraRenderedEvent::Type = "camera-rendered";
    }
}
