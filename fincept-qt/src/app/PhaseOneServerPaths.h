#pragma once

#include "app/PhaseOneServerCli.h"
#include "core/config/AppPaths.h"
#include "multiuser/contracts/PhaseOneAuthTypes.h"

namespace fincept {

struct PhaseOneResolvedServerOptions {
    QString host;
    quint16 port = multiuser::kPhaseOneDefaultPort;
    QString db_path;
    QString server_root;
    QString requested_profile;
    bool ignored_profile = false;
    AppPaths::Overrides app_path_overrides;
};

class PhaseOneServerPaths {
  public:
    static PhaseOneResolvedServerOptions resolve(const PhaseOneServerCliOptions& options);
};

} // namespace fincept
