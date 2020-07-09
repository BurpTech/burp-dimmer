#pragma once

#include <array>
#include <BurpDimmer/Json/File/Interface.hpp>
#include "Interface.hpp"

namespace BurpDimmer
{
    namespace Reset
    {

        template <size_t fileCount>
        class Instance : public Interface
        {

        public:

            using Files = std::array<Json::File::Interface *, fileCount>;

            Instance(const Files & toDelete) :
                _toDelete(toDelete)
            {}

            void reboot() const override
            {
                ESP.restart();
            }

            void factoryReset() const override
            {
                for (auto file : _toDelete)
                {
                    file->remove();
                }
                reboot();
            }

        private:

            const Files & _toDelete;

        };

    }
}
