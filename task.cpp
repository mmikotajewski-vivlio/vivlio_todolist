#include "task.h"

Task::Task(const TaskPriority &priority, const QString &description, const uint32_t id)
    : m_priority(priority)
    , m_description(description.trimmed())
    , m_id(id)
{}

Task::Task(const QString &line, const uint32_t id)
    : m_id(id)
{
    auto priority = static_cast<TaskPriority>(line.split(" ").first().toInt());
    auto firstSpaceIndex = line.indexOf(" ");
    Q_ASSERT(firstSpaceIndex > 0);
    auto description = line;
    description.remove(0, firstSpaceIndex + 1);
    m_priority = priority;
    m_description = description;
}

std::ostream &operator<<(std::ostream &stream, const Task &task)
{
    stream << "ID: " << task.m_id << "\tDescription:\t" << task.m_description.toStdString();
    return stream;
}

QTextStream &operator<<(QTextStream &stream, const Task &task)
{
    stream << task.m_priority << " " << task.m_description;
    stream.flush();
    return stream;
}
