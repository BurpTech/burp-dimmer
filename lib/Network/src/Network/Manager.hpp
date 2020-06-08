#pragma once

#include <Redux/Subscriber.hpp>
#include <Config.hpp>

#include "./Normal.hpp"
#include "./AccessPoint.hpp"
#include "./Off.hpp"
#include "./WpsConfig.hpp"

namespace Network {

  class Manager : Redux::Subscriber<Config::State> {

    public:

      void setup();
      void loop();
      void notify(const Config::State * state) override;

    private:

      Normal _normal;
      AccessPoint _accessPoint;
      Off _off;
      WpsConfigMode _wpsConfig;
      const Config::Network::State * _config;

  };
};
