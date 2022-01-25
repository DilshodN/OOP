#include "Database.h"

Database::Database() = default;

bool Database::OpenDatabase(const char *path) {
    status = sqlite3_open(path, &database);
    return status != 1;
}

bool Database::ExecuteQuery(const std::string &query) {
    status = sqlite3_exec(database, query.c_str(), Database::callback, nullptr, &db_error);
    if (status != SQLITE_OK) {
        logl("Could not execute query");
        sqlite3_free(db_error);
        return false;
    } else return true;
}


bool Database::GetQueryResult(const std::string &query, Data &data) {
    status = sqlite3_exec(database, query.c_str(), Database::callback, &data, &db_error);
    if (status != SQLITE_OK) {
        logl("Could not execute query on GetEntry()");
        sqlite3_free(db_error);
        return false;
    } else return true;
}

void Database::CloseDatabase() {
    sqlite3_close_v2(database);
}

int Database::callback(void *data, int argc, char **argv, char **azColName) {
    Data *d = (Data *) data;
    d->rows = argc;
    for (int i = 0; i < argc; i++) {
        if (data != nullptr) {
            d->vector.emplace_back((argv[i] ? argv[i] : "NULL"));
        }
    }
    return 0;
}