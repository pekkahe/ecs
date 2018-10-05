#pragma once

namespace eng
{
    namespace math
    {
        template <typename T>
        void clamp(T& value, const T& min, const T& max)
        {
            if (value < min)
            {
                value = min;
            }
            else if (value > max)
            {
                value = max;
            }
        }
    }
}