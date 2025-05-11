#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <QString>
#include <QVector>

/**
 * @brief Structure representing subject information.
 */
struct Subject {
  QString name;
  int grade;
};

/**
 * @brief Structure representing student information.
 */
struct Student {
  QString lastName;    ///< Student's last name.
  QString firstName;   ///< Student's first name.
  QString patronymic;  ///< Student's middle name (patronymic).
  QVector<Subject>
      subjects;  ///< Vector containing student's subject information.

  [[nodiscard]] QString toString() const;
};

#endif  // STUDENT_HPP