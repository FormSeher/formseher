/*
 * This file is part of FormSeher.
 *
 * FormSeher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FormSeher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FormSeher.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2014 FormSeher
 */

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

        std::vector<Model> objectsToReturn;
        std::ifstream dbFile(pathToDatabase);

        // read file
        std::string databaseString( (std::istreambuf_iterator<char>(dbFile) ), (std::istreambuf_iterator<char>()) );

        // parse read file
        document.Parse<0>(databaseString.c_str());

        // if read in file is empty or corrupted return empty vector
        if(document.HasParseError()){
            return objectsToReturn;
        }

        // object array
        const rapidjson::Value& objects = document["objects"];
        if(!objects.IsArray()){
            return objectsToReturn;
        }

        // get every object from objects-array
        for (rapidjson::SizeType i = 0; i < objects.Size(); i++){

            const rapidjson::Value& object = objects[i]["object"];

            if(!object.IsObject()){
                continue;
            }

            Model model;

            // set name for model
            if(object["name"].IsString()){
                model.setName(object["name"].GetString());
            }

            // get lines of object
            const rapidjson::Value& lines = object["lines"];
            if(!lines.IsArray()){
                continue;
            }
            for (rapidjson::SizeType lineCounter = 0; lineCounter < lines.Size(); lineCounter++){

                const rapidjson::Value& line = lines[lineCounter]["line"];

                if(line.HasMember("start") && line.HasMember("end")){
                    const rapidjson::Value& start = line["start"];
                    const rapidjson::Value& end = line["end"];

                    // add line to model
                    Line lineToAdd(start["x"].GetInt(), start["y"].GetInt(), end["x"].GetInt(), end["y"].GetInt());
                    model.addLine(lineToAdd);
                }
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

        // create objects array if database is empty
        if(document.HasParseError()){

            document.Parse<0>("{\"objects\":[]}");
        }

        rapidjson::Value& objects = document["objects"];
        if(!objects.IsArray()){
            return;
        }

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

            rapidjson::Value lineName;
            lineName.SetObject();
            lineName.AddMember("line", line, allocator);
            lines.PushBack(lineName, allocator);
        }

        obj.AddMember("lines", lines, allocator);
        rapidjson::Value objName;
        objName.SetObject();
        objName.AddMember("object", obj, allocator);
        objects.PushBack(objName, allocator);
    }

    void DatabaseUtils::removeObject(Object objectToRemove){

        if(!document.HasMember("objects")){
            return;
        }
        rapidjson::Value& objects = document["objects"];
        if(!objects.IsArray()){
            return;
        }

        for (rapidjson::SizeType i = 0; i < objects.Size(); i++){

            if(!objects[i]["object"].IsObject()){
                continue;
            }

            if(objectToRemove.getName().compare(objects[i]["object"]["name"].GetString()) == 0){
                objects[i].RemoveMember("object");
            }
        }
    }
}
