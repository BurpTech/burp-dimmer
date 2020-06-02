#pragma once

namespace Network {

  class Mode {

    public:

      virtual void start() = 0;
      virtual void stop() = 0;
      virtual void setup() = 0;
      virtual void loop() = 0;

  };

}
