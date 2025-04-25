#include <boost/asio.hpp>
#include <iostream>

int
main() {
    boost::asio::io_context io;
    boost::asio::steady_timer timer(io, boost::asio::chrono::seconds(2));

    timer.async_wait([](const boost::system::error_code&) {
        std::cout << "Hello from Boost.Asio!" << std::endl;
    });

    io.run();
    return 0;
}
