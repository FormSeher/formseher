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

        /**
         * @brief DatabaseUtils constructor
         * @param path to existing or to be created database file
         */
        DatabaseUtils(std::string path);

        /**
         * @brief reads in database file from path specified in constructor
         * @return read in models as vector from database file
         */
        std::vector<Model> read();

        /**
         * @brief write added Objects to database file to path specified in constructor
         */
        void write();

        /**
         * @brief adds object to database - reminder: use write() after in the end in order to safe new altered database
         * @param objectToAdd
         */
        void addObject(Object objectToAdd);

        /**
         * @brief removes a object from database - reminder: use write() in the end in order to safe altered database
         * @param objectToRemove
         */
        void removeObject(Object objectToRemove);

    private:

        std::string pathToDatabase;
        rapidjson::Document document;
    };
}
#endif // DATABASEUTILS_H
