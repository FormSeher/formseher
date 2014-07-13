#ifndef LEARNINGOBJECT_H
#define LEARNINGOBJECT_H

// Database tool
#include "imagemode.h"

// Formseher project
#include "line.h"
#include "linedetection/linedetectionalgorithm.h"
#include "objectdetection/databaseutils.h"

// OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Qt
#include <QColor>
#include <QObject>
#include <QString>

/**
 * @brief The LearningObject class represents a instance of learning a object.
 * It holds all information, like database, image, lines, settings.
 */
class LearningObject : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief LearningObject constructor.
     * @param imagePath Path to a opened image which contains the learn object.
     */
    LearningObject(QString imagePath);

    /**
     * @brief LearningObject destructor.
     */
    ~LearningObject();

    /**
     * @brief setDatabase Assignes the opened database to this LearningObject.
     * @param databasePath Path to the database file.
     */
    void setDatabase(QString databasePath);

    /**
     * @brief getDatabaseModels Getter for all models of the database file.
     * @return Vector of models from database.
     */
    std::vector<formseher::Model> getDatabaseModels() const;

    /**
     * @brief getImage Getter for the loaded image.
     * @return Loaded image.
     */
    cv::Mat getImage() const;

    /**
     * @brief getImagePath Getter for the loaded image's path.
     * @return Loaded image's path.
     */
    QString getImagePath() const;

    /**
     * @brief getDatabasePath Getter for the loaded database's path.
     * @return Loaded database's path.
     */
    QString getDatabasePath() const;

    /**
     * @brief getLines Getter for the line vectors of possible and chosen lines.
     * @return Pair of possible and chosen lines.
     */
    std::pair<std::vector<formseher::Line>, std::vector<formseher::Line> > getLines() const;

    /**
     * @brief getOriginalImage Getter for the originally loaded image.
     * @return Originally loaded image.
     */
    cv::Mat getOriginalImage() const;

    /**
     * @brief saveToDatabase Saves the current chosenLines with the given name as a model to the database.
     * @param name Current model's name.
     */
    void saveToDatabase(QString name);

    /**
     * @brief addChosenLine Adds the given line to the chosenLines vector.
     * @param line Line to be added.
     */
    void addChosenLine(formseher::Line line);

    /**
     * @brief addChosenLines Adds the given lines to the chosenLines vector.
     * @param lines Lines to be added.
     */
    void addChosenLines(std::vector<formseher::Line> lines);


public slots:
    /**
     * @brief slot_getImage Slot to calculate the new displayed image based on the settings.
     * @param mode Current chosen imagemode.
     * @param possibleIndex Index of the currently chosen line in the possible lines listView.
     * @param chosenIndex Index of the currently chosen line in the chosen lines listView.
     */
    void slot_getImage(ImageMode mode, int possibleIndex = -1, int chosenIndex = -1);

    /**
     * @brief slot_setSettings Slot to set new settings.
     * @param lineDetectionAlgorithm Pointer to the line detection algorithm.
     * @param lineColors Pair of colors the lines get drawed with.
     * @param thickness Thickness the lines get drawed with.
     */
    void slot_setSettings(formseher::LineDetectionAlgorithm* lineDetectionAlgorithm, std::pair<QColor, QColor> lineColors, int thickness);

    /**
     * @brief slot_doubleClicked Slot that gets connected to a doubleclick event of the lines listViews.
     * @param clickedLines Pair of indexes from the listViews (The one not clicked is -1).
     */
    void slot_doubleClicked(std::pair<int, int> clickedLines);

    /**
     * @brief slot_deleteFromDataBase Slot to delete a model from the database.
     * @param name Name of the object that should be deleted from the database.
     */
    void slot_deleteFromDataBase(QString name);

signals:
    /**
     * @brief signal_newImage Signal that gets emmited if a new image is loaded.
     */
    void signal_newImage(cv::Mat);

    /**
     * @brief signal_settingsChanged Signal that gets emmited if the settings get changed.
     */
    void signal_settingsChanged();

    /**
     * @brief signal_linesChanged Signal that gets emmited if the line vectors get changed.
     */
    void signal_linesChanged(std::pair<std::vector<formseher::Line>, std::vector<formseher::Line>>);

    /**
     * @brief signal_newDatabase Signal that gets emmited if a new database is loaded.
     */
    void signal_newDatabase(std::vector<formseher::Model>);


private:
    /** @brief Content of the loaded image. */
    cv::Mat image;

    /** @brief Path to the loaded image. */
    QString imagePath;

    /** @brief Path to the loaded database. */
    QString databasePath;

    /** @brief Vector of the possible lines in the image. */
    std::vector<formseher::Line> possibleLines;

    /** @brief Vector of the currently chosen lines. */
    std::vector<formseher::Line> chosenLines;

    /** @brief  Pointer to the DatabaseUtils object. */
    formseher::DatabaseUtils* databaseUtils;

    /** @brief Pointer to the chosen line detection algorithm. */
    formseher::LineDetectionAlgorithm* lineDetectionAlgorithm;

    /** @brief Pair of colors the lines get drawed with. */
    std::pair<QColor, QColor> lineColors;

    /** @brief Thickness for painting lines. */
    int thickness = 2;
};

#endif // LEARNINGOBJECT_H
