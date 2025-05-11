#include "studentapp.hpp"

#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

StudentApp::StudentApp(QWidget *parent) : QMainWindow(parent) { setupUi(); }

void StudentApp::createFile() {
  QString fileName = QFileDialog::getSaveFileName(this, "Create File", "",
                                                  "Text Files (*.txt)");
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
      file.close();
    }
  }
}

void StudentApp::addRecord() {
  Student newStudent;
  bool ok;
  newStudent.lastName = QInputDialog::getText(
      this, "Add Record", "Enter Last Name:", QLineEdit::Normal, "", &ok);
  if (!ok) return;

  newStudent.firstName = QInputDialog::getText(
      this, "Add Record", "Enter First Name:", QLineEdit::Normal, "", &ok);
  if (!ok) return;

  newStudent.patronymic = QInputDialog::getText(
      this, "Add Record", "Enter Patronymic:", QLineEdit::Normal, "", &ok);
  if (!ok) return;

  for (int i = 0; i < 4; ++i) {
    Subject subject;
    subject.name = QInputDialog::getText(
        this, "Add Record",
        "Enter Subject Name " + QString::number(i + 1) + ":", QLineEdit::Normal,
        "", &ok);
    if (!ok) return;

    subject.grade = QInputDialog::getInt(
        this, "Add Record", "Enter Grade for " + subject.name + ":", 0, 0, 100,
        1, &ok);
    if (!ok) return;

    newStudent.subjects.push_back(subject);
  }

  studentManager.addStudent(newStudent);
}

void StudentApp::createIndexFiles() {
  studentManager.sortStudentsAlphabetically();
  QMessageBox::information(this, "Success",
                           "Index files created successfully.");
}

void StudentApp::viewFile() {
  auto *outputText = findChild<QTextEdit *>();
  if (outputText) {
    QString fileContent;
    for (const auto &student : studentManager.getAllStudents()) {
      fileContent += student.toString() + '\n';
    }
    outputText->setText(fileContent);
  }
}

void StudentApp::searchRecord() {
  QString searchLastName = QInputDialog::getText(this, "Search Record",
                                                 "Enter Last Name to search:");
  if (searchLastName.isEmpty()) return;

  Student student = studentManager.findStudent(searchLastName);
  if (student.lastName.isEmpty()) {
    QMessageBox::information(this, "Not Found",
                             "Record not found for " + searchLastName);
    return;
  }

  auto *outputText = findChild<QTextEdit *>();
  if (outputText) {
    outputText->setText(student.toString());
  }
}

void StudentApp::searchAndUpdateRecord() {
  bool ok;
  QString searchLastName = QInputDialog::getText(this, "Search and Update",
                                                 "Enter Last Name to search:");
  if (searchLastName.isEmpty()) return;

  Student student = studentManager.findStudent(searchLastName);
  if (student.lastName.isEmpty()) {
    QMessageBox::information(this, "Not Found",
                             "Record not found for " + searchLastName);
    return;
  }

  Student updatedStudent;
  updatedStudent.lastName = QInputDialog::getText(
      this, "Update Record", "Enter Last Name:", QLineEdit::Normal,
      student.lastName, &ok);
  if (!ok) return;

  updatedStudent.firstName = QInputDialog::getText(
      this, "Update Record", "Enter First Name:", QLineEdit::Normal,
      student.firstName, &ok);
  if (!ok) return;

  updatedStudent.patronymic = QInputDialog::getText(
      this, "Update Record", "Enter Patronymic:", QLineEdit::Normal,
      student.patronymic, &ok);
  if (!ok) return;

  for (const auto &subject : student.subjects) {
    Subject updatedSubject;
    updatedSubject.name = QInputDialog::getText(
        this, "Update Subject", "Update Subject Name:", QLineEdit::Normal,
        subject.name, &ok);
    if (!ok) return;

    updatedSubject.grade = QInputDialog::getInt(
        this, "Update Subject", "Update Grade for " + updatedSubject.name + ":",
        subject.grade, 0, 100, 1, &ok);
    if (!ok) return;

    updatedStudent.subjects.push_back(updatedSubject);
  }

  studentManager.updateStudent(searchLastName, updatedStudent);
}

void StudentApp::deleteRecord() {
  QString deleteLastName = QInputDialog::getText(this, "Delete Record",
                                                 "Enter Last Name to delete:");
  if (deleteLastName.isEmpty()) return;

  studentManager.deleteStudent(deleteLastName);
  QMessageBox::information(this, "Success", "Record deleted successfully.");
}

void StudentApp::setupUi() {
  auto *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  auto *layout = new QVBoxLayout(centralWidget);

  auto *titleLabel = new QLabel("Student Records Management", this);
  titleLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(titleLabel);

  auto *createFileButton = new QPushButton("Create File", this);
  connect(createFileButton, &QPushButton::clicked, this,
          &StudentApp::createFile);
  layout->addWidget(createFileButton);

  auto *addRecordButton = new QPushButton("Add Record", this);
  connect(addRecordButton, &QPushButton::clicked, this, &StudentApp::addRecord);
  layout->addWidget(addRecordButton);

  auto *createIndexFilesButton = new QPushButton("Create Index Files", this);
  connect(createIndexFilesButton, &QPushButton::clicked, this,
          &StudentApp::createIndexFiles);
  layout->addWidget(createIndexFilesButton);

  auto *viewFileButton = new QPushButton("View File", this);
  connect(viewFileButton, &QPushButton::clicked, this, &StudentApp::viewFile);
  layout->addWidget(viewFileButton);
  
  auto *searchButton = new QPushButton("Search Record", this);
  connect(searchButton, &QPushButton::clicked, this, &StudentApp::searchRecord);
  layout->addWidget(searchButton);

  auto *searchAndUpdateButton =
      new QPushButton("Search and Update Record", this);
  connect(searchAndUpdateButton, &QPushButton::clicked, this,
          &StudentApp::searchAndUpdateRecord);
  layout->addWidget(searchAndUpdateButton);

  auto *deleteRecordButton = new QPushButton("Delete Record", this);
  connect(deleteRecordButton, &QPushButton::clicked, this,
          &StudentApp::deleteRecord);
  layout->addWidget(deleteRecordButton);

  auto *outputText = new QTextEdit(this);
  layout->addWidget(outputText);
}
