#pragma once

#include <array>
#include "Interface.hpp"

namespace BurpDimmer
{
    namespace Serialization
    {
        namespace Deserialized
        {

            template <size_t fieldCount>
            class Instance : public Interface
            {

            public:

                const Field * get(const size_t index) const override
                {
                    return _fields[index];
                }

                void set(const size_t index, const Field * field) override
                {
                    _fields[index] = field;
                }

            private:

                using Fields = std::array<const Field *, fieldCount>;
                Fields _fields;

            };

        } // namespace Deserialized
        
    } // namespace Serialization
    
} // namespace BurpDimmer
