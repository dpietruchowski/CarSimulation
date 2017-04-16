#ifndef PROBABILITYVALIDATOR_H
#define PROBABILITYVALIDATOR_H

#include <QDoubleValidator>


class ProbabilityValidator : public QDoubleValidator
{
public:
    ProbabilityValidator(QObject *parent, const QLocale &locale);
    QValidator::State validate(QString &s, int &i) const;
};

#endif // PROBABILITYVALIDATOR_H
