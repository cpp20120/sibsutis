#ifndef STUDENTAPP_HPP
#define STUDENTAPP_HPP

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "studentmanager.hpp"

/**
 * @class StudentApp
 * @brief Main application window for managing student records.
 *
 * This class provides a graphical user interface for managing student records,
 * including creating, viewing, searching, updating, and deleting records.
 */
class StudentApp : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Constructs a StudentApp object.
   *
   * @param parent The parent widget.
   */
  explicit StudentApp(QWidget *parent = nullptr);

 private slots:
  /**
   * @brief Creates a new file for storing student records.
   */
  void createFile();

  /**
   * @brief Adds a new student record.
   */
  void addRecord();

  /**
   * @brief Creates index files for sorting student records alphabetically.
   */
  void createIndexFiles();

  /**
   * @brief Displays the contents of the student records file.
   */
  void viewFile();

  /**
   * @brief Searches for a student record by last name and updates it.
   */
  void searchAndUpdateRecord();

  /**
   * @brief Searches for a student record by last name and displays it.
   */
  void searchRecord();

  /**
   * @brief Deletes a student record by last name.
   */
  void deleteRecord();

 private:
  StudentManager studentManager;  ///< Manages student records.

  /**
   * @brief Sets up the user interface.
   */
  void setupUi();
};

#endif  // STUDENTAPP_HPP
