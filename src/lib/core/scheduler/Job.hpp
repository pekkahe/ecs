#pragma once

namespace wip
{
    class Job
    {
    public:
        virtual void process() = 0;
        virtual void finish() = 0;
    };

    class Contract
    {
        void readResources();
        void writeResources();
    };
}