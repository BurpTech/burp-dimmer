#pragma once

#include "Field.hpp"

namespace BurpDimmer
{
    namespace Serialization
    {

        class CStr : public Field
        {

        public:

            struct StatusCodes {
                BurpStatus::Status::Code ok;
                BurpStatus::Status::Code notPresent; // not used if not required
                BurpStatus::Status::Code wrongType;
                BurpStatus::Status::Code tooLong;
            };

            CStr(const size_t length, const bool required, const StatusCodes statusCodes);

            const BurpStatus::Status::Code deserialize(const JsonVariant & serialized) override;
            void serialize(const JsonVariant & serialized) override;
            const char * get();
            void set(const char * value);

        private:

            const char * _value;
            const size_t _length;
            const bool _required;
            const StatusCodes _statusCodes;

        };
        
    } // namespace Serialization
} // namespace BurpDimmer
