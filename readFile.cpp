#include "readFile.h"

#include <QFile>
#include <QTextStream>

QFile* readFile(const QString &filePath)
{
    QFile* file = new QFile { filePath };
    return file;
}

QStringList readLines(QFile *file)
{
    Q_ASSERT(file->isReadable());
    QStringList lines{};
    QTextStream in(file);
    while (!in.atEnd()) {
        lines.push_back(in.readLine());
    }
    return lines;
}
