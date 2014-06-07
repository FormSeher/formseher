#ifndef FS_HAFFDATABASE_H
#define FS_HAFFDATABASE_H

#include <vector>
#include <string>

#include "objectdetection/object.h"

namespace formseher {

class HaffDatabase
{
public:
    /**
     * @brief Ceate a new instance of a HaffDatabase.
     * @param filePath The file where the database is stored.
     */
    HaffDatabase(std::string filePath);

    /**
     * @brief Destructor. WARNING: All Object-pointers retrieved from this
     * Database become invalid!
     */
    ~HaffDatabase();

    /**
     * @brief Loads the objects stored in the database.
     */
    bool load();

    /**
     * @brief Get the objects previously loaded by HaffDatabase::load().
     * @return Vector of the Objects
     */
    const std::vector<const Object*>& getObjects() const;

private:
    // Path to the database file
    std::string filePath;

    // Populated by Objects retrieved from load().
    std::vector<const Object*> objects;
};

} // namespace formseher

#endif // FS_HAFFDATABASE_H
