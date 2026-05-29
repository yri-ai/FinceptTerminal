#include "app/PhaseOneServerCli.h"
#include "app/PhaseOneStartupCoordinator.h"

#include <QApplication>

#include <cstdio>

int main(int argc, char* argv[]) {
    const auto cli = fincept::PhaseOneServerCli::parse(argc, argv);
    if (!cli.ok) {
        fprintf(stderr, "[PhaseOneServerCli] %s\n", qUtf8Printable(cli.message));
        return 1;
    }

    if (cli.options.mode == fincept::PhaseOneProcessMode::Server) {
        fprintf(stderr,
                "[PhaseOneServerCli] --server is no longer supported in FinceptTerminal. "
                "Use FinceptServer instead.\n");
        return 1;
    }

    fincept::PhaseOneStartupCoordinator startup_coordinator;
    startup_coordinator.initialize_pre_app();

    startup_coordinator.initialize_client_pre_app(cli.options);
    QApplication app(argc, argv);
    return startup_coordinator.run_client(app);
}
