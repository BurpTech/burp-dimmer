#include "Config/Deserialize.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Config {

    Store store;
    Light::Selector lightSelector(store, [](const State * state) {
        return state->light;
    });
    Network::Selector networkSelector(store, [](const State * state) {
        return state->network;
    });
    Network::AccessPoint::Selector networkAccessPointSelector(networkSelector, [](const Network::State * state) {
        return state->accessPoint;
    });
    Network::Manager::Selector networkManagerSelector(networkSelector, [](const Network::State * state) {
        return state->manager;
    });
    Network::Station::Selector networkStationSelector(networkSelector, [](const Network::State * state) {
        return state->station;
    });

    void init(Store & store, const Reducer & reducer, const JsonObject & object) {
      deserialize(object, [&](const State * initialState) {
          store.setReducer(&reducer, initialState);
          lightSelector.init();
          networkSelector.init();
          networkAccessPointSelector.init();
          networkManagerSelector.init();
          networkStationSelector.init();
      });
    }

  }
}
