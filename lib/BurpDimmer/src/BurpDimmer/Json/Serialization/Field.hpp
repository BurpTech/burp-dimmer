#pragma once

#include <ArduinoJson.h>
#include <BurpStatus.hpp>

namespace BurpDimmer
{
    namespace Serialization
    {
        class Field
        {

        public:

            virtual const BurpStatus::Status::Code deserialize(const JsonVariant & serialized) = 0;
            virtual void serialize(const JsonVariant & serialized) = 0;

        };
        
    } // namespace Serialization
} // namespace BurpDimmer
