#pragma once

#include <BurpLogger.hpp>
#include <BurpTree/Node.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>
#include "../Components/Blinker.hpp"
#include "../Components/Button.hpp"
#include "../Reset/Interface.hpp"

namespace BurpDimmer {
  namespace DeviceControls {

    using namespace Config::Network::Manager;
    using namespace Components;
    using namespace std::placeholders;

    template <class Updater>
    class Instance {

      public:

        using ConfigState = Config::Network::Manager::State;
        using ConfigNode = BurpTree::Node::Interface<ConfigState>;

        Instance(
          const BurpLogger::Logger * logger,
          Updater & updater,
          const Reset::Interface & reset,
          const ConfigNode & configNode,
          Blinker & blinker,
          const unsigned long blinkTime,
          Button & button,
          const unsigned long shortDelay,
          const unsigned long longDelay
        ) :
          _updater(updater),
          _reset(reset),
          _configNode(configNode),
          _blinker(blinker),
          _blinkTime(blinkTime),
          _button(button),
          _shortDelay(shortDelay),
          _longDelay(longDelay),
          _logger(logger)
        {} 

        void setup() {
          _blinker.setup();
          _button.setup(_longPresses);
        }

        void loop() {
          _button.loop();
        }

      private:

        Updater & _updater;
        const Reset::Interface & _reset;
        const ConfigNode & _configNode;
        Blinker & _blinker;
        const unsigned long _blinkTime;
        Button & _button;
        const unsigned long _shortDelay;
        const unsigned long _longDelay;
        const BurpLogger::Logger * _logger;

        const Button::LongPress _reboot = {
          0,
          nullptr,
          std::bind(&Instance::_rebootRelease, this)
        };

        const Button::LongPress _query = {
          _shortDelay,
          std::bind(&Instance::_queryPress, this),
          std::bind(&Instance::_queryRelease, this)
        };

        const Button::LongPress _nextPermMode = {
          _shortDelay,
          std::bind(&Instance::_nextPermModePress, this),
          std::bind(&Instance::_nextPermModeRelease, this)
        };

        const Button::LongPress _wpsConfig = {
          _shortDelay,
          std::bind(&Instance::_wpsConfigPress, this),
          std::bind(&Instance::_wpsConfigRelease, this)
        };

        const Button::LongPress _tempAccessPoint = {
          _shortDelay,
          std::bind(&Instance::_tempAccessPointPress, this),
          std::bind(&Instance::_tempAccessPointRelease, this)
        };

        const Button::LongPress _factoryReset = {
          _longDelay,
          std::bind(&Instance::_factoryResetPress, this),
          nullptr
        };

        const Button::LongPress * _longPresses[7] = {
          &_reboot,
          &_query,
          &_nextPermMode,
          &_wpsConfig,
          &_tempAccessPoint,
          &_factoryReset,
          nullptr
        };

        void _rebootRelease() {
          _logger->info("reboot release");
          _reset.reboot();
        }

        void _queryPress() {
          _logger->info("query press");
          _blinker.blink(1, _blinkTime);
        }

        void _queryRelease() {
          _logger->info("query release");
          const ConfigState * state = _configNode.getState();
          _logger->info("permMode: %u", state->permMode);
          delay(1000);
          switch (state->permMode) {
            case ConfigState::PermMode::NORMAL:
              _blinker.blink(1, _blinkTime);
              break;
            case ConfigState::PermMode::ACCESS_POINT:
              _blinker.blink(2, _blinkTime);
              break;
            case ConfigState::PermMode::OFF:
              _blinker.blink(3, _blinkTime);
              break;
            default:
              break;
          }
        }

        void _nextPermModePress() {
          _logger->info("nextPermMode press");
          _blinker.blink(2, _blinkTime);
        }

        void _nextPermModeRelease() {
          _logger->info("nextPermMode release");
          _logger->log("nextPermMode", _updater.update(&Factory::nextPermMode));
        }

        void _wpsConfigPress() {
          _logger->info("wpsConfig press");
          _blinker.blink(3, _blinkTime);
        }

        void _wpsConfigRelease() {
          _logger->info("wpsConfig release");
          _logger->log("startWpsConfig", _updater.update(&Factory::startWpsConfig));
        }

        void _tempAccessPointPress() {
          _logger->info("tempAccessPoint press");
          _blinker.blink(4, _blinkTime);
        }

        void _tempAccessPointRelease() {
          _logger->info("tempAccessPoint release");
          _logger->log("startTempAccessPoint", _updater.update(&Factory::startTempAccessPoint));
        }

        void _factoryResetPress() {
          _logger->info("factoryReset press");
          _blinker.blink(5, _blinkTime);
          _reset.factoryReset();
        }

    };

  }
}
