#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/CStr.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/MacAddress.hpp>
#include <BurpSerialization/IPv4.hpp>
#include <BurpSerialization/Object.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class Serialization : public BurpSerialization::Serialization {

          private:

              using UInt8Scalar = BurpSerialization::Scalar<uint8_t>;
              using MacAddress = BurpSerialization::MacAddress;
              using IPv4 = BurpSerialization::IPv4;

          public:

              struct {
                  bool isNull = false;
                  const char * hostname;
                  const char * ssid;
                  const char * passphrase;
                  UInt8Scalar::Value channel;
                  MacAddress::Value bssid;
                  struct {
                    bool isNull;
                    IPv4::Value localIp;
                    IPv4::Value gateway;
                    IPv4::Value subnet;
                    IPv4::Value dns1;
                    IPv4::Value dns2;
                  } ipConfig;
              } root;

              Serialization();

          private:

              using CStr = BurpSerialization::CStr;
              using Object5 = BurpSerialization::Object<5>;
              using Object6 = BurpSerialization::Object<6>;

              const CStr _hostname;
              const CStr _ssid;
              const CStr _passphrase;
              const UInt8Scalar _channel;
              const MacAddress _bssid;
              const IPv4 _localIp;
              const IPv4 _gateway;
              const IPv4 _subnet;
              const IPv4 _dns1;
              const IPv4 _dns2;
              const Object5 _ipConfig;
              const Object6 _root;

        };

      }
    }
  }
}
