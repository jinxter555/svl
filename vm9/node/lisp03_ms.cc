#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>

using namespace std;

// Forward declarations
struct Expr;
using ExprPtr = shared_ptr<Expr>;
using Env = map<string, ExprPtr>;
using FuncTree = map<string, shared_ptr<void>>;

struct Function {
    vector<string> params;
    ExprPtr body;
    Env closure;
};

struct Expr {
    enum Type { Symbol, Number, List, Func } type;
    string symbol;
    double number;
    vector<ExprPtr> list;
    shared_ptr<Function> func;

    Expr(string s) : type(Symbol), symbol(s) {}
    Expr(double n) : type(Number), number(n) {}
    Expr(vector<ExprPtr> l) : type(List), list(move(l)) {}
    Expr(shared_ptr<Function> f) : type(Func), func(f) {}
};

// Tokenizer
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    string token;
    for (char c : input) {
        if (isspace(c)) {
            if (!token.empty()) tokens.push_back(token), token.clear();
        } else if (c == '(' || c == ')') {
            if (!token.empty()) tokens.push_back(token), token.clear();
            tokens.push_back(string(1, c));
        } else {
            token += c;
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

// Parser
ExprPtr parse(vector<string>& tokens) {
    if (tokens.empty()) throw runtime_error("Unexpected EOF");
    string token = tokens.front(); tokens.erase(tokens.begin());

    if (token == "(") {
        vector<ExprPtr> list;
        while (tokens.front() != ")") list.push_back(parse(tokens));
        tokens.erase(tokens.begin()); // remove ")"
        return make_shared<Expr>(list);
    } else if (token == ")") {
        throw runtime_error("Unexpected ')'");
    } else {
        try {
            return make_shared<Expr>(stod(token));
        } catch (...) {
            return make_shared<Expr>(token);
        }
    }
}

// Utility: Extract symbol path from nested list
vector<string> extractSymbolPath(ExprPtr expr) {
    vector<string> path;
    if (expr->type == Expr::Symbol) {
        path.push_back(expr->symbol);
    } else if (expr->type == Expr::List) {
        for (auto& e : expr->list) {
            if (e->type != Expr::Symbol)
                throw runtime_error("Function path must be symbols");
            path.push_back(e->symbol);
        }
    } else {
        throw runtime_error("Invalid function name");
    }
    return path;
}

// Function tree resolution
shared_ptr<void>& resolveFunc(FuncTree& tree, const vector<string>& path, bool create = false) {
    FuncTree* current = &tree;
    for (size_t i = 0; i < path.size(); ++i) {
        const string& key = path[i];
        if (!current->count(key)) {
            if (create)
                (*current)[key] = make_shared<FuncTree>();
            else
                throw runtime_error("Function path not found: " + key);
        }
        if (i == path.size() - 1) return (*current)[key];
        current = static_pointer_cast<FuncTree>((*current)[key]).get();
    }
    throw runtime_error("Invalid function path");
}

// Evaluator
ExprPtr eval(ExprPtr expr, Env& env, FuncTree& funcTree) {
    if (expr->type == Expr::Number) return expr;
    if (expr->type == Expr::Symbol) {
        if (env.count(expr->symbol)) return env[expr->symbol];
        throw runtime_error("Undefined symbol: " + expr->symbol);
    }

    const auto& list = expr->list;
    if (list.empty()) throw runtime_error("Empty expression");

    ExprPtr head = list[0];

    // Special forms
    if (head->type == Expr::Symbol) {
        string op = head->symbol;

        if (op == "define") {
            string var = list[1]->symbol;
            ExprPtr val = eval(list[2], env, funcTree);
            env[var] = val;
            return val;
        }

        if (op == "defun") {
            vector<string> path = extractSymbolPath(list[1]);
            vector<string> params;
            for (auto& p : list[2]->list)
                params.push_back(p->symbol);
            ExprPtr body = list[3];
            auto fn = make_shared<Function>(Function{params, body, env});
            resolveFunc(funcTree, path, true) = make_shared<Expr>(fn);
            return make_shared<Expr>(fn);
        }

        if (op == "list") {
            vector<ExprPtr> result;
            for (size_t i = 1; i < list.size(); ++i)
                result.push_back(eval(list[i], env, funcTree));
            return make_shared<Expr>(result);
        }

        if (op == "+") {
            double sum = 0;
            for (size_t i = 1; i < list.size(); ++i)
                sum += eval(list[i], env, funcTree)->number;
            return make_shared<Expr>(sum);
        }

        if (op == "-") {
            double result = eval(list[1], env, funcTree)->number;
            for (size_t i = 2; i < list.size(); ++i)
                result -= eval(list[i], env, funcTree)->number;
            return make_shared<Expr>(result);
        }

        if (op == "*") {
            double result = 1;
            for (size_t i = 1; i < list.size(); ++i)
                result *= eval(list[i], env, funcTree)->number;
            return make_shared<Expr>(result);
        }

        if (op == "/") {
            double result = eval(list[1], env, funcTree)->number;
            for (size_t i = 2; i < list.size(); ++i) {
                double denom = eval(list[i], env, funcTree)->number;
                if (denom == 0) throw runtime_error("Division by zero");
                result /= denom;
            }
            return make_shared<Expr>(result);
        }
    }

    // Function call
    vector<string> path = extractSymbolPath(head);
    ExprPtr fn_expr = static_pointer_cast<Expr>(resolveFunc(funcTree, path));
    if (fn_expr->type != Expr::Func)
        throw runtime_error("Not a function");

    auto fn = fn_expr->func;
    if (list.size() - 1 != fn->params.size())
        throw runtime_error("Argument count mismatch");

    Env local_env = fn->closure;
    for (size_t i = 0; i < fn->params.size(); ++i)
        local_env[fn->params[i]] = eval(list[i + 1], env, funcTree);

    return eval(fn->body, local_env, funcTree);
}

// REPL
int main() {
    Env global_env;
    FuncTree funcTree;
    string line;
    cout << "Lisp Interpreter with Tree-Structured Function Names and `list`\n";
    while (getline(cin, line)) {
        if (line == "exit") break;
        try {
            auto tokens = tokenize(line);
            auto ast = parse(tokens);
            auto result = eval(ast, global_env, funcTree);
            if (result->type == Expr::Number)
                cout << result->number << endl;
            else if (result->type == Expr::Symbol)
                cout << result->symbol << endl;
            else if (result->type == Expr::List) {
                cout << "(";
                for (size_t i = 0; i < result->list.size(); ++i) {
                    if (result->list[i]->type == Expr::Number)
                        cout << result->list[i]->number;
                    else if (result->list[i]->type == Expr::Symbol)
                        cout << result->list[i]->symbol;
                    if (i < result->list.size() - 1) cout << " ";
                }
                cout << ")" << endl;
            } else if (result->type == Expr::Func)
                cout << "<function>" << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    return 0;
}

