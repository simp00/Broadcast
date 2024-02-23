#if 0
#include <iostream>
#include <asio.hpp>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/udp.hpp>

using asio::ip::udp;

int main() {
    try {
        asio::io_context io_context;

        // 获取所有本地网络接口
        std::vector<asio::ip::address_v4> localAddresses;
        for (auto& iface : asio::ip::network_v4::interfaces()) {
            for (auto& address : iface.second.addresses) {
                if (address.is_v4()) {
                    localAddresses.push_back(address.to_v4());
                }
            }
        }

        for (const auto& localAddress : localAddresses) {
            // 创建UDP socket
            udp::socket socket(io_context, udp::endpoint(localAddress, 0));
            socket.set_option(asio::socket_base::broadcast(true));

            // 广播消息
            std::string message = "Hello from " + localAddress.to_string();
            udp::endpoint broadcast_endpoint(asio::ip::address_v4::broadcast(), 12345);
            socket.send_to(asio::buffer(message), broadcast_endpoint);

            std::cout << "Broadcast message from " << localAddress.to_string() << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#elif 0
#include <iostream>
#include <asio.hpp>
#include<chrono>
using asio::ip::udp;
void broadcast()
{
    try {
        asio::io_context io_context;
        // 创建一个resolver以解析本地主机名
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

        // 遍历解析结果并发送广播消息
        while (endpoints != asio::ip::tcp::resolver::iterator()) {
            asio::ip::address localAddress = endpoints->endpoint().address();
            if (localAddress.is_v4()) {
                // 创建UDP socket
                udp::socket socket(io_context, udp::endpoint(localAddress, 0));
                socket.set_option(asio::socket_base::broadcast(true));

                // 广播消息
                std::string message = "{ip:" + localAddress.to_string();
                udp::endpoint broadcast_endpoint(asio::ip::address_v4::broadcast(), 12345);
                socket.send_to(asio::buffer(message), broadcast_endpoint);

                std::cout << "Broadcast message from " << localAddress.to_string() << std::endl;
            }
            ++endpoints;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
int main() {

    return 0;
}
#elif 1
#include <iostream>
#include <asio.hpp>

using asio::ip::udp;

class BroadcastServer {
public:
    BroadcastServer(asio::io_context& io_context, unsigned short port)
    :m_io_context(io_context), m_timer(io_context)
    { // 5秒发送一次广播
        startTimer();
    }

private:
    void startTimer() {
        m_timer.expires_from_now(std::chrono::seconds(5)); // 初始延迟5秒
        m_timer.async_wait([this](std::error_code ec) {
            if (!ec) {
                broadcastIPAddress();
                startTimer(); // 重新启动定时器
            }
        });
    }

    void broadcastIPAddress() {
        // 获取本地主机名
        try {
            // 创建一个resolver以解析本地主机名
            asio::ip::tcp::resolver resolver(m_io_context);
            asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
            asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

            // 遍历解析结果并发送广播消息
            while (endpoints != asio::ip::tcp::resolver::iterator()) {
                asio::ip::address localAddress = endpoints->endpoint().address();
                if (localAddress.is_v4()) {
                    // 创建UDP socket
                    udp::socket socket(m_io_context, udp::endpoint(localAddress, 0));
                    socket.set_option(asio::socket_base::broadcast(true));

                    // 广播消息
                    std::string message = "{ip:" + localAddress.to_string();
                    udp::endpoint broadcast_endpoint(asio::ip::address_v4::broadcast(), 12345);
                    socket.send_to(asio::buffer(message), broadcast_endpoint);

                    std::cout << "Broadcast message from " << localAddress.to_string() << std::endl;
                }
                ++endpoints;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    asio::io_context& m_io_context;
    asio::steady_timer m_timer;
};

int main() {
    try {
        asio::io_context io_context;

        // 创建并启动广播服务器
        BroadcastServer server(io_context, 12345);

        // 运行IO服务，让服务器在后台长时间运行
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#endif