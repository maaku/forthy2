#include "forthy2/cx.hpp"
#include "forthy2/env.hpp"
#include "forthy2/sym.hpp"
#include "forthy2/type.hpp"
#include "forthy2/val.hpp"

namespace forthy2 {
  Env::Item::Item(Env *home, Sym &id, Val &val):
    home(home), id(&id), val(&val) {}

  Macro &Env::add_macro(Cx &cx,
                        Pos pos,
                        Sym &id,
                        const vector<Arg> &args,
                        const vector<Ret> &rets) {
    Macro &m(cx.macro_type.get(cx, id, args, rets));
    bind(pos, id, m);
    return m;
  }

  Method &Env::add_method(Cx &cx,
                          Pos pos,
                          Sym &id,
                          const vector<Arg> &args,
                          const vector<Ret> &rets) {
    MethodSet &s(MethodSet::get(cx, pos, *this, id));

    Method &m(cx.method_type.get(cx,
                                 s,
                                 Args::get_id(cx, id, args),
                                 args, rets,
                                 Args::get_weight(cx, args)));
    
    bind(pos, m.id, m);
    s.push(m);
    return m;
  }

  void Env::bind(Pos pos, Sym &id, Val &val) {
    Iter i(find(id));
    
    if (i == items.end() || *i->id != id) {
      insert(i, id, val);
    } else {
      if (i->home == this) { throw ESys(pos, "Dup binding: ", id); }
      i->val = &val;
    }      
  }

  void Env::bind_type(Cx &cx, Pos pos, Type &type) {
    bind(pos, type.id, type);
  }

  Env::Iter Env::find(Sym &id) {
    return lower_bound(items.begin(), items.end(), id,
                       [&](auto &x, auto &y) { return *x.id < y; });
  }
    
  Val &Env::get(Pos pos, Sym &id) {
    auto i(find(id));
    if (i == items.end() || *i->id != id) { throw ESys(pos, "Unknown id: ", id); }
    return *i->val;
  }
    
  Env::Iter Env::insert(Iter i, Sym &id, Val &val) {
    return items.emplace(i, this, id, val);
  }
  
  void Env::mark_items(Cx &cx) {
    for (Item it: items) { it.val->mark(cx); }
  }
}
