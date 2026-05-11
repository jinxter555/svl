#include "lisp_expr.hh"



const vector<string> LispExpr::lisp_path= {UNIVERSE, "Lang", "Lisp"};
const vector<string> LispExpr::lisp_path_module= {UNIVERSE, "Lang", "Lisp", "Module"};
const vector<string> LispExpr::lisp_path_alias= {UNIVERSE, "Lang", "Lisp", "Alias"};
const vector<string> LispExpr::lisp_path_keyword= {UNIVERSE, "Lang", "Lisp", "Keyword"};
const vector<string> LispExpr::lisp_lang_atoms = {UNIVERSE, "module", "fun", "mvar", "lvar", "class"};
const vector<string> LispExpr::cc_path_module= {UNIVERSE, "Lang", "CC", "Module"};
//const vector<string> LispExpr::interactive_key  = {UNIVERSE, "interactive"};
//const vector<string> LispExpr::lisp_process = {UNIVERSE, "Process"};
const Node::Integer LispExpr::atom_module(str_to_atom("module"));

const Node::Integer LispExpr:: atom_fun(str_to_atom("fun"));
const Node::Integer LispExpr:: atom_def(str_to_atom("def"));
const Node::Integer LispExpr:: atom_class(str_to_atom("class"));
const Node::Integer LispExpr:: atom_get(str_to_atom("get"));
const Node::Integer LispExpr:: atom_set(str_to_atom("set"));
const Node::Integer LispExpr:: atom_index(str_to_atom("index"));
const Node::Integer LispExpr:: atom_size(str_to_atom("size"));
const Node::Integer LispExpr:: atom_ok(str_to_atom("ok"));
const Node::Integer LispExpr:: atom_error(str_to_atom("error"));
const Node::Integer LispExpr:: atom_unknown(str_to_atom("unknown"));
const Node::Integer LispExpr:: atom_lambda(str_to_atom("lambda"));
const Node::Integer LispExpr:: atom_closure(str_to_atom("closure"));
const Node::Integer LispExpr:: atom_else(str_to_atom("else"));
const Node::Integer LispExpr:: atom_atom(str_to_atom("atom"));
const Node::Integer LispExpr:: atom_integer(str_to_atom("integer"));
const Node::Integer LispExpr:: atom_float(str_to_atom("float"));
const Node::Integer LispExpr:: atom_string(str_to_atom("string"));
const Node::Integer LispExpr:: atom_cc_vec(str_to_atom("cc_vec"));
const Node::Integer LispExpr:: atom_cc_list(str_to_atom("cc_list"));
const Node::Integer LispExpr:: atom_cc_deque(str_to_atom("cc_deque"));
const Node::Integer LispExpr:: atom_cc_map(str_to_atom("cc_map"));
const Node::Integer LispExpr:: atom_cc_imap(str_to_atom("cc_imap"));
const Node::Integer LispExpr:: atom_object(str_to_atom("object"));
const Node::Integer LispExpr:: atom_namespace(str_to_atom("namespace"));
const Node::Integer LispExpr:: atom_pid(str_to_atom("pid"));
const Node::Integer LispExpr:: atom_ppid(str_to_atom("ppid"));
const Node::Integer LispExpr:: atom_queue(str_to_atom("queue"));
const Node::Integer LispExpr:: atom_swap(str_to_atom("swap"));
const Node::Integer LispExpr:: atom_send(str_to_atom("send"));
const Node::Integer LispExpr:: atom_receive(str_to_atom("receive"));
const Node::Integer LispExpr:: atom_worker(str_to_atom("worker"));
const Node::Integer LispExpr:: atom_inbox(str_to_atom("inbox"));
const Node::Integer LispExpr:: atom_ipc(str_to_atom("ipc"));
const Node::Integer LispExpr:: atom_print(str_to_atom("print"));
const Node::Integer LispExpr:: atom_self(str_to_atom("self"));
const Node::Integer LispExpr:: atom_eval(str_to_atom("eval"));
const Node::Integer LispExpr:: atom_wait(str_to_atom("wait"));