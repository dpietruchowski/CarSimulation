#include "newworlddialog.h"
#include "ui_newworlddialog.h"
#include <assert.h>
#include <QDebug>
#include <QIntValidator>
#include <vector>
#include <cmath>

NewWorldDialog::NewWorldDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::NewWorldDialog),
    locale(QLocale::Polish, QLocale::Poland), pValidator(this, locale)
{
    ui->setupUi(this);

    ui->popSizeEdit->setValidator(new QIntValidator(0, 500,
                                                    ui->popSizeEdit));
    ui->gravityXEdit->setValidator(new QIntValidator(-150, 150,
                                                     ui->gravityXEdit));
    ui->gravityYEdit->setValidator(new QIntValidator(-150, 150,
                                                     ui->gravityYEdit));
    ui->worldWidthEdit->setValidator(new QIntValidator(0, 3000,
                                                       ui->worldWidthEdit));
    ui->worldHeightEdit->setValidator(new QIntValidator(0, 300,
                                                        ui->worldHeightEdit));
    ui->bufferEdit->setValidator(new QIntValidator(0, 300,
                                                   ui->bufferEdit));
    ui->timeEdit->setValidator(new QIntValidator(0, 5400 /* 1h 30 min */,
                                                 ui->timeEdit));

    setGroupValidator(ui->crossoverBox);
    setGroupValidator(ui->mutationBox);
}

void NewWorldDialog::setDefault()
{
    ui->retranslateUi(this);
}

void NewWorldDialog::showValues()
{
    showValues(this);
}

GeneticParameters NewWorldDialog::geneticParameters() const
{
    const QString& populationSize = ui->popSizeEdit->text();
    const QString& bodyMutation = ui->bodyMutedit->text();
    const QString& wheelMutation = ui->wheelMutedit->text();
    const QString& onePointCrossover = ui->onePointEdit->text();
    const QString& twoPointCrossover = ui->twoPointEdit->text();
    const QString& wheelCrossover = ui->wheelEdit->text();

    return {
                locale.toInt(populationSize),
                RANK_ROULETTESELECTION,
                {
                    {
                        locale.toDouble(bodyMutation),
                        locale.toDouble(wheelMutation)
                    },
                    {
                        locale.toDouble(onePointCrossover),
                        locale.toDouble(twoPointCrossover),
                        locale.toDouble(wheelCrossover),
                    }
                }
            };
}

size_t NewWorldDialog::bufferSize() const
{
    return static_cast<size_t>(locale.toInt(ui->bufferEdit->text()));
}

double NewWorldDialog::maxWorldTime() const
{
    return locale.toDouble(ui->timeEdit->text());
}

b2Vec2 NewWorldDialog::worldSize() const
{
    const QString& worldWidth = ui->worldWidthEdit->text();
    const QString& worldHeight = ui->worldHeightEdit->text();
    return b2Vec2(static_cast<float32>(locale.toDouble(worldWidth)),
                  static_cast<float32>(locale.toDouble(worldHeight)));
}

b2Vec2 NewWorldDialog::gravity() const
{
    const QString& gravityXText = ui->gravityXEdit->text();
    const QString& gravityYText = ui->gravityYEdit->text();
    return b2Vec2(static_cast<float32>(locale.toDouble(gravityXText)),
                  static_cast<float32>(locale.toDouble(gravityYText)));
}

void NewWorldDialog::showValues(QObject* obj)
{
    for(const auto& child : obj->children())
    {
        if (qobject_cast<QLineEdit*>(child))
        {
            const QString& text = qobject_cast<QLineEdit*>(child)->text();
            qDebug() << locale.toDouble(text) << " text: " << text;
        }
        showValues(child);
    }
}

NewWorldDialog::~NewWorldDialog()
{
    delete ui;
}

void NewWorldDialog::setGroupValidator(QGroupBox *box)
{
    for(const auto& child : box->children())
    {
        if (qobject_cast<QLineEdit*>(child))
        {
            qobject_cast<QLineEdit*>(child)->setValidator(&pValidator);
            connect(child, SIGNAL(textChanged(QString)),
                    this, SLOT(validate(QString)));
        }
    }
}

void NewWorldDialog::validate(QString inputText)
{
    auto toDouble = [this](const QLineEdit* le) -> double
    {
        bool ok;
        QString text = le->text();
        if(text.isEmpty())
            text = "0";
        double ret = locale.toDouble(text, &ok);
        assert(ok);
        return ret;
    };

    qDebug() << "DIALOG VALIDATE ";
    QLineEdit* sender = qobject_cast<QLineEdit*> (QObject::sender());
    assert(sender);
    QObject *parent = sender->parent();
    std::vector<QLineEdit*> tab;
    for(const auto& child : parent->children())
    {
        QLineEdit* iterChild = qobject_cast<QLineEdit*> (child);
        if (iterChild)
        {
            tab.push_back(iterChild);
        }
    }

    const int nChildren = tab.size();
    double sum = 0;
    int edited = 0;
    for(int i = 0; i < nChildren; ++i)
    {
        double value;
        if(sender == tab[i])
        {
            edited = i + 1;
            value = locale.toDouble(inputText);
        } else
            value = toDouble(tab[i]);

        qDebug() << "wprowadzone: " << value;
        sum += value;
    }
    edited %= nChildren;
    qDebug() << "reszta: " << sum;
    while(std::abs(sum - 1.0) > 0.00000001)
    {
        double value = toDouble(tab[edited]);
        sum -= value;
        double newValue = (sum - 1.0) > 0 ?
                    0 :
                    std::floor((1.0 - sum)*1000)/1000;
        if(newValue == value)
        {
            ++edited;
            edited %= nChildren;
            sum += value;
            continue;
        }
        tab[edited]->setText(locale.toString(newValue));
        break;
    }
}
