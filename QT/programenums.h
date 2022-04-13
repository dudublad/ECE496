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

static constexpr unsigned int SIGNAL_GENERATED = 1;
static constexpr unsigned int EFFECT_ADDED_TYPE = 2;
static constexpr unsigned int PLAY_BUTTON_PRESSED = 3;


#endif // PROGRAMENUMS_H
