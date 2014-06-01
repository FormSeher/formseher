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


        std::ifstream dbFile(pathToDatabase);

        // read file
        std::string databaseString( (std::istreambuf_iterator<char>(dbFile) ), (std::istreambuf_iterator<char>()) );

        // parse read file
        document.Parse<0>(databaseString.c_str());

        // get objects here
        std::vector<Model> objectsToReturn;
        // object array
        const rapidjson::Value& objects = document["objects"];
        assert(objects.IsArray());

        // get every object from objects-array
        for (rapidjson::SizeType i = 0; i < objects.Size(); i++){

            const rapidjson::Value& object = objects[i]["object"];
            Model model;

            // set name for model
            assert((object["name"].IsString()));
            model.setName(object["name"].GetString());

            // get lines of object
            const rapidjson::Value& lines = object["lines"];
            assert(lines.IsArray());
            for (rapidjson::SizeType lineCounter = 0; lineCounter < lines.Size(); lineCounter++){

                const rapidjson::Value& line = lines[lineCounter]["line"];
                assert(line.HasMember("start"));
                assert(line.HasMember("end"));

                const rapidjson::Value& start = line["start"];
                const rapidjson::Value& end = line["end"];

                // add line to model
                Line lineToAdd(start["x"].GetInt(), start["y"].GetInt(), end["x"].GetInt(), end["y"].GetInt());
                model.addLine(lineToAdd);
            }
            objectsToReturn.push_back(model);
        }
        return objectsToReturn;
    }

    void DatabaseUtils::write(){

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

    void DatabaseUtils::addObject(Object objectToAdd){

        assert(document.HasMember("objects"));
        rapidjson::Value& objects = document["objects"];
        assert(objects.IsArray());

        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

        rapidjson::Value obj;
        obj.SetObject();
        obj.AddMember("name", objectToAdd.getName().c_str(), allocator);

        const std::vector<const Line*> linesToAdd = objectToAdd.getLines();

        rapidjson::Value lines;
        lines.SetArray();

        for(uint i = 0; i < linesToAdd.size(); i++){

            rapidjson::Value line;
            line.SetObject();

            rapidjson::Value start;
            start.SetObject();

            rapidjson::Value end;
            end.SetObject();

            start.AddMember("x", linesToAdd[i]->getStart().x, allocator);
            start.AddMember("y", linesToAdd[i]->getStart().y, allocator);

            end.AddMember("x", linesToAdd[i]->getEnd().x, allocator);
            end.AddMember("y", linesToAdd[i]->getEnd().y, allocator);

            line.AddMember("start", start, allocator);
            line.AddMember("end", end, allocator);

//            lines[rapidjson::SizeType(i)] = line;
//            lines.AddMember("line", line, allocator);
            rapidjson::Value lineName;
            lineName.SetObject();
            lineName.AddMember("line", line, allocator);
            lines.PushBack(lineName, allocator);
        }

        obj.AddMember("lines", lines, allocator);
        rapidjson::Value objName;
        objName.SetObject();
        objName.AddMember("object", obj, allocator);
//        obj.
//        objects.AddMember("object", obj, allocator);
        objects.PushBack(objName, allocator);
    }

    void DatabaseUtils::removeObject(Object objectToRemove){

        assert(document.HasMember("objects"));
        rapidjson::Value& objects = document["objects"];
        assert(objects.IsArray());

        for (rapidjson::SizeType i = 0; i < objects.Size(); i++){

            rapidjson::Value& object = objects[i];
            assert(object.IsObject());

            if(objectToRemove.getName().compare(object["name"].GetString()) == 0){
                object.Clear();
            }
        }
    }
}
