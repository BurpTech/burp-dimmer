#pragma once

#include <cstdint>

namespace BurpDimmer
{
    namespace Serialization
    {
        namespace Deserialized
        {

            class Interface;

            union Field
            {
                const char * c_str;
                const bool c_bool;
                const int8_t int8;
                const int16_t int16;
                const int32_t int32;
                const uint8_t uint8;
                const uint16_t uint16;
                const uint32_t uint32;
                const Interface * deserialized;
            };

        } // namespace Deserialized
        
    } // namespace Serialization
    
} // namespace BurpDimmer
