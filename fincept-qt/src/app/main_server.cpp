#include "app/PhaseOneServerCli.h"
#include "app/PhaseOneStartupCoordinator.h"

#include <cstdio>

int main(int argc, char* argv[]) {
    const auto cli = fincept::PhaseOneServerCli::parse(argc, argv);
    if (!cli.ok) {
        fprintf(stderr, "[PhaseOneServerCli] %s\n", qUtf8Printable(cli.message));
        return 1;
    }

    fincept::PhaseOneServerCliOptions options = cli.options;
    options.mode = fincept::PhaseOneProcessMode::Server;

    if (!options.client_passthrough_args.isEmpty()) {
        fprintf(stderr,
                "[PhaseOneServerCli] unexpected client arguments in server mode: %s\n",
                qUtf8Printable(options.client_passthrough_args.join(' ')));
        return 1;
    }

    fincept::PhaseOneStartupCoordinator startup_coordinator;
    startup_coordinator.initialize_pre_app();
    if (const auto server_exit = startup_coordinator.maybe_run(argc, argv, options); server_exit.has_value())
        return *server_exit;

    fprintf(stderr, "[PhaseOneServerCli] server startup mode was not selected\n");
    return 1;
}
