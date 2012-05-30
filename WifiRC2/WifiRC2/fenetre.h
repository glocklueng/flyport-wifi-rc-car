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
#include <QMessageBox>
#include <QSlider>
#include <QLineEdit>

class MainWindows : public QWidget
{
    Q_OBJECT

    public:
        MainWindows();
        void keyPressEvent ( QKeyEvent * event );
        void keyReleaseEvent( QKeyEvent * event );
    private:

        QFrame *dock;
        QGroupBox *reseau;
            QPushButton* connexion;
            QPushButton* deconnexion;
            QLabel *etat;
            QLabel *etatValue;
            QLabel *ip;
            QLineEdit *ipValue;
            QLabel *port;
            QLineEdit *portValue;
       QGroupBox *eclairage;            // phares
              QPushButton* allumage;
        QGroupBox *moteur;
            QLabel *avantL;
                QSlider *avantS;
                QLabel *avantV;
            QLabel *arriereL;
                QSlider *arriereS;
                QLabel *arriereV;
        QGroupBox *direction;
            QLabel *intensiteL;
                QSlider *intensiteS;
                QLabel *intensiteV;
            QLabel *neutreL;
                QSlider *neutreS;
                QLabel *neutreV;
        QGroupBox *infos;
            QPushButton * commandes;
            QPushButton * projet;


        QPushButton* avant;
        QPushButton* stop;
        QPushButton* gauche;
        QPushButton* droite;
        QPushButton* arriere;

        QTcpSocket * socket;

    public slots:
            void envoyerGauche();
            void envoyerDroite();
            void envoyerReculer();
            void envoyerAvancer();
            void envoyerStop();
            void envoyerNeutre();
            void demanderConnexion();
            void demanderDeconnexion();
            void ouvrirCommandes();
            void envoyerPhare();


};



#endif
