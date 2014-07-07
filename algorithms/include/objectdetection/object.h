#ifndef FS_OBJECT_H
#define FS_OBJECT_H

#include "objectdetection/model.h"

namespace formseher
{

class Object : public Model
{
public:
    /**
     * @brief Object standard constructor
     */
    Object();

    /**
     * @brief Object copy constructor
     * @param object Object that is copied.
     */
    Object(const Object& object);

    /**
     * @brief Sets the rating of the Object.
     * @param rating The rating.
     */
    void setRating(float rating);

    /**
     * @brief Get the rating of the Object.
     * @return The rating.
     */
    float getRating();

    /**
     * @brief Clears the list of lines.
     */
    void clearLines();

private:
    float rating;
};

} // namespace formseher

#endif // FS_OBJECT_H
