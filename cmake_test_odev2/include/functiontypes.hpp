#ifndef functiontypes_hpp
#define functiontypes_hpp
#include <functional>
namespace graf
{
    using RenderFunction   = std::function<void()>;
    using KeyboardFunction = std::function<void(int, int, int)>;
}

#endif