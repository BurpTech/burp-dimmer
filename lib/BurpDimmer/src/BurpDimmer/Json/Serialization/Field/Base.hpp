#pragma once

#include <ArduinoJson.h>
#include <BurpStatus.hpp>
#include "../Deserialized/Field.hpp"

namespace BurpDimmer
{
    namespace Serialization
    {
        namespace Field
        {

            class Base
            {

            public:

                virtual void deserialize(
                    const JsonVariant & serialized,
                    const BurpStatus::Status & status
                ) = 0;

                const Deserialized::Field & getField();

            private:

                Deserialized::Field _field;

            };
            
        } // namespace Type
    } // namespace Serialization
} // namespace BurpDimmer
