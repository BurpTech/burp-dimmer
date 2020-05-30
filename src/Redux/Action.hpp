#ifndef Redux_Action_hpp
#define Redux_Action_hpp

namespace Redux {
  class Action {

    public:

      unsigned int type;

      Action(unsigned int type) :
        type(type) {
      }

  };
}

#endif
