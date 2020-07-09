#pragma once

namespace BurpDimmer
{
    namespace Reset
    {

        class Interface
        {

        public:

            virtual void reboot() const = 0;
            virtual void factoryReset() const = 0;

        };

    }
}
