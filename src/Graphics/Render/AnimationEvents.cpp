#include "AnimationEvents.h"

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type AnimateEvent::Type = "animate";
        const Event::Event::Type SetupAnimationEvent::Type = "setup_animation";
        const Event::Event::Type UpdateAnimationEvent::Type = "update_animation";
    }
}
