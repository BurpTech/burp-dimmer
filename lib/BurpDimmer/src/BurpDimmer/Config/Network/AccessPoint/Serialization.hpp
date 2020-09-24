#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/CStr.hpp>
#include <BurpSerialization/IPv4.hpp>
#include <BurpSerialization/Object.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class Serialization : public BurpSerialization::Serialization {

          private:

              using UInt8Scalar = BurpSerialization::Scalar<uint8_t>;
              using BoolScalar = BurpSerialization::Scalar<bool>;
              using IPv4 = BurpSerialization::IPv4;

          public:

              struct {
                  bool isNull = false;
                  struct {
                    bool isNull = false;
                    const char * ssid;
                    const char * passphrase;
                  } securityConfig;
                  UInt8Scalar::Value channel;
                  BoolScalar::Value ssidHidden;
                  UInt8Scalar::Value maxConnections;
                  struct {
                    bool isNull = false;
                    IPv4::Value localIp;
                    IPv4::Value gateway;
                    IPv4::Value subnet;
                  } ipConfig;
              } root;

              Serialization();

          private:

              using Object2 = BurpSerialization::Object<2>;
              using Object3 = BurpSerialization::Object<3>;
              using Object5 = BurpSerialization::Object<5>;
              using CStr = BurpSerialization::CStr;

              const CStr _ssid;
              const CStr _passphrase;
              const Object2 _securityConfig;
              const UInt8Scalar _channel;
              const BoolScalar _ssidHidden;
              const UInt8Scalar _maxConnections;
              const IPv4 _localIp;
              const IPv4 _gateway;
              const IPv4 _subnet;
              const Object3 _ipConfig;
              const Object5 _root;

        };

      }
    }
  }
}
