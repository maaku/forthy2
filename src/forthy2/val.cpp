#include "forthy2/cx.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Node<Op> &Val::call(Cx &cx, Pos pos, Node<Op> &return_pc, bool safe, bool now) {
    cx.push(*this);
    return *return_pc.next;
  }

  void Val::iter(Cx &cx, Pos pos, IterBody body) { body(*this); }

  bool Val::mark(Cx &cx) {
    if (marked) { return false; }
    if (Type &t(type(cx)); this != &t) { t.mark(cx); }
    Node<Val>::unlink();
    cx.marked.push(*this);
    marked = true;
    return true;
  }

  Form &Val::unquote(Cx &cx, Pos pos) { return cx.lit_form.get(pos, *this); }

  ostream &operator <<(ostream &out, const Val &val) {
    const_cast<Val &>(val).dump(out);
    return out;
  }
}
