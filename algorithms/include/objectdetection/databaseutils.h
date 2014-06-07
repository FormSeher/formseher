#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include "model.h"
#include "object.h"
#include "utils/rapidjson/document.h"

typedef unsigned int uint;

namespace formseher
{

    class DatabaseUtils{

    public:

        DatabaseUtils(std::string path);
        std::vector<Model> read();
        void write();
        void addObject(Object objectToAdd);
        void removeObject(Object objectToRemove);

    private:

        std::string pathToDatabase;
        rapidjson::Document document;
    };
}
#endif // DATABASEUTILS_H
