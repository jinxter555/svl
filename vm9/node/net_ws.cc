#include "net_ws.hh"
#include "lang.hh"
#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

vector<SimpleWebSocketServer::swss_sptr>  SimpleWebSocketServer::swss_objects={};
vector<SocketListener::sl_sptr>  SocketListener::sl_objects={};
vector<SocketSession::ss_sptr>  SocketSession::ss_objects={};
vector<SocketClient::sc_sptr>  SocketClient::sc_objects={};


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
  MYLOGGER(trace_function, "SimpleWebSocketServer::apply_obj(Node&process, Node::Map& lisp_object, const Vector& args)", __func__, SLOG_FUNC_INFO);
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

//------------------------------------------------------------------------
//------------------------------------ SocketSession

SocketSession::SocketSession(tcp::socket&& socket) 
  : ws_(move(socket)) {}

Node::Integer SocketSession::create_and_register(tcp::socket&& socket) {
  auto sptr = make_shared<SocketSession>(move(socket));
  sptr->accept_handshake();
  Node::Integer id = ss_objects.size();
  ss_objects.push_back(sptr);
  return id;
}

void SocketSession::accept_handshake() {
  ws_.accept();

  // Configure standard 60-second idle timeout with auto pings

  websocket::stream_base::timeout opt;
  opt.handshake_timeout = chrono::seconds(30);
  opt.idle_timeout = chrono::seconds(60);
  opt.keep_alive_pings = true;
  ws_.set_option(opt);

  // 2. Register a control callback to monitor activity
  // This triggers whenever a Ping, Pong, or Close control frame is processed
  /*
  ws_.control_callback(
    [](websocket::frame_type kind, beast::string_view payload) {
      if (kind == websocket::frame_type::ping) {
        cout << "[Heartbeat] Received Ping from client. Automatically replying Pong.\n";
      } else if (kind == websocket::frame_type::pong) {
        cout << "[Heartbeat] Received Pong response from client. Connection healthy.\n";
      } else if (kind == websocket::frame_type::close) {
        cout << "[Heartbeat] Received Close request frame.\n";
      }
  });
  */

}

//------------------------------------ 
vector<uint8_t> SocketSession::read_binary() {
  buffer_.consume(buffer_.size());
  ws_.read(buffer_);

  auto data_buffer = buffer_.data();

  const uint8_t* first = static_cast<const uint8_t*>(data_buffer.data());
  const uint8_t* last = first + data_buffer.size();

  return vector<uint8_t>(first, last);
}

string SocketSession::read_text() {
  //cout << "\nbegin: read_text(): bs: " << buffer_.size() << "\n";
  //cout << "buffer1: " << beast::buffers_to_string(buffer_.data()) << "\n";
  buffer_.consume(buffer_.size());
  //cout << "buffer2: " << beast::buffers_to_string(buffer_.data()) << " bs:" << buffer_.size() <<"\n";

  ws_.read(buffer_);
  //cout << "end: read_text(): bs: " << buffer_.size() <<"\n";
  //write_text("got it");

  return beast::buffers_to_string(buffer_.data());
}

void SocketSession::write_text(const string&text) {
  ws_.text(true);
  ws_.write(net::buffer(text));
}

void SocketSession::write_binary(const vector<uint8_t>& binary)  {
  ws_.text(false);
  ws_.write(net::buffer(binary.data(), binary.size()));
}

bool SocketSession::is_open() const { return ws_.is_open(); }
bool SocketSession::got_text() const { return ws_.got_text(); }

void SocketSession::run_echo_server() {
  try {
    while(is_open()) {
      vector<uint8_t> raw_payload = read_binary();
      if(got_text()) {
        string  text_msg(raw_payload.begin(), raw_payload.end());
        cout << "[Text Received]: " << text_msg << (text_msg.back() == '\n' ? "" : "\n");
        write_text("Server text response to: " + text_msg);
  
      } else {
        cout << "[Binary Received]: " << raw_payload.size() << " bytes\n";
        write_binary(raw_payload);
      }
    }
  } catch(beast::system_error const&se) {
    if(se.code() == websocket::error::closed) {
     cout << "Client disconnected cleanly.\n";
    } else {
     cerr << "Session dropped: " << se.code().message() << "\n";
    }
  }
}

Node::OpStatus SocketSession::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "SocketSession::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  try {
    auto &object = object_node._get_map_ref();
    return apply_obj(process, object, args);

  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "Listener object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
}

