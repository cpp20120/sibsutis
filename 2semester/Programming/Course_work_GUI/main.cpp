#include <QApplication>

#include "studentapp.hpp"

/**
 * @brief Entry point for the application.
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 * @return Application exit code.
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  StudentApp studentApp;
  studentApp.show();

  return app.exec();
}