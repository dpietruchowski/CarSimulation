#ifndef NEWWORLDDIALOG_H
#define NEWWORLDDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include "probabilityvalidator.h"
#include "genetic/geneticalgorithm.h"

namespace Ui {
class NewWorldDialog;
}

class NewWorldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewWorldDialog(QWidget *parent = 0);
    void setDefault();
    void showValues();
    const GeneticParameters& geneticParameters() const;
    size_t bufferSize() const;
    double maxWorldTime() const;
    b2Vec2 worldSize() const;
    b2Vec2 gravity() const;
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
