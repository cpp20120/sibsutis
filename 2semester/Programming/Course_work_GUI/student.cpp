#include "student.hpp"

/**
 * @brief Converts a Student object to its string representation.
 *
 * This function formats a Student object as a string, including the student's
 * name and information about each subject with corresponding grades.
 *
 * @return QString representing the Student object.
 */
QString Student::toString() const {
  QString result = lastName + ' ' + firstName + ' ' + patronymic + ' ';
  for (const auto &subject : subjects) {
    result += subject.name + ' ' + QString::number(subject.grade) + ' ';
  }
  return result.trimmed();
}