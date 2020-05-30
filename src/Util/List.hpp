#ifndef Util_List_hpp
#define Util_List_hpp

#include <functional>

namespace Util {
  template <class T>
  class List {

    public:

      using f_onEach = std::function<void(T & entry)>;

      List(T ** ppEntries) :
        _ppEntries(ppEntries) {
      }

      void forEach(f_onEach onEach) {
        T ** _ppEntry = _ppEntries;
        while (*_ppEntry) {
          onEach(**_ppEntry);
          _ppEntry++;
        }
      }

    private:

      T ** _ppEntries;

  };
}

#endif
