#include "CLI/CLI.hpp"
#include "server/tcp_server.h"
#include <chrono>

int main(int argc, char** argv) {
    using namespace std::chrono_literals;
    shagit::TCPServer server;
    server.Start();

    CLI::App cli;
    int min_res = 0;
    cli.add_option("-time-limit", "max time for tcp server in minutes.")->expected(1);
    cli.parse(argc, argv);
    cli.get_option("-time-limit")->results(min_res);

    std::chrono::minutes min(min_res);
    while (!server.IsClosed()) {
        auto connections = server.GetConnections();
        std::this_thread::sleep_for(10min);
        if (server.GetConnections() == connections)
            server.Close();
    }

    server.Stop();
    return 0;
}
