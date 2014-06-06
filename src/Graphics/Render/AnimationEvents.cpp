#include "AnimationEvents.h"

namespace Graphics
{
    namespace Render
    {
        const Event::Event::Type SetupAnimationEvent::TYPE = "setup_animation";
        const Event::Event::Type AnimateEvent::TYPE = "animate";
        const Event::Event::Type UpdateAnimationEvent::TYPE = "update_animation";
    }
}
