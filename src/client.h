#pragma once
#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

constexpr int DEF_SIZE__ = 1000;
using boost::asio::ip::tcp;
namespace asio = boost::asio;

class Client : public std::enable_shared_from_this<Client> {
public:
  Client(asio::io_context &ctx);
  void start();
  void login(int id, char *name, char *pass);
  void signup(int id, char *name, char *pass);
  void logs(int id, ) std::unordered_map<int, std::string> results;

private:
  void connect(const std::string &host, const std::string &port);
  void shutdown();
  void deliver(const std::string &msg);
  void do_write();
  void read();

  tcp::socket socket_;
  asio::strand<asio::any_io_executor> strand_;
  asio::streambuf buffer_;
  std::deque<std::string> out_queue_;
};
