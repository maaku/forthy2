#include "forthy2/cx.hpp"
#include "forthy2/ops/rotl.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  RotlOp::RotlOp(Form &form, Node<Op> &prev): Op(form, prev) {}

  void RotlOp::dealloc(Cx &cx) {
    Op::dealloc(cx);
    cx.rotl_op.put(*this);
  }

  void RotlOp::dump(ostream &out) { out << "rotl"; }
}
