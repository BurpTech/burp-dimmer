#include <BurpDebug.hpp>
#include "Logger.hpp"

namespace BurpDimmer {

  const char * Logger::_format = "%s : %s";

  Logger::Logger(const char * label) :
    _label(label)
  {}
  
  void Logger::status(const Status & status) {
    switch (status.getLevel()) {
      case Status::Level::INFO:
        BURP_DEBUG_INFO(_format, _label, status.c_str());
        break;
      case Status::Level::WARNING:
        BURP_DEBUG_WARN(_format, _label, status.c_str());
        break;
      case Status::Level::ERROR:
        BURP_DEBUG_ERROR(_format, _label, status.c_str());
        break;
    }
  }

}
