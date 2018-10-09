#pragma once

namespace trait
{
    class non_copyable
    {
    protected:
        non_copyable() = default;
        ~non_copyable() = default;

        non_copyable(const non_copyable&) = delete;
        non_copyable& operator=(const non_copyable&) = delete;
        non_copyable(non_copyable&&) = default;
        non_copyable& operator=(non_copyable&&) = default;
    };

    class non_copyable_nor_movable
    {
    protected:
        non_copyable_nor_movable() = default;
        ~non_copyable_nor_movable() = default;

        non_copyable_nor_movable(const non_copyable_nor_movable&) = delete;
        non_copyable_nor_movable& operator=(const non_copyable_nor_movable&) = delete;
        non_copyable_nor_movable(non_copyable_nor_movable&&) = delete;
        non_copyable_nor_movable& operator=(non_copyable_nor_movable&&) = delete;
    };
}