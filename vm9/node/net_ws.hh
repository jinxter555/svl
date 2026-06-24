#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "node.hh"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;
namespace websocket = beast::websocket;


using namespace std;



//------------------------------------------------------------------------
class SocketSession {
private:
  websocket::stream<beast::tcp_stream> ws_;
  beast::flat_buffer buffer_;

public:
  explicit SocketSession(tcp::socket&& socket);
  void accept_handshake();

  vector<uint8_t> read_binary();
  string read_text();

  void write_text(const string&text);
  void write_binary(const vector<uint8_t>& binary) ;

  bool is_open() const;
  bool got_text() const;

  void run_echo_server();


  using ss_uptr = unique_ptr <SocketSession>;
  static vector<ss_uptr> ss_objects;

  static Node::Integer create_and_register(tcp::socket&& socket);
  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply_obj(Node&process, Node::Map &object, const Node::Vector& args) ;

};

class SocketListener {
private:
  //net::io_context& ioc_;
  net::io_context ioc_;
  tcp::acceptor acceptor_;
public:
  //SocketListener(net::io_context& ioc, const string& address,  uint16_t port);
  SocketListener(const string& address,  uint16_t port);
  SocketSession accept();
  using sl_uptr =  unique_ptr<SocketListener>;
  static vector<sl_uptr> sl_objects;
  static Node::Integer  create_and_register(const string& address,  uint16_t port);

  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply_obj(Node&process, Node::Map &object, const Node::Vector& args) ;

};

class SocketClient {
private:
  net::io_context ioc_;
  tcp::resolver resolver_;
  websocket::stream<beast::tcp_stream> ws_;
  beast::flat_buffer buffer_;

  string server_addr;
  string server_port;

public:
  SocketClient();
  void connect(const string&host, uint16_t port);
  void connect(const string&host, const string&port);

  void write_text(const string& message);
  void write_binary(const vector<uint8_t>& binary) ;
  string read_text();
  vector<uint8_t> read_binary();
  void close();

  bool is_open() const;
  bool got_text() const;

  //static Node::Integer  create_and_register(const string& address,  uint16_t port);
  static Node::Integer  create_and_register();

  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply_obj(Node&process, Node::Map &object, const Node::Vector& args) ;

  using sc_uptr = unique_ptr   <SocketClient>;
  static vector<sc_uptr>  sc_objects;

};

