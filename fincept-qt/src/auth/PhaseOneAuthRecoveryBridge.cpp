#include "auth/PhaseOneAuthRecoveryBridge.h"

#include "storage/repositories/SettingsRepository.h"

namespace fincept::auth {

void PhaseOneAuthRecoveryBridge::persist_phase_one_session(const SessionData& session) {
    Q_UNUSED(session)
}

void PhaseOneAuthRecoveryBridge::clear_startup_auth_state() {
    SettingsRepository::instance().remove("fincept_session");
}

} // namespace fincept::auth
