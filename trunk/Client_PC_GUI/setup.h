#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QFormlayout>
#include <QRadioButton>
#include <QComboBox>
#include <QFrame>
#include <QVBoxLayout>

class SetupWindows : public QDialog
{
    Q_OBJECT

    public:
        SetupWindows(QWidget *parent);

    private:
        QDialogButtonBox * boutons;

        QTabWidget * setupOnglets;
        QWidget * onglet1;
        QWidget * onglet2;

        QLineEdit *netbiosValue;
        QLineEdit *adressValue;
        QLineEdit *dns1Value;
        QLineEdit *dns2Value;
        QLineEdit *gatewayValue;
        QLineEdit *maskValue;


        QFrame* type;
        QRadioButton *typeAdhoc;
        QRadioButton *typeInfrastructure;
        QLineEdit *nameValue;
        QLineEdit *dhcpValue;
        QComboBox *securityValue;
    
    signals:

    
    public slots:
    
};

#endif // SETUP_H
