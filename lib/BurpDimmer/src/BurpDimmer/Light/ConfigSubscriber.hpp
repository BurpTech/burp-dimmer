#pragma once

#include <BurpRedux/Subscriber/Interface.hpp>
#include "../Config/Light/State.hpp"
#include "Store.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {

    class ConfigSubscriber : public BurpRedux::Subscriber::Interface<Config> {

      public:

        ConfigSubscriber(Store::Interface & store);
        void setup(const Config * config) override;
        void onPublish(const Config * config) override;

      private:

        Store::Interface & _store;

    };

  }
}
