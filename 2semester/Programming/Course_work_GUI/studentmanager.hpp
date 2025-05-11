#ifndef STUDENTMANAGER_HPP
#define STUDENTMANAGER_HPP

#include <QString>
#include <QVector>

#include "student.hpp"

/**
 * @class StudentManager
 * @brief Manages student records, including loading, saving, and manipulating
 * records.
 *
 * This class provides functionality to add, update, delete, and search for
 * student records. It also handles loading and saving records to a file.
 */
class StudentManager {
 public:
  /**
   * @brief Constructs a StudentManager object.
   */
  StudentManager();  // Constructor

  /**
   * @brief Adds a student record.
   *
   * @param student The student record to add.
   */
  void addStudent(const Student &student);

  /**
   * @brief Updates a student record.
   *
   * @param lastName The last name of the student to update.
   * @param updatedStudent The updated student record.
   */
  void updateStudent(const QString &lastName, const Student &updatedStudent);

  /**
   * @brief Deletes a student record by last name.
   *
   * @param lastName The last name of the student to delete.
   */
  void deleteStudent(const QString &lastName);

  /**
   * @brief Retrieves all student records.
   *
   * @return A vector of all student records.
   */
  QVector<Student> getAllStudents() const;

  /**
   * @brief Sorts student records alphabetically by last name.
   */
  void sortStudentsAlphabetically();

  /**
   * @brief Finds a student record by last name.
   *
   * @param lastName The last name of the student to find.
   * @return The found student record, or an empty Student object if not found.
   */
  Student findStudent(const QString &lastName) const;

 private:
  QVector<Student> students;  ///< Vector to store student records.
  QString filename =
      "students.txt";  ///< The filename for storing student records.

  /**
   * @brief Loads student records from a file.
   */
  void loadStudentsFromFile();

  /**
   * @brief Saves student records to a file.
   */
  void saveStudentsToFile();
};

#endif  // STUDENTMANAGER_HPP
