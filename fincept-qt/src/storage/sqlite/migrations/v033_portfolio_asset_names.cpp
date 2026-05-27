#include "storage/sqlite/migrations/MigrationRunner.h"

#include <QSqlError>
#include <QSqlQuery>

namespace fincept {
namespace {

Result<void> sql_v033(QSqlDatabase& db, const char* statement) {
    QSqlQuery query(db);
    if (!query.exec(statement))
        return Result<void>::err(query.lastError().text().toStdString());
    return Result<void>::ok();
}

Result<void> apply_v033(QSqlDatabase& db) {
    auto result = sql_v033(db, "ALTER TABLE portfolio_assets ADD COLUMN holding_name TEXT DEFAULT ''");
    if (result.is_err()) {
        const std::string error = result.error();
        if (error.find("duplicate column name") == std::string::npos)
            return result;
    }

    result = sql_v033(db,
                      "UPDATE portfolio_assets SET holding_name = symbol "
                      "WHERE COALESCE(holding_name, '') = ''");
    if (result.is_err())
        return result;

    return Result<void>::ok();
}

} // namespace

void register_migration_v033() {
    static bool done = false;
    if (done)
        return;
    done = true;
    MigrationRunner::register_migration({33, "portfolio_asset_names", apply_v033});
}

} // namespace fincept
