#include <iostream>

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>

#include "ProgramAction.h"
#include "TaskPriority.h"
#include "readFile.h"
#include "task.h"
#include "taskManagement.h"
#include "writeFile.h"

namespace Args {
std::array<QString, 2> helpArgs{"--help", "-h"};
std::array<QString, 2> addArgs{"--add", "-a"};
std::array<QString, 2> addUrgentArgs{"--add-urgent", "-u"};
std::array<QString, 2> addNotSoUrgentArgs{"--add-not-so-urgent", "-n"};
std::array<QString, 2> markAsDoneArgs{"--mark-as-done", "-m"};
std::array<QString, 2> purgeArgs{"--purge", "-p"};
std::array<QString, 2> startTaskArgs{"--start-task", "-s"};
std::array<QString, 2> stopTaskArgs{"--stop-current-task", "-S"};

} // namespace Args

template<typename T, ssize_t size>
bool contains(std::array<T, size> array, const T &value)
{
    return std::find(array.cbegin(), array.cend(), value) != array.cend();
}

void display(const QList<Task> &tasks)
{
    std::cout << "Urgent tasks :" << std::endl;
    for (auto task : tasks) {
        if (task.priority() == TaskPriority::Urgent) {
            std::cout << task << std::endl;
        }
    }
    std::cout << "Less urgent tasks :" << std::endl;
    for (auto task : tasks) {
        if (task.priority() == TaskPriority::NormallyUrgent) {
            std::cout << task << std::endl;
        }
    }
    std::cout << "Not so urgent tasks :" << std::endl;
    for (auto task : tasks) {
        if (task.priority() == TaskPriority::NotSoUrgent) {
            std::cout << task << std::endl;
        }
    }
    std::cout << "Done tasks :" << std::endl;
    for (auto task : tasks) {
        if (task.priority() == TaskPriority::Done) {
            std::cout << task << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    TaskPriority priority = TaskPriority::Unknown;
    ProgramAction action = ProgramAction::Display;
    QString taskToAdd{};
    uint32_t taskId{};
    int currentArgIndex = 0;
    uint32_t taskIdGenerator = 0;
    while (currentArgIndex != argc) {
        currentArgIndex++;
        QString currentArg{argv[currentArgIndex]};
        if (contains<QString, 2>(Args::helpArgs, currentArg)) {
            std::cout << "Program name : vivtodo\n"
                      << "Description : Super todo list management\n"
                      << "Options :\n"
                      << "\t --help / -h : Shows help\n"
                      << "\t --add / -a <Thing to do between quotes> :\t\t Add a normally urgent "
                         "item to the todo list\n"
                      << "\t --add-urgent / -u <Thing to do between quotes> :\t\t Add an urgent "
                         "item to the todo list\n"
                      << "\t --add-not-so-urgent / -n <Thing to do between quotes> :\t\t Add a not "
                         "urgent item to the todo list\n"
                      << "\t --mark-as-done / -m <Task ID> :\t\t Mark the task whose ID is given "
                         "in parameter as done\n"
                      << "\t --purge / -p :\t\t Removes all tasks marked as done\n"
                      << "\t --start-task / -s <Task ID>:\t\t Starts task whose ID is given in "
                         "parameter\n"
                      << "\t --stop-current-task / -S:\t\t Stops task whose ID is given in "
                         "parameter and  displays the time you took to do it. Switch it to Done "
                         "state.\n\n"
                      << "\t\t Note that all the options above are mutually exclusive.\n"
                         "\t\t If no option is provided, just displays the list of items in the "
                         "TODO list with an ID that can be used to mark tasks as done with the "
                         "appropriate option, namely, "
                         "sorted by priority (urgents, normally urgent, "
                         "not urgent, done)"
                      << std::endl;
            return 0;
        } else if (contains<QString, 2>(Args::addArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc - 1, Q_FUNC_INFO, "Bad parameter count");
            taskToAdd = argv[++currentArgIndex];
            action = ProgramAction::Add;
            priority = TaskPriority::NormallyUrgent;
            Q_ASSERT_X(currentArgIndex == argc - 1, Q_FUNC_INFO, "Bad parameter count");
        } else if (contains<QString, 2>(Args::addUrgentArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc - 1, Q_FUNC_INFO, "Bad parameter count");
            taskToAdd = argv[++currentArgIndex];
            action = ProgramAction::Add;
            priority = TaskPriority::Urgent;
            Q_ASSERT_X(currentArgIndex == argc - 1, Q_FUNC_INFO, "Bad parameter count");
        } else if (contains<QString, 2>(Args::addNotSoUrgentArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc - 1, Q_FUNC_INFO, "Bad parameter count");
            taskToAdd = argv[++currentArgIndex];
            action = ProgramAction::Add;
            priority = TaskPriority::NotSoUrgent;
            Q_ASSERT_X(currentArgIndex == argc - 1, Q_FUNC_INFO, "Bad parameter count");
        } else if (contains<QString, 2>(Args::markAsDoneArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc - 1, Q_FUNC_INFO, "Bad parameter count");
            taskId = QString{argv[++currentArgIndex]}.toUInt();
            action = ProgramAction::MarkAsDone;
            Q_ASSERT_X(currentArgIndex == argc - 1, Q_FUNC_INFO, "Bad parameter count");

        } else if (contains<QString, 2>(Args::purgeArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc, Q_FUNC_INFO, "Bad parameter count");
            action = ProgramAction::Purge;
        } else if (contains<QString, 2>(Args::startTaskArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc, Q_FUNC_INFO, "Bad parameter count");
            taskId = QString{argv[++currentArgIndex]}.toUInt();
            action = ProgramAction::StartTask;
            Q_ASSERT_X(currentArgIndex == argc - 1, Q_FUNC_INFO, "Bad parameter count");
        } else if (contains<QString, 2>(Args::stopTaskArgs, currentArg)) {
            Q_ASSERT_X(currentArgIndex != argc, Q_FUNC_INFO, "Bad parameter count");
            action = ProgramAction::StopTask;
        }
    }

    QString dataFilePath = "/tmp/toto";
    QFile *file = nullptr;
    QStringList lines{};
    switch (action) {
    case ProgramAction::Add: {
        Task task{priority, taskToAdd};
        file = new QFile{dataFilePath};
        file->open(QFile::Append | QFile::WriteOnly);
        appendTask(file, task);
        file->flush();
        break;
    }
    case ProgramAction::Purge: {
        file = readFile(dataFilePath);
        file->open(QFile::ReadOnly);
        lines = readLines(file);
        file->close();
        QList<Task> tasks;

        file->open(QFile::WriteOnly | QFile::Truncate);

        for (auto line : lines) {
            tasks.append(Task{line, taskIdGenerator++});
        }
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->priority() == TaskPriority::Done) {
                tasks.erase(it);
            }
        }
        writeLines(file, tasks);
        break;
    }
    case ProgramAction::Display: {
        file = readFile(dataFilePath);
        file->open(QFile::ReadOnly);
        auto lines = readLines(file);
        QList<Task> tasks;
        for (auto line : lines) {
            tasks.append(Task{line, taskIdGenerator++});
        }

        display(tasks);

        break;
    }
    case ProgramAction::MarkAsDone: {
        file = readFile(dataFilePath);
        file->open(QFile::ReadOnly);
        lines = readLines(file);
        file->close();
        QList<Task> tasks;
        for (auto line : lines) {
            tasks.append(Task{line, taskIdGenerator++});
        }
        for (auto &task : tasks) {
            if (task.id() == taskId) {
                task.setPriority(TaskPriority::Done);
            }
        }
        file->open(QFile::WriteOnly | QFile::Truncate);
        writeLines(file, tasks);
        break;
    }
    case ProgramAction::StartTask: {
        startTask(taskId);
        break;
    }
    case ProgramAction::StopTask: {
        stopCurrentTask();
        break;
    }
    default: {
        std::cerr << "Unknown action" << std::endl;
    }
    }
}
