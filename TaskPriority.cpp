#include "TaskPriority.h"

std::ostream &operator<<(std::ostream &stream, const TaskPriority &priority)
{
    stream << static_cast<uint32_t>(priority);
    return stream;
}
QTextStream &operator<<(QTextStream &stream, const TaskPriority &priority)
{
    auto value = QString::number(static_cast<uint32_t>(priority));
    stream << value;
    stream.flush();
    return stream;
}
