#include "ConfigSubscriber.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(BurpTree::Dispatcher<Factory> & dispatcher, Factory & factory) :
      _dispatcher(dispatcher),
      _factory(factory),
      _logger("Light::ConfigSubscriber")
    {}

    void ConfigSubscriber::setup(const BurpTree::State * initial) {
      _factory.setConfig(initial->as<Config>());
    }

    void ConfigSubscriber::onPublish(const BurpTree::State * next) {
      using namespace std::placeholders;
      _logger.status(_dispatcher.dispatch(std::bind(&Factory::applyConfig, _1, next->as<Config>())));
    }

  }
}
