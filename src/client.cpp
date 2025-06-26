#include "client.h"

Client::Client(asio::io_context &ctx)
    : socket_(ctx), strand_(socket_.get_executor()) {}

void Client::connect(const std::string &host, const std::string &port) {
  tcp::resolver r(socket_.get_executor());
  auto endpoints = r.resolve(host, port);
  asio::async_connect(
      socket_, endpoints,
      [self = shared_from_this()](boost::system::error_code ec,
                                  const tcp::endpoint &) {
        if (ec) {
          std::cerr << "Connect failed: " << ec.message() << '\n';
          return;
        }
        std::cout << "Connected. Type /room <name> to switch rooms.\n";
        self->read();
      });
}

void Client::shutdown() {
  boost::system::error_code dummy;
  socket_.close(dummy);
  std::cerr << "Disconnected." << std::endl;
}

void Client::login(char *name, char *pass) {
  std::string msg = "LOGIN\n";
  msg += name;
  msg += "\n";
  msg += pass;
  msg += "\n\r\n";
  deliver(msg);
}

void Client::signup(char *name, char *pass) {
  std::string msg = "REGISTER\n";
  msg += name;
  msg += "\n";
  msg += pass;
  msg += "\n\r\n";
  deliver(msg);
}

void Client::deliver(const std::string &msg) {
  asio::post(strand_, [self = shared_from_this(), msg] {
    bool write_in_progress = !self->out_queue_.empty();
    self->out_queue_.push_back(msg + "\n");
    if (!write_in_progress) {
      self->do_write();
    }
  });
}

void Client::do_write() {
  auto self = shared_from_this();
  asio::async_write(
      socket_, asio::buffer(out_queue_.front()),
      asio::bind_executor(
          strand_, [self](boost::system::error_code ec, std::size_t) {
            if (!ec) {
              self->out_queue_.pop_front();
              if (!self->out_queue_.empty()) {
                self->do_write();
              }
            } else {
              std::cerr << "write error: " << ec.message() << std::endl;
            }
          }));
}
