#ifndef TASKPRIORITY_H
#define TASKPRIORITY_H

#include <QTextStream>
#include <iostream>

enum class TaskPriority {
    Unknown,
    Done,
    NotSoUrgent,
    NormallyUrgent,
    Urgent,
};

std::ostream &operator<<(std::ostream &stream, const TaskPriority &priority);
QTextStream &operator<<(QTextStream &stream, const TaskPriority &priority);
#endif // TASKPRIORITY_H
