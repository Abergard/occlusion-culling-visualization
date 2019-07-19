#pragma once
#include <vlCore/Object.hpp>

namespace ocv
{
template <class T, class... Args>
vl::ref<T> make_ref(Args&&... args)
{
    return new T(std::forward<Args>(args)...);
}
}
