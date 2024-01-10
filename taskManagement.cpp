#include "taskManagement.h"

#include <QDateTime>

#include "readFile.h"
#include "writeFile.h"

QString currentTaskFilePath = "/tmp/current_task";

void startTask(uint32_t taskId)
{
    auto currentTaskFile = readFile(currentTaskFilePath);
    currentTaskFile->open(QFile::WriteOnly | QFile::Truncate);
    int32_t timestamp = QDateTime::currentSecsSinceEpoch();
    QTextStream stream{currentTaskFile};
    stream << taskId << " " << timestamp;
    stream.flush();
}

void stopCurrentTask()
{
    auto currentTaskFile = readFile(currentTaskFilePath);
    currentTaskFile->open(QFile::ReadOnly);
    auto taskListFile = readFile("/tmp/toto");
    taskListFile->open(QFile::ReadOnly);
    auto lines = readLines(taskListFile);
    uint32_t taskIdGenerator = 0;
    QList<Task> tasks;
    for (auto line : lines) {
        tasks.append(Task{line, taskIdGenerator++});
    }
    int32_t currentTimestamp = QDateTime::currentSecsSinceEpoch();
    QTextStream stream{currentTaskFile};
    int32_t readTimestamp;
    auto taskId = 0;

    stream >> taskId >> readTimestamp;

    for (auto &task : tasks) {
        if (task.id() == taskId) {
            std::cout << "The following task has been finished in "
                      << currentTimestamp - readTimestamp << " seconds !" << std::endl;
            std::cout << task.description().toStdString() << std::endl;
            task.setPriority(TaskPriority::Done);
            taskListFile->close();
            taskListFile->open(QFile::WriteOnly | QFile::Truncate);
            writeLines(taskListFile, tasks);
        }
    }
}
