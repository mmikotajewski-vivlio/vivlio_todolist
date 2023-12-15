#include "writeFile.h"

#include <QDataStream>
#include <QTextStream>
#include <iostream>

bool writeLines(QFile *file, QStringList lines)
{
    Q_ASSERT(file->isWritable());

    file->seek(0);
    QTextStream out(file);
    for (auto line : lines) {
        out << line.trimmed() << "\n";
    }

    return true;
}

bool writeLines(QFile *file, QList<Task> tasks)
{
    Q_ASSERT(file->isWritable());

    file->seek(0);
    QTextStream out(file);
    for (auto task : tasks) {
        out << task << "\n";
    }
    out.flush();

    return true;
}

bool appendTask(QFile *file, const Task &task)
{
    Q_ASSERT(file->isWritable());
    QTextStream out(file);

    out << task << "\n";

    return true;
}
