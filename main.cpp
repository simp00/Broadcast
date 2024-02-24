#if 0
#include <iostream>
#include <asio.hpp>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/udp.hpp>

using asio::ip::udp;

int main() {
    try {
        asio::io_context io_context;

        // ��ȡ���б�������ӿ�
        std::vector<asio::ip::address_v4> localAddresses;
        for (auto& iface : asio::ip::network_v4::interfaces()) {
            for (auto& address : iface.second.addresses) {
                if (address.is_v4()) {
                    localAddresses.push_back(address.to_v4());
                }
            }
        }

        for (const auto& localAddress : localAddresses) {
            // ����UDP socket
            udp::socket socket(io_context, udp::endpoint(localAddress, 0));
            socket.set_option(asio::socket_base::broadcast(true));

            // �㲥��Ϣ
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
        // ����һ��resolver�Խ�������������
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);

        // ����������������͹㲥��Ϣ
        while (endpoints != asio::ip::tcp::resolver::iterator()) {
            asio::ip::address localAddress = endpoints->endpoint().address();
            if (localAddress.is_v4()) {
                // ����UDP socket
                udp::socket socket(io_context, udp::endpoint(localAddress, 0));
                socket.set_option(asio::socket_base::broadcast(true));

                // �㲥��Ϣ
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
#elif 0
#include <iostream>
#include <asio.hpp>

using asio::ip::udp;
using asio::ip::tcp;


class BroadcastServer {
public:
    BroadcastServer(asio::io_context& io_context, unsigned short port)
    :m_io_context(io_context), m_timer(io_context)
    { // 5�뷢��һ�ι㲥
        startTimer();
    }

private:
    void startTimer() {
        m_timer.expires_from_now(std::chrono::seconds(5)); // ��ʼ�ӳ�5��
        m_timer.async_wait([this](std::error_code ec) {
            if (!ec) {
                broadcastIPAddress();
                startTimer(); // ����������ʱ��
            }
        });
    }

    void broadcastIPAddress() {
        // ��ȡ����������
        try {
            // ����һ��resolver�Խ�������������
            asio::ip::tcp::resolver resolver(m_io_context);
            asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
            asio::ip::tcp::resolver::iterator endpoints = resolver.resolve(query);
                for (tcp::resolver::iterator endpoint = endpoints; endpoint != tcp::resolver::iterator(); ++endpoint) {
                std::cout << "IP Address: " << endpoint->endpoint().address().to_string() << std::endl;
                std::cout << "Port: " << endpoint->endpoint().port() << std::endl;
            }
            // ����������������͹㲥��Ϣ
            while (endpoints != asio::ip::tcp::resolver::iterator()) {
                asio::ip::address localAddress = endpoints->endpoint().address();
                if (localAddress.is_v4()) {
                    // ����UDP socket
                    udp::socket socket(m_io_context, udp::endpoint(localAddress, 0));
                    socket.set_option(asio::socket_base::broadcast(true));

                    // �㲥��Ϣ
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

        // �����������㲥������
        BroadcastServer server(io_context, 12345);

        // ����IO�����÷������ں�̨��ʱ������
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#elif 1
#include <iostream>
#include <asio.hpp>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace asio::ip;


using asio::ip::udp;
using asio::ip::tcp;

// ������ִ��ϵͳ�����ȡ������
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}




class BroadcastServer {
public:
    BroadcastServer(asio::io_context& io_context, unsigned short port)
    :m_io_context(io_context), m_timer(io_context)
    { // 5�뷢��һ�ι㲥
        startTimer();
    }

private:
    void startTimer() {
        m_timer.expires_from_now(std::chrono::seconds(5)); // ��ʼ�ӳ�5��
        m_timer.async_wait([this](std::error_code ec) {
            if (!ec) {
                broadcastIPAddress();
                startTimer(); // ����������ʱ��
            }
        });
    }

    void broadcastIPAddress() {
        // ��ȡ����������
        try {
            // ����һ��resolver�Խ�������������
           // ��ȡ����������Ϣ
        std::string network_info = exec("ip addr show");

        // ���� UDP socket
        udp::socket socket(m_io_context, udp::endpoint(udp::v4(), 0));
        socket.set_option(asio::socket_base::broadcast(true));
        // ����Ŀ���ַ
        udp::endpoint target_address(asio::ip::address_v4::broadcast(), 12345);

        // ��������������Ϣ��Ŀ���ַ
        socket.send_to(asio::buffer(network_info), target_address);
            
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
        // �����������㲥������
        BroadcastServer server(io_context, 12345);

        // ����IO�����÷������ں�̨��ʱ������
        io_context.run();
      
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}


#endif