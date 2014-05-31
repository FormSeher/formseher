#include "objectdetection/databaseutils.h"
#include "objectdetection/model.h"
#include "objectdetection/object.h"
#include "utils/rapidjson/document.h"
#include "utils/rapidjson/stringbuffer.h"
#include "utils/rapidjson/writer.h"
#include "iostream"
#include "fstream"

namespace formseher{

    DatabaseUtils::DatabaseUtils(std::string path){
        pathToDatabase = path;
    }

    std::vector<Model> DatabaseUtils::read(){

        std::string databaseString;
        std::ifstream dbFile;

        // read file
        dbFile.open(pathToDatabase);
        while(!dbFile.is_open()){
            getline(dbFile, databaseString);
        }
        dbFile.close();

        // parse read file
        document.Parse<0>(databaseString.c_str());

        // get objects here
        std::vector<Model> objects;

        return objects;
    }

    void DatabaseUtils::write(Object objectToAdd){

        // add object to document here


        // get string from json
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string str = buffer.GetString();

        // write into file
        std::ofstream file(pathToDatabase);
        if (file.is_open()){

            file << str;
            file.close();
        }
    }
}
