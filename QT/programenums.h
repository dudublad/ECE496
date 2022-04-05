#ifndef PROGRAMENUMS_H
#define PROGRAMENUMS_H

#include <QStringList>

typedef enum {
    Int,
    Double,
    Choice
} InputType;

typedef struct InputInfo
{
    InputType type;
    QString label;
    double maximum;
    double minimum;
    QStringList choices;
} InputInfo;


#endif // PROGRAMENUMS_H
