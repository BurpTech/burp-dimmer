#include "Status.hpp"
#include "Serialization.hpp"
#include "../Constants.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        constexpr char hostnameField[] = "hostname";
        constexpr char ssidField[] = "ssid";
        constexpr char passphraseField[] = "passphrase";
        constexpr char channelField[] = "channel";
        constexpr char bssidField[] = "bssid";
        constexpr char ipConfigField[] = "ipConfig";
        constexpr char localIpField[] = "localIp";
        constexpr char gatewayField[] = "gateway";
        constexpr char subnetField[] = "subnet";
        constexpr char dns1Field[] = "dns1";
        constexpr char dns2Field[] = "dns2";

        Serialization::Serialization() :
          BurpSerialization::Serialization(_root),
          _hostname(0, MAX_HOSTNAME_LENGTH, {
            Status::ok,
            Status::ok, // hostname optional
            Status::invalidHostname,
            Status::ok, // min length is 0 so can't get too short error
            Status::hostnameTooLong
          }, root.hostname),
          _ssid(0, MAX_SSID_LENGTH, {
            Status::ok,
            Status::missingSsid,
            Status::invalidSsid,
            Status::ok, // min length is 0 so can't get too short error
            Status::ssidTooLong
          }, root.ssid),
          _passphrase(MIN_PASSPHRASE_LENGTH, MAX_PASSPHRASE_LENGTH, {
            Status::ok,
            Status::ok, // passphrase optional
            Status::invalidPassphrase,
            Status::passphraseTooShort,
            Status::passphraseTooLong
          }, root.passphrase),
          _channel({
            Status::ok,
            Status::ok, // channel optional
            Status::invalidChannel
          }, root.channel),
          _bssid({
            Status::ok,
            Status::ok, // bssid optional
            Status::invalidBssid,
            Status::invalidBssid,
            Status::invalidBssid,
            Status::invalidBssid,
            Status::invalidBssid,
            Status::invalidBssid
          }, root.bssid),
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
          _dns1({
            Status::ok,
            Status::ok, // dns1 optional
            Status::invalidDns1,
            Status::invalidDns1,
            Status::invalidDns1,
            Status::invalidDns1,
            Status::invalidDns1,
          }, root.ipConfig.dns1),
          _dns2({
            Status::ok,
            Status::ok, // dns2 optional
            Status::invalidDns2,
            Status::invalidDns2,
            Status::invalidDns2,
            Status::invalidDns2,
            Status::invalidDns2,
          }, root.ipConfig.dns2),
          _ipConfig({
            Object5::Entry({localIpField, &_localIp}),
            Object5::Entry({gatewayField, &_gateway}),
            Object5::Entry({subnetField, &_subnet}),
            Object5::Entry({dns1Field, &_dns1}),
            Object5::Entry({dns2Field, &_dns2}),
          }, {
            Status::ok,
            Status::ok, // IP config optional
            Status::invalidIpConfig
          }, root.ipConfig.isNull),
          _root({
            Object6::Entry({hostnameField, &_hostname}),
            Object6::Entry({ssidField, &_ssid}),
            Object6::Entry({passphraseField, &_passphrase}),
            Object6::Entry({channelField, &_channel}),
            Object6::Entry({bssidField, &_bssid}),
            Object6::Entry({ipConfigField, &_ipConfig})
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
