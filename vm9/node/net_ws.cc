#include "net_ws.hh"
#include "lang.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<SimpleWebSocketServer::swss_sptr>  SimpleWebSocketServer::swss_objects={};


SimpleWebSocketServer::SimpleWebSocketServer(const string& address, unsigned short port, lambda_t lambda) 
  : acceptor_(ioc_, {net::ip::make_address(address), port})
  , session_lambda_(move(lambda)) {}

SimpleWebSocketServer::SimpleWebSocketServer(const string& address, unsigned short port) 
  : acceptor_(ioc_, {net::ip::make_address(address), port}) {}



void SimpleWebSocketServer::run() {
  while(true) {
    tcp::socket socket(ioc_);
    acceptor_.accept(socket);

    try {
      SessionState state{websocket::stream<beast::tcp_stream>(move(socket))};
      state.ws.accept();

      thread([this, session = move(state)]() mutable {
        try{
          this->session_lambda_(session.ws);
        } catch(exception&e) {
          cerr << "session thread exception: " <<  e.what() << "\n";
        }
      }).detach();

    } catch(const exception& e) {
      cerr << "Connection setup failed: " <<  e.what() << "\n";
    }

  }
}

void SimpleWebSocketServer::run(lambda_t &lambda) {
  while(true) {
    tcp::socket socket(ioc_);
    acceptor_.accept(socket);

    try {
      SessionState state{websocket::stream<beast::tcp_stream>(move(socket))};
      state.ws.accept();

      thread([&lambda, session = move(state)]() mutable {
        try{
          lambda(session.ws);
        } catch(exception&e) {
          cerr << "session thread exception: " <<  e.what() << "\n";
        }
      }).detach();

    } catch(const exception& e) {
      cerr << "Connection setup failed: " <<  e.what() << "\n";
    }
  }
}

void SimpleWebSocketServer::run_echo_server(){

  lambda_t echo_lambda = [](websocket::stream<beast::tcp_stream>&ws) {
    auto remote_ep = beast::get_lowest_layer(ws).socket().remote_endpoint();
    string client_info = remote_ep.address().to_string() + ":"  + to_string(remote_ep.port());

    cout << "[Server] New client connection from " << client_info << "\n";

    beast::flat_buffer buffer;

    while(true) {
      buffer.consume(buffer.size());
      beast::error_code ec;
      ws.read(buffer, ec);

      if(ec == websocket::error::closed) break;
      if(ec) throw beast::system_error{ec};

      string text_message = beast::buffers_to_string(buffer.data());
      cout << "[" << client_info<<"]: " << text_message << "\n";

      ws.text(ws.got_text());
      ws.write(buffer.data());




    }
  };
  run(echo_lambda);
}

Node::OpStatus SimpleWebSocketServer::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "SimpleWebSocketServer::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);


  try {
    auto &object = object_node._get_map_ref();
    return apply_obj(process, object, args);

  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "SWSS object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }


}



Node::OpStatus SimpleWebSocketServer::apply_obj(Node&process, Node::Map &lisp_object, const Node::Vector& args) {

  MYLOGGER(trace_function, "SimpleWebSocketServer::apply_obj(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  Node::Integer id;
  if(args.size() < 1) 
    return {false, Node::create_error(Error::Type::Unknown, "need a SWSS :method, :open, :close etc...")};

  auto &method = args[0];

  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "SWSS apply :method needs to be an atom. :server, :client, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
  auto atom_cc_fun_name = method->_get_integer();

  if(atom_cc_fun_name  == Lang::Atom::server) {
    if(args.size() < 3) return {false, Node::create_error(Error::Type::Parse, "need address and port")};
    auto ipaddr = args[1]->_to_str();
    auto port = args[2]->_get_integer();
    cout << "[server] ip: "  <<  ipaddr << " port: " << port << "\n";

    swss_sptr swss_obj;
    try {
      swss_obj = make_shared<SimpleWebSocketServer>(ipaddr, port);
    } catch(const exception &e) {
      cerr << "make shared<SimpleWeboscket> error: " << e.what() << "\n";
      return {true, Node::create(Lang::Atom::error, Node::Type::Atom)};
    }

    Node::Integer id = swss_objects.size();
    lisp_object[CC_OBJ_ID]  = Node::create( id);
    swss_objects.push_back(move(swss_obj));

    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  } 

  if (lisp_object.find(CC_OBJ_ID) == lisp_object.end()) {
    auto msg = "no CC_OBJ_ID or has been deleted or WS connection has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }
  
  try {
    id  = lisp_object[CC_OBJ_ID]->_get_integer();
  } catch(...) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }

  auto swss_obj = swss_objects[id];
  
  
  if(atom_cc_fun_name == Lang::Atom::run) {
    if(args.size() < 2) return {false, Node::create_error(Error::Type::Parse, "need address and port")};
    if(args[1]->_get_type() == Node::Type::Atom) {
      cout << "run arg[1] is type atom : " << args[1]->_to_str() << "\n";

      auto atom_cc_sub_fun_name = args[1]->_get_integer();
      if(atom_cc_sub_fun_name == Lang::str_to_atom("echo")) {
        cout << "i am in echo server! server object: " << Node::_to_str(lisp_object) <<"\n";
        swss_obj->run_echo_server();
        return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
      }

    }  else {
      cout << "run arg not atom but it is : " << args[1]->_to_str() << "\n";
      return {true, Node::create(Lang::Atom::error, Node::Type::Atom)};
    }

    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  }

  return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};


}