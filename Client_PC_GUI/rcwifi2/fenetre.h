#ifndef HEADER_FENETRE
#define HEADER_FENETRE

#include <QApplication>
#include <QMenuBar>
#include <QKeyEvent>
#include <QMainWindow>
#include <QAction>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QPushButton>
#include <QTcpSocket>
#include "setup.h"

class MainWindows : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindows();
        void keyPressEvent ( QKeyEvent * event );
        void keyReleaseEvent( QKeyEvent * event );
    private:

        QMenu *menuFichier;
        QMenu *menuAffichage;
        QMenu *menuAide;
        QAction *setup;
        QAction *infos;
        QAction *quitter;
        QAction *about;

        QDockWidget *dock;
        QWidget *dockContent;
        QGroupBox *alim;
            QLabel *battery;
            QProgressBar *batteryBar;
        QGroupBox *ip;
            QLabel *netbios;
            QLabel *netbiosValue;
            QLabel *adress;
            QLabel *adressValue;
            QLabel *dns1;
            QLabel *dns1Value;
            QLabel *dns2;
            QLabel *dns2Value;
            QLabel *gateway;
            QLabel *gatewayValue;
            QLabel *mask;
            QLabel *maskValue;
        QGroupBox *wifi;
            QLabel *type;
            QLabel *typeValue;
            QLabel *name;
            QLabel *nameValue;
            QLabel *dhcp;
            QLabel *dhcpValue;
            QLabel *security;
            QLabel *securityValue;
        QWidget *zoneCentrale;
            QPushButton* avant;
            QPushButton* stop;
            QPushButton* gauche;
            QPushButton* droite;
            QPushButton* neutre;

       QTcpSocket * socket;
    public slots:
            void ouvrirSetup();
            void envoyerGauche();
            void envoyerDroite();
            void envoyerNeutre();
            void envoyerAvancer();
            void envoyerStop();


};



#endif
