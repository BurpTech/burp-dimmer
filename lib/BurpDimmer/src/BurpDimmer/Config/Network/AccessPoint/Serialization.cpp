#include <ESP8266WiFi.h>
#include "Status.hpp"
#include "Serialization.hpp"

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

        Serialization::Serialization() :
          BurpSerialization::Serialization(_root),
          _ssid(WL_SSID_MAX_LENGTH, {
            Status::ok,
            Status::missingSsid,
            Status::invalidSsid,
            Status::ssidTooLong
          }, root.securityConfig.ssid),
          _passphrase(WL_WPA_KEY_MAX_LENGTH, {
            Status::ok,
            Status::ok, // passphrase optional
            Status::invalidPassphrase,
            Status::passphraseTooLong
          }, root.securityConfig.passphrase),
          _securityConfig({
            Object2::Entry({ssidField, &_ssid}),
            Object2::Entry({passphraseField, &_passphrase})
          }, {
            Status::ok,
            Status::ok, // security config optional (will use factory default if missing)
            Status::invalidSecurityConfig
          }, root.securityConfig.isNull),
          _channel({
            Status::ok,
            Status::ok, // channel optional
            Status::invalidChannel
          }, root.channel),
          _ssidHidden({
            Status::ok,
            Status::ok, // ssid hidden flag optional
            Status::invalidSsidHidden
          }, root.ssidHidden),
          _maxConnections({
            Status::ok,
            Status::ok, // max connections optional
            Status::invalidMaxConnections
          }, root.maxConnections),
          _localIp({
            Status::ok,
            Status::missingLocalIp,
            Status::invalidLocalIp,
            Status::invalidLocalIp,
            Status::invalidLocalIp,
            Status::invalidLocalIp,
            Status::invalidLocalIp
          }, root.ipConfig.localIp),
          _gateway({
            Status::ok,
            Status::missingGateway,
            Status::invalidGateway,
            Status::invalidGateway,
            Status::invalidGateway,
            Status::invalidGateway,
            Status::invalidGateway
          }, root.ipConfig.gateway),
          _subnet({
            Status::ok,
            Status::missingSubnet,
            Status::invalidSubnet,
            Status::invalidSubnet,
            Status::invalidSubnet,
            Status::invalidSubnet,
            Status::invalidSubnet
          }, root.ipConfig.subnet),
          _ipConfig({
            Object3::Entry({localIpField, &_localIp}),
            Object3::Entry({gatewayField, &_gateway}),
            Object3::Entry({subnetField, &_subnet})
          }, {
            Status::ok,
            Status::ok, // IP config optional
            Status::invalidIpConfig
          }, root.ipConfig.isNull),
          _root({
            Object5::Entry({securityConfigField, &_securityConfig}),
            Object5::Entry({channelField, &_channel}),
            Object5::Entry({ssidHiddenField, &_ssidHidden}),
            Object5::Entry({maxConnectionsField, &_maxConnections}),
            Object5::Entry({ipConfigField, &_ipConfig})
          }, {
            Status::ok,
            Status::noObject,
            Status::invalidConfig
          }, root.isNull)
        {}

      }
    }
  }
}
