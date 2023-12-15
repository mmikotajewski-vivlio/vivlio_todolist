#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <QFile>
#include "task.h"

bool writeLines(QFile *file, QStringList lines);
bool writeLines(QFile *file, QList<Task> tasks);

bool appendTask(QFile *file, const Task &task);

#endif // WRITEFILE_H
