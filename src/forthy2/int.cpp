#include "forthy2/cx.hpp"
#include "forthy2/int.hpp"

namespace forthy2 {
  void Int::dump(ostream &out) { out << imp; }

  void Int::iter(Cx &cx, Pos pos, IterBody body) {
    for (Imp i(0); i < imp; i++) { body(cx.int_type.get(cx, i)); }
  }

  void Int::sweep(Cx &cx) {
    Val::sweep(cx);
    cx.int_type.pool.put(*this);
  }

  Type &Int::type(Cx &cx) { return cx.int_type; }

  IntType::IntType(Cx &cx, Sym &id, vector<Type *> parents):
    PoolType<Int>(cx, id, parents) {}
}
