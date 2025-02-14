#ifndef FORTHY2_FORM_SCOPE_HPP
#define FORTHY2_FORM_SCOPE_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct ScopeForm: Form {
    Forms body;
    
    ScopeForm(Pos pos);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out, int quote) override;
    Node<Op> &compile_ref(Cx &cx, Forms &in, Node<Op> &out) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    int splice(Cx &cx, int n) override;
    void write(ostream &out) override;
  };
}

#endif
