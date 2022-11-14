#pragma once

namespace sche
{
    class Job
    {
    public:
        virtual void process() = 0;
        virtual void finish() = 0;
    };
}