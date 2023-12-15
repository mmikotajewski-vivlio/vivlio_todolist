#ifndef READFILE_H
#define READFILE_H

#include <QString>
#include <QFile>

QFile* readFile(const QString& filePath);

QStringList readLines(QFile *file);

#endif // READFILE_H
