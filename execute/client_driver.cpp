#include "server/client.h"
#include "CLI/CLI.hpp"
#include "server/session.h"

namespace shagit {
namespace {

Args ParseArgs(int argc, char **argv) {
    CLI::App cli;
    std::map<std::string, Request> mapper = {
        {"list", Request::LIST_HUBS},
        {"create-hub", Request::CREATE_HUB},
        {"join-hub", Request::JOIN_HUB},
        {"approve-hub", Request::APPROVE_JOIN},
        {"get-hub", Request::GET_HUB},
        {"create-cr", Request::CREATE_CR},
        {"approve-cr", Request::APPROVE_CR},
        {"echo", Request::ECHO_TEST}
    };

    cli.add_subcommand(argv[0]);
    cli.add_subcommand("list");
    cli.add_subcommand("create-hub");
    cli.add_subcommand("join-hub");
    cli.add_subcommand("approve-hub");
    cli.add_subcommand("get-hub");
    cli.add_subcommand("create-cr");
    cli.add_subcommand("approve-cr");
    cli.add_subcommand("echo");

    cli.parse(argc, argv);
    auto cmd = cli.get_subcommand_ptr(argv[1]);

    Request request = mapper.find(cmd->get_name())->second;
    std::optional<HubStorage::Id> id = std::nullopt;
    switch (request) {
        case GET_HUB:
            id.emplace(0);
            std::cin >> *id;
            break;
        case CREATE_CR:
            id.emplace(std::stoull(cmd->get_name()));
            break;
        case APPROVE_CR:
            id.emplace(std::stoull(cmd->get_name()));
            break;
        default:
            /* ignore*/;
    }
    return {request, id};
}

}  // namespace
}  // namespace shagit

int main(int argc, char **argv) {
    shagit::Client client;
    client.Connect();
    client.SendRequest(shagit::ParseArgs(argc, argv));
    return 0;
}
