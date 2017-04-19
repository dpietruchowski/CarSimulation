#ifndef PROBABILITYVALIDATOR_H
#define PROBABILITYVALIDATOR_H

#include <QDoubleValidator>

///
/// \brief The ProbabilityValidator class is used to validate input string in
/// QLineEdit that should contains double that is within 0 - 1 range and is in
/// the correct format.
///
class ProbabilityValidator : public QDoubleValidator
{
public:
    ///
    /// \brief A ProbabilityValidator constructor.
    /// \param parent Parent for this widget
    /// \param locale The locale that will be used for the validator
    ///
    ProbabilityValidator(QObject *parent, const QLocale &locale);

    ///
    /// \brief Reimplemented from QDoubleValidator::validate(). Returns
    /// QValidator::Acceptable if the string input contains a double that is within
    /// 0 - 1 range and is in the correct format. Returns QValidator::Intermediate
    /// if input is empty. Otherwise returns QValidator::Invalid.
    /// \param s Input string
    /// \param i The position of cursor.
    /// \return QValidator::Acceptable if the string input contains a double that is within
    /// 0 - 1 range and is in the correct format or QValidator::Intermediate
    /// if input is empty. Otherwise returns QValidator::Invalid.
    ///
    QValidator::State validate(QString &s, int &i) const;
};

#endif // PROBABILITYVALIDATOR_H
