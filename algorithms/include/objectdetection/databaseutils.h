#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include "model.h"
#include "object.h"
#include "utils/rapidjson/document.h"

namespace formseher
{

    class DatabaseUtils{

    public:

        DatabaseUtils(std::string path);
        std::vector<Model> read();
        void write(Object objectToAdd);

    private:

        std::string pathToDatabase;
        rapidjson::Document document;
    };
}
#endif // DATABASEUTILS_H
