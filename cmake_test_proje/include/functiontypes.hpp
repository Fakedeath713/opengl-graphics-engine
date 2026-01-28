#ifndef functiontypes_hpp
#define functiontypes_hpp
#include <functional>
namespace graf
{
    using RenderFunction   = std::function<void()>;
    using KeyboardFunction = std::function<void(int, int, int)>;
    using MouseFunction = std::function<void(double, double)>;
}

#endif