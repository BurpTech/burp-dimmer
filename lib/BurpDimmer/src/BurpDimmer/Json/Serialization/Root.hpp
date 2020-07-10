#pragma once

#include <array>
#include <functional>
#include "Field/Base.hpp"

namespace BurpDimmer
{
    namespace Json
    {
        namespace Serialization
        {
            class Root
            {

            public:

                
                using f_create = std::function<bool (const BurpStatus::Status & status, const Deserialized::Field & deserialized)>;

                Root(const Field::Base & root) :
                    _root(root)
                {}

                bool deserialize(const JsonVariant & serialized, f_create create) const
                {
                    BurpStatus::Status status;
                    _root.deserialize(serialized, status);
                    return create(status, _root.getField());
                }

            private:

                const Field::Base & _root;

            };
        
        }
    }
}
