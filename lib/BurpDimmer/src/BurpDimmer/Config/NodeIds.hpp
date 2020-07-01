#pragma once

#include <BurpTree/Node.hpp>

namespace BurpDimmer {
  namespace Config {

    enum Id : BurpTree::Node::Id {
      networkAccessPoint,
      networkManager,
      networkStation,
      light
    };

  }
}
