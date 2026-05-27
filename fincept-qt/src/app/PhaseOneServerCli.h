#pragma once

#include "multiuser/contracts/PhaseOneAuthTypes.h"

#include <QString>
#include <QStringList>

namespace fincept {

enum class PhaseOneProcessMode {
    Client,
    Server,
};

struct PhaseOneServerCliOptions {
    PhaseOneProcessMode mode = PhaseOneProcessMode::Client;
    QString host;
    quint16 port = multiuser::kPhaseOneDefaultPort;
    QString db_path;
    QString profile = QStringLiteral("default");
    QStringList client_passthrough_args;
};

struct PhaseOneServerCliParseResult {
    bool ok = false;
    PhaseOneServerCliOptions options;
    QString error_code;
    QString message;
};

class PhaseOneServerCli {
  public:
    static PhaseOneServerCliParseResult parse(int argc, const char* const argv[]);
};

} // namespace fincept
