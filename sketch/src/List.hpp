#ifndef List_hpp
#define List_hpp

template <class T>
class List {
  using f_onEach = std::function<void(T * pMember)>;

  size_t _count;
  T ** _ppMembers;

  public:
    List(size_t count, T ** ppMembers) :
      _count(count),
      _ppMembers(ppMembers) {
    }

    void forEach(f_onEach onEach) {
      for (int i = 0;  i < _count; i++) {
        onEach(_ppMembers[i]);
      }
    }
};

#endif
