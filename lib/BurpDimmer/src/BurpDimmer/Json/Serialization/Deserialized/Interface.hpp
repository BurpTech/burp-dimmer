#pragma once

#include "Field.hpp"

namespace BurpDimmer
{
    namespace Serialization
    {
        namespace Deserialized
        {

            class Interface
            {

            public:

                virtual const Field * get(const size_t index) const = 0;
                virtual void set(const size_t index, const Field * field) const = 0;

            };

        } // namespace Deserialized
        
    } // namespace Serialization
    
} // namespace BurpDimmer
