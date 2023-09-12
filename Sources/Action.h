#pragma once
#include "Delegate.h"

namespace Inking
{
    template<typename ...Args>
    using Action = Delegate<void, Args...>;
}