Node::OpStatus SocketSession::apply_obj(Node&process, Node::Map &lisp_object, const Node::Vector& args) {
  MYLOGGER(trace_function, "SocketSession::apply_obj(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "lisp_object: " + Node::_to_str(lisp_object), SLOG_FUNC_INFO+30);

  Node::Integer id;
  if(args.size() < 1) 
    return {false, Node::create_error(Error::Type::Unknown, "need a SWSS :method, :open, :close etc...")};

  auto &method = args[0];

  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "SWSSession apply :method needs to be an atom. :server, :client, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }

  //cout << "SS apply,pass 1!\n";
  //cout << "lisp_object: " <<  Node::_to_str(lisp_object) << "\n";

  try {
    id  = lisp_object[CC_OBJ_ID]->_get_integer(); //cout << "cc_obj_id: " << id << "\n";
  } catch(...) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }
  auto swss_obj = ss_objects[id];
  auto atom_cc_fun_name = method->_get_integer();

  if(atom_cc_fun_name  == Lang::Atom::read_text) {
 //   cout << "begin read_text: " ;
    auto input_str =  swss_obj->read_text();
//    cout << "read_text: "  << input_str << "\n ";
    return {true, Node::create(Node::create(input_str))};
  } 

  if(atom_cc_fun_name  == Lang::Atom::write_text) {
    if(args.size() < 2) return {false, Node::create_error(Error::Type::Parse, "need string")};
    cout << "sending: " <<  args[1]->_to_str() << "\n";
    swss_obj->write_text(args[1]->_to_str());
    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  }



  if(atom_cc_fun_name  == Lang::Atom::echo) {
    cout << "begin echo: " ;
    swss_obj->run_echo_server();
    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  } 
  if(atom_cc_fun_name  == Lang::Atom::is_open) {
    return {true, Node::create(swss_obj->is_open())};
  }
  if(atom_cc_fun_name  == Lang::Atom::got_text) {
    return {true, Node::create(swss_obj->got_text())};
  }





  return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};

}

//------------------------------------ SocketListener
/*
SocketListener::SocketListener(net::io_context&ioc, const string&address, uint16_t port) 
  : ioc_(ioc), acceptor_(ioc, tcp::endpoint{net::ip::make_address(address), port}) { 
  acceptor_.set_option(net::socket_base::reuse_address(true));
}
*/
SocketListener::SocketListener(const string&address, uint16_t port) 
  : acceptor_(ioc_, tcp::endpoint{net::ip::make_address(address), port}) { 
  acceptor_.set_option(net::socket_base::reuse_address(true));
}



SocketSession SocketListener::accept() {
  tcp::socket socket(ioc_);
  acceptor_.accept(socket);

  SocketSession session(move(socket));
  session.accept_handshake();
  return session;
}

Node::Integer SocketListener::create_and_register(const string& address,  uint16_t port) {
  auto sptr = make_shared<SocketListener>(address, port);
  Node::Integer id =  sl_objects.size();
  sl_objects.push_back(sptr);
  return id;
}

Node::OpStatus SocketListener::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "SocketListener::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  try {
    auto &object = object_node._get_map_ref();
    return apply_obj(process, object, args);

  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "Listener object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
}

Node::OpStatus SocketListener::apply_obj(Node&process, Node::Map &lisp_object, const Node::Vector& args) {
  MYLOGGER(trace_function, "SocketListener::apply_obj(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  Node::Integer id;
  if(args.size() < 1) 
    return {false, Node::create_error(Error::Type::Unknown, "need a Listener method, :server, :accept etc...")};

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
    cout << "SocketListener [server] ip: "  <<  ipaddr << " port: " << port << "\n";

    id = SocketListener::create_and_register(ipaddr, port);
    lisp_object[CC_OBJ_ID]  = Node::create(id);

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
  auto swss_obj = sl_objects[id];

  if(atom_cc_fun_name == Lang::Atom::accept) {
  //  cout << "SocketListener [server] accept !\n";
    tcp::socket socket(swss_obj->ioc_);
    swss_obj->acceptor_.accept(socket);
    auto  ss_obj_id =  SocketSession::create_and_register(move(socket));
    return {true, Node::create(ss_obj_id)};
  }
  cout << "unknown listener command!\n";

  return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};

}


//------------------------------------ SocketClient
SocketClient::SocketClient() : resolver_(ioc_), ws_(ioc_) {}

void SocketClient::connect(const string&host,  uint16_t port) { connect(host, to_string(port)); }

void SocketClient::connect(const string&host, const string&port) {
  server_addr = host; server_port = port;

  auto const results = resolver_.resolve(host, port);
  beast::get_lowest_layer(ws_).connect(results);

  ws_.set_option(websocket::stream_base::decorator(
    [](websocket::request_type& req) {
      req.set(beast::http::field::user_agent, string(BOOST_BEAST_VERSION_STRING) 
        + " websocket-client-lisp");
    }));

  string host_header = host + ":" + port;
  ws_.handshake(host_header, "/");
}

void SocketClient::write_text(const string& message) {
  ws_.text(true);
  ws_.write(net::buffer(message));
}

