#include "State.hpp"
#include "../../Json/Serialization/Root.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        constexpr char securityConfigField[] = "securityConfig";
        constexpr char ssidField[] = "ssid";
        constexpr char passphraseField[] = "passphrase";
        constexpr char channelField[] = "channel";
        constexpr char ssidHiddenField[] = "ssidHidden";
        constexpr char maxConnectionsField[] = "maxConnections";
        constexpr char ipConfigField[] = "ipConfig";
        constexpr char localIpField[] = "localIp";
        constexpr char gatewayField[] = "gateway";
        constexpr char subnetField[] = "subnet";

        namespace Serialization {
          constexpr Json::Serialization::Field::CStr ssid();
          constexpr Json::Serialization::Field::CStr passphrase();
          constexpr Json::Serialization::Field::Object securityConfig({
            {ssidField, ssid},
            {passphraseField, passphrase}
          });
          constexpr Json::Serialization::Field::Int8 channel();
          constexpr Json::Serialization::Field::CBool ssidHidden();
          constexpr Json::Serialization::Field::Int8 maxConnections();
          constexpr Json::Serialization::Field::IPAddress localIp();
          constexpr Json::Serialization::Field::IPAddress gateway();
          constexpr Json::Serialization::Field::IPAddress subnet();
          constexpr Json::Serialization::Field::Object ipConfig({
            {localIpField, localIp},
            {gatewayField, gateway},
            {subnetField, subnet}
          });
          constexpr Json::Serialization::Field::Object root({
            {securityConfigField, securityConfig},
            {channelField, channel},
            {ssidHiddenField, ssidHidden},
            {maxConnectionsField, maxConnections},
            {ipConfigField, ipConfig}
          });
        }

        constexpr int defaultChannel = 1;
        constexpr int defaultSsidHidden = 0;
        constexpr int defaultMaxConnections = 4;
        constexpr IPConfig * defaultIpConfig = nullptr;

        State::State(
          const char * ssid,
          const char * passphrase,
          const int channel,
          const int ssidHidden,
          const int maxConnections,
          const IPConfig * ipConfig
        ) :
          ssid(ssid),
          hasPassphrase(passphrase != nullptr),
          passphrase(passphrase ? passphrase : ""),
          channel(channel),
          ssidHidden(ssidHidden),
          maxConnections(maxConnections),
          hasIpConfig(ipConfig != nullptr),
          ipConfig(ipConfig ? *ipConfig : IPConfig({0, 0, 0}))
        {}

        State::State(
          const char * defaultSsid,
          const char * defaultPassphrase,
        ) :
          State(
            defaultSsid,
            defaultPassphrase,
            defaultChannel,
            defaultSsidHidden,
            defaultMaxConnections,
            defaultIpConfig,
          )
        {}

        void State::serialize(const JsonVariant & serialized) const {
          Serialization::securityConfig.exists(true);
          Serialization::ssid.set(ssid);
          Serialization::passphrase.set(passphrase);
          Serialization::channel.set(channel),
          Serialization::ssidHidden.set(ssidHidden),
          Serialization::maxConnections.set(maxConnections),
          if (hasIpConfig) {
            Serialization::ipConfig.exists(true);
            Serialization::localIp.get(ipConfig.localIp),
            Serialization::gateway.get(ipConfig.gateway),
            Serialization::subnet.get(ipConfig.subnet)
          } else {
            Serialization::ipConfig.exists(false);
          }
          Serialization::root.serialize(serialized);
        }

        bool Factory::deserialize(const JsonVariant & serialized) {
          BurpStatus::Status::Code statusCode = Serialization::root.deserialize(serialized);
          if (statusCode == Status::ok) {
            const IPConfig ipConfig = {
              Serialization::localIp.get(),
              Serialization::gateway.get(),
              Serialization::subnet.get()
            };
            return ok(new(getAddress()) State(
              Serialization::securityConfig.exists() ? Serialization::ssid.get() : _defaultSsid,
              Serialization::securityConfig.exists() ? Serialization::passphrase.get() : _defaultPassphrase,
              Serialization::channel.get(),
              Serialization::ssidHidden.get(),
              Serialization::maxConnections.get(),
              Serialization::ipConfig.exists() ? &ipConfig : nullptr
            ));
          }
          return fail(statusCode);
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(_defaultSsid, _defaultPassphrase));
          });
        }

        void Factory::setDefaults(const char * defaultSsid, const char * defaultPassphrase) {
          _defaultSsid = defaultSsid;
          _defaultPassphrase = defaultPassphrase;
        }

        #define C_STR_LABEL "BurpDimmer::Config::Network::AccessPoint"
        #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(noObject);
            C_STR_CASE(noTest);
            C_STR_CASE(invalidTest);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
