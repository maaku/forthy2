#ifndef FORTHY2_FORM_QUOTE_HPP
#define FORTHY2_FORM_QUOTE_HPP

#include "forthy2/form.hpp"

namespace forthy2 {
  struct Val;
  
  struct QuoteForm: Form {
    Form &val;
    
    QuoteForm(const Pos &pos, Form &val);
    Node<Op> &compile(Cx &cx, Forms &in, Node<Op> &out, int quote) override;
    void dealloc(Cx &cx) override;
    void mark_vals(Cx &cx) override;
    void write(ostream &out) override;
  };
}

#endif
