#include "probabilityvalidator.h"
#include <QDebug>

ProbabilityValidator::ProbabilityValidator(QObject *parent,
                                           const QLocale &locale):
    QDoubleValidator(0, 1, 3, parent)
{
    setLocale(locale);
}

QValidator::State ProbabilityValidator::validate(QString &s, int& /* i */) const
{
    if (s.isEmpty() || s == "-") {
        return QValidator::Intermediate;
    }
    QChar decimalPoint = locale().decimalPoint();

    if(s.indexOf(decimalPoint) != -1) {
        int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

        if (charsAfterPoint > decimals()) {
            return QValidator::Invalid;
        }
    }

    bool ok;
    double d = locale().toDouble(s, &ok);

    if (ok && d >= bottom() && d <= top()) {
        return QValidator::Acceptable;
    }
    return QValidator::Invalid;
}