string SocketClient::read_text() {
  buffer_.consume(buffer_.size());
  //cout << "buffer2: " << beast::buffers_to_string(buffer_.data()) << " bs:" << buffer_.size() <<"\n";

  ws_.read(buffer_);
  //cout << "end: read_text(): bs: " << buffer_.size() <<"\n";
  //write_text("got it");

  return beast::buffers_to_string(buffer_.data());

}
void SocketClient::close() {
  ws_.close(websocket::close_code::normal);
}
void SocketClient::write_binary(const vector<uint8_t>& binary)  {
  ws_.text(false);
  ws_.write(net::buffer(binary.data(), binary.size()));
}

vector<uint8_t> SocketClient::read_binary() {
  buffer_.consume(buffer_.size());
  ws_.read(buffer_);

  auto data_buffer = buffer_.data();

  const uint8_t* first = static_cast<const uint8_t*>(data_buffer.data());
  const uint8_t* last = first + data_buffer.size();

  return vector<uint8_t>(first, last);
}

//Node::Integer SocketClient::create_and_register(const string& address,  uint16_t port) {
Node::Integer SocketClient::create_and_register() {
  auto sptr = make_shared<SocketClient>();
  Node::Integer id =  sc_objects.size();
  sc_objects.push_back(sptr);
  return id;
}

bool SocketClient::is_open() const { return ws_.is_open(); }
bool SocketClient::got_text() const { return ws_.got_text(); }

Node::OpStatus SocketClient::apply(Node&process, Node &object_node, const Node::Vector& args) {
  MYLOGGER(trace_function, "SocketClient::apply(Node&process, Node& object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "object_node: " + object_node._to_str(), SLOG_FUNC_INFO+30);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);

  try {
    auto &object = object_node._get_map_ref();
    return apply_obj(process, object, args);

  } catch(...) {
    //auto msg = "1File object is not a Node::Map!";
    auto msg = "SocketClient object is not a Node::Map or applying method not successful!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
}

Node::OpStatus SocketClient::apply_obj(Node&process, Node::Map &lisp_object, const Node::Vector& args) {
  MYLOGGER(trace_function, "Socketclient::apply_obj(Node&process, Map& lisp_object, const Vector& args)", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, "args: " + Node::_to_str(args), SLOG_FUNC_INFO+30);
 

  Node::Integer id;
  if(args.size() < 1) 
    return {false, Node::create_error(Error::Type::Unknown, "need a SWSS :method, :open, :close etc...")};

  auto &method = args[0];

  if(method->_get_type() != Node::Type::Atom ){
    auto msg = "SocketClient apply :method needs to be an atom. :server, :client, :getline, etc!";
    cerr << msg << "\n";
    return {false, Node::create_error(Error::Type::Parse, msg)};
  }
  auto atom_cc_fun_name = method->_get_integer();


  //cout << "SS apply,pass 1!\n";
  //cout << "lisp_object: " <<  Node::_to_str(lisp_object) << "\n";
  if(atom_cc_fun_name  == Lang::Atom::initialize) {
    id =  SocketClient::create_and_register();
    lisp_object[CC_OBJ_ID]  = Node::create(id);
    return {true, Node::create(id)};
  }

  try {
    id  = lisp_object[CC_OBJ_ID]->_get_integer(); //cout << "cc_obj_id: " << id << "\n";
  } catch(...) {
    auto msg = "no CC_OBJ_ID or has been deleted or file has been closed!";
    return {false, Node::create_error(Error::Type::Unknown, msg)};
  }
  auto sc_obj = sc_objects[id];

  if(atom_cc_fun_name  == Lang::Atom::connect) {
    if(args.size() < 3) return {false, Node::create_error(Error::Type::Parse, "need address and port")};
    auto ipaddr = args[1]->_to_str();
    auto port = args[2]->_to_str();
    cout << "[server] addr: "  <<  ipaddr << " port: " << port << "\n";
    //id =  SocketClient::create_and_register();
    //lisp_object[CC_OBJ_ID]  = Node::create(id);
    sc_obj->connect(ipaddr, port);
    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  }
  if(atom_cc_fun_name  == Lang::Atom::write_text) {
    if(args.size() < 2) return {false, Node::create_error(Error::Type::Parse, "need string")};
    cout << "sending: " <<  args[1]->_to_str() << "\n";
    sc_obj->write_text(args[1]->_to_str());
    return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};
  }
  if(atom_cc_fun_name  == Lang::Atom::read_text) {
 //   cout << "begin read_text: " ;
    auto input_str =  sc_obj->read_text();
//    cout << "read_text: "  << input_str << "\n ";
    return {true, Node::create(Node::create(input_str))};
  } 


  return {true, Node::create(Lang::Atom::ok, Node::Type::Atom)};

}
