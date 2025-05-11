#include "studentmanager.hpp"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <algorithm>

StudentManager::StudentManager() { loadStudentsFromFile(); }

void StudentManager::addStudent(const Student &student) {
  students.append(student);
  saveStudentsToFile();
}

void StudentManager::updateStudent(const QString &lastName,
                                   const Student &updatedStudent) {
  for (auto &student : students) {
    if (student.lastName == lastName) {
      student = updatedStudent;
      break;
    }
  }
  saveStudentsToFile();
}

void StudentManager::deleteStudent(const QString &lastName) {
  students.erase(std::remove_if(students.begin(), students.end(),
                                [lastName](const Student &student) {
                                  return student.lastName == lastName;
                                }),
                 students.end());
  saveStudentsToFile();
}

QVector<Student> StudentManager::getAllStudents() const { return students; }

void StudentManager::sortStudentsAlphabetically() {
  std::sort(students.begin(), students.end(),
            [](const Student &a, const Student &b) {
              return a.lastName < b.lastName;
            });
  saveStudentsToFile();
}

Student StudentManager::findStudent(const QString &lastName) const {
  for (const auto &student : students) {
    if (student.lastName == lastName) {
      return student;
    }
  }
  return Student();
}

void StudentManager::loadStudentsFromFile() {
  QFile file(filename);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    students.clear();

    while (!in.atEnd()) {
      QString line = in.readLine().trimmed();
      if (line.isEmpty()) continue;

      QStringList parts = line.split(' ', Qt::SkipEmptyParts);
      if (parts.size() < 3) continue;

      Student student;
      student.lastName = parts[0];
      student.firstName = parts[1];
      student.patronymic = parts[2];

      for (int i = 3; i < parts.size(); i += 2) {
        if (i + 1 >= parts.size()) break;
        Subject subject;
        subject.name = parts[i];
        subject.grade = parts[i + 1].toInt();
        student.subjects.append(subject);
      }

      students.append(student);
    }
    file.close();
  } else {
    qDebug() << "Failed to open file:" << filename;
  }
}

void StudentManager::saveStudentsToFile() {
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    for (const auto &student : students) {
      out << student.toString() << '\n';
    }
    file.close();
  }
}
