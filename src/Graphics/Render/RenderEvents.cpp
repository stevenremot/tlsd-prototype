#include "RenderEvents.h"

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type RenderMeshFileEvent::Type = "render_mesh_file";
        const Event::Event::Type RenderAnimatedMeshFileEvent::Type = "render_animated_mesh_file";
        const Event::Event::Type RenderModel3DEvent::Type = "render_model_3d";
        const Event::Event::Type RenderCameraEvent::Type = "render_camera";
    }
}
