#ifndef NEWWORLDDIALOG_H
#define NEWWORLDDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include "probabilityvalidator.h"
#include "genetic/geneticalgorithm.h"

namespace Ui {
class NewWorldDialog;
}

///
/// \brief The NewWorldDialog class represents dialog with QLineEdit entries to
/// set parameters for new world.
///
class NewWorldDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief A NewWorldDialog constructor.
    /// \param parent Parent for this widget
    ///
    explicit NewWorldDialog(QWidget *parent = 0);

    ///
    /// \brief Sets default locales for entries.
    ///
    void setDefault();

    ///
    /// \brief Shows values in all entries.
    ///
    void showValues();

    ///
    /// \brief Returns genetic parameters.
    /// \return Genetic parameters
    ///
    GeneticParameters geneticParameters() const;

    ///
    /// \brief Returns size of buffer.
    /// \return The size of buffer
    ///
    size_t bufferSize() const;

    ///
    /// \brief Returns max world's time.
    /// \return Max world's time
    ///
    double maxWorldTime() const;

    ///
    /// \brief Returns the size of the world.
    /// \return The size of the world
    ///
    b2Vec2 worldSize() const;

    ///
    /// \brief Returns value of the gravity for the world.
    /// \return Value of the gravity for the world
    ///
    b2Vec2 gravity() const;

    ///
    /// \brief A NewWorldDialog destructor.
    ///
    ~NewWorldDialog();

private:
    void showValues(QObject *obj);
    void setGroupValidator(QGroupBox* box);

private slots:
    void validate(QString string);

private:
    Ui::NewWorldDialog *ui;
    QLocale locale;
    ProbabilityValidator pValidator;
};

#endif // NEWWORLDDIALOG_H
