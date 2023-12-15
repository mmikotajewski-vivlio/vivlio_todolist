#ifndef TASK_H
#define TASK_H

#include <QString>
#include <iostream>

#include "TaskPriority.h"

class Task
{
public:
    Task(const TaskPriority &priority, const QString &description, const uint32_t id = 0);
    Task(const QString &line, const uint32_t id);

    TaskPriority priority() const { return m_priority; }

    friend std::ostream &operator<<(std::ostream &stream, const Task &task);
    friend QTextStream &operator<<(QTextStream &stream, const Task &task);

private:
    TaskPriority m_priority;
    QString m_description;
    uint32_t m_id;
};

std::ostream &operator<<(std::ostream &stream, const Task &task);
QTextStream &operator<<(QTextStream &stream, const Task &task);

#endif // TASK_H
