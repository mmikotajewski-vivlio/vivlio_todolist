#include "readFile.h"

#include <QFile>

QFile* readFile(const QString &filePath)
{
    QFile* file = new QFile { filePath };
    return file;
}
