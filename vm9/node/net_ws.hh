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

struct SessionState {
  websocket::stream<beast::tcp_stream> ws;
};


class SimpleWebSocketServer {
  net::io_context ioc_;
  tcp::acceptor acceptor_;

  using lambda_t = function<void(websocket::stream<beast::tcp_stream>&)> ;
  //lambda_t session_lambda_;
  lambda_t session_lambda_={};


public:
  SimpleWebSocketServer(const string& address, unsigned short port,  lambda_t lambda);
  SimpleWebSocketServer(const string& address, unsigned short port);
  void run();
  void run(lambda_t& lambda);
  void run_echo_server();
  static Node::OpStatus apply(Node&process, Node &node, const Node::Vector& args) ;
  static Node::OpStatus apply_obj(Node&process, Node::Map &object, const Node::Vector& args) ;

  using swss_sptr = shared_ptr<SimpleWebSocketServer>;
  static vector<swss_sptr>  swss_objects;


};