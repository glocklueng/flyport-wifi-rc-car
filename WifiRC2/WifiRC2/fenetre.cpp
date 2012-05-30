#include "fenetre.h"

MainWindows::MainWindows() : QWidget()
{
    setWindowIcon(QIcon("logo.png"));

        /* PRECONFIGURATION WIFI */
    socket = new QTcpSocket(this);
    socket->abort();

       /* GESTION DU DOCK */
    dock=new QFrame(this);
    dock->setFrameShape(QFrame::StyledPanel);

    reseau=new QGroupBox("Réseau");
        connexion=new QPushButton("Connexion");
        deconnexion=new QPushButton("Déconnexion");
        etat=new QLabel("État");
        etatValue=new QLabel("<b>Désactivé</b>");
            etatValue->setAlignment(Qt::AlignHCenter);
        ip = new QLabel("IP");
        ipValue = new QLineEdit("192.168.1.115");
            ipValue->setAlignment(Qt::AlignHCenter);
        port = new QLabel("Port");
        portValue = new QLineEdit("2050");
            portValue->setAlignment(Qt::AlignHCenter);

    QGridLayout *reseauLayout = new QGridLayout;
        reseauLayout->addWidget(connexion,1,2);
        reseauLayout->addWidget(deconnexion,1,3);
        reseauLayout->addWidget(etat,2,1);
        reseauLayout->addWidget(etatValue,2,2,1,2);
        reseauLayout->addWidget(ip,3,1);
        reseauLayout->addWidget(ipValue,3,2,1,2);
        reseauLayout->addWidget(port,4,1);
        reseauLayout->addWidget(portValue,4,2,1,2);
    reseau->setLayout(reseauLayout);

    eclairage=new QGroupBox("Phares");
        allumage=new QPushButton("Allumer / Eteindre");

        QVBoxLayout *eclairageLayout = new QVBoxLayout;
            eclairageLayout->addWidget(allumage);
        eclairage->setLayout(eclairageLayout);

    moteur=new QGroupBox("Puissance moteur");
        avantL=new QLabel("Avant");
            avantL->setAlignment(Qt::AlignHCenter);
        avantS=new QSlider();
            avantS->setMinimum(35);
            avantS->setMaximum(100);
            avantS->setValue(100);
        avantV=new QLabel("100");
            avantV->setAlignment(Qt::AlignCenter);
        arriereL=new QLabel("Arrière");
            arriereL->setAlignment(Qt::AlignHCenter);
        arriereS=new QSlider();
            arriereS->setMinimum(35);
            arriereS->setMaximum(100);
            arriereS->setValue(100);
        arriereV=new QLabel("100");
            arriereV->setAlignment(Qt::AlignCenter);
        QGridLayout* moteurLayout=new QGridLayout;
            moteurLayout->addWidget(avantL,1,1,1,2);
            moteurLayout->addWidget(avantS,2,1);
            moteurLayout->addWidget(avantV,2,2);
            moteurLayout->addWidget(arriereL,1,3,1,2);
            moteurLayout->addWidget(arriereS,2,3);
            moteurLayout->addWidget(arriereV,2,4);
        moteur->setLayout(moteurLayout);

    direction=new QGroupBox("Direction");
        intensiteL=new QLabel("Intensite de la direction");
        intensiteS=new QSlider(Qt::Horizontal);
            intensiteS->setMinimum(1);
            intensiteS->setMaximum(40);
            intensiteS->setValue(40);
        intensiteV=new QLabel("100");
            intensiteV->setMinimumWidth(21);
            intensiteV->setAlignment(Qt::AlignHCenter);
        neutreL=new QLabel("Calibrage de la direction");
        neutreS=new QSlider(Qt::Horizontal);
            neutreS->setMinimum(-50);
            neutreS->setMaximum(50);
            neutreS->setValue(0);
        neutreV=new QLabel("0");
            neutreV->setMinimumWidth(21);
            neutreV->setAlignment(Qt::AlignHCenter);
        QGridLayout* directionLayout=new QGridLayout;
            directionLayout->addWidget(intensiteL,1,1,1,2);
            directionLayout->addWidget(intensiteS,2,1);
            directionLayout->addWidget(intensiteV,2,2);
            directionLayout->addWidget(neutreL,3,1,1,2);
            directionLayout->addWidget(neutreS,4,1);
            directionLayout->addWidget(neutreV,4,2);
        direction->setLayout(directionLayout);

    infos= new QGroupBox("Informations");
        commandes = new QPushButton("Commandes");
        projet = new QPushButton("A propos de WiFiRC");
        QVBoxLayout* infosLayout=new QVBoxLayout;
            infosLayout->addWidget(commandes);
            infosLayout->addWidget(projet);
        infos->setLayout(infosLayout);

    QVBoxLayout *dockLayout=new QVBoxLayout;
        dockLayout->addWidget(reseau);
        dockLayout->addWidget(eclairage);
        dockLayout->addWidget(moteur);
        dockLayout->addWidget(direction);
        dockLayout->addWidget(infos);
    dock->setLayout(dockLayout);


        /* GESTION DE LA TELECOMMANDE */
    avant= new QPushButton( QString::fromUtf8("\u25B2"));
    stop= new QPushButton( QString::fromUtf8("\u25CF"));
    gauche= new QPushButton( QString::fromUtf8("\u25C4") );
    droite = new QPushButton( QString::fromUtf8("\u25BA") );
    arriere = new QPushButton( QString::fromUtf8("\u25BC"));
    QGridLayout* telec=new QGridLayout;
        telec->addWidget(avant,1,2);
        telec->addWidget(gauche,2,1);
        telec->addWidget(droite,2,3);
        telec->addWidget(stop,2,2);
        telec->addWidget(arriere,3,2);
        avant->setMinimumSize(180,180);
        avant->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        stop->setMinimumSize(180,180);
        stop->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        gauche->setMinimumSize(180,180);
        gauche->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        droite->setMinimumSize(180,180);
        droite->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        arriere->setMinimumSize(180,180);
        arriere->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    /*  */
    dock->setMaximumWidth(350);
    QHBoxLayout* main = new QHBoxLayout(this);
        main->addLayout(telec);
        main->addWidget(dock);
    setLayout(main);

    /* GESTION DES SINGUAX/SLOTS */
    connect(neutreS,SIGNAL(valueChanged(int)),neutreV,SLOT(setNum(int)));
    connect(intensiteS,SIGNAL(valueChanged(int)),intensiteV,SLOT(setNum(int)));
    connect(avantS,SIGNAL(valueChanged(int)),avantV,SLOT(setNum(int)));
    connect(arriereS,SIGNAL(valueChanged(int)),arriereV,SLOT(setNum(int)));
    connect(gauche,SIGNAL(clicked()),this,SLOT(envoyerGauche()));
    connect(droite,SIGNAL(clicked()),this,SLOT(envoyerDroite()));
    connect(avant,SIGNAL(clicked()),this,SLOT(envoyerAvancer()));
    connect(stop,SIGNAL(clicked()),this,SLOT(envoyerStop()));
    connect(arriere,SIGNAL(clicked()),this,SLOT(envoyerReculer()));
    connect(connexion, SIGNAL(clicked()), this, SLOT(demanderConnexion()));
    connect(deconnexion, SIGNAL(clicked()), this, SLOT(demanderDeconnexion()));
    connect(commandes, SIGNAL(clicked()), this, SLOT(ouvrirCommandes()));
    connect(allumage, SIGNAL(clicked()), this, SLOT(envoyerPhare()));
}

    /* GESTION DU CLAVIER */
void MainWindows::keyPressEvent ( QKeyEvent * event )
{
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
            case Qt::Key_K :
                gauche->click();
                break;
            case Qt::Key_O :
                avant->click();
                break;
            case Qt::Key_M :
                droite->click();
                break;
            case Qt::Key_L :
                arriere->click();
                break;
            default:
            ;
        }
    }
}

void MainWindows::keyReleaseEvent( QKeyEvent * event )
{
    if (event->isAutoRepeat() == false)
    {
        switch(event->key())
        {
            case Qt::Key_K :
                envoyerNeutre();
                break;
            case Qt::Key_O :
                stop->click();
                break;
            case Qt::Key_M :
                envoyerNeutre();
                break;
            case Qt::Key_L :
                stop->click();
                break;
            default:
            ;
        }
    }

}

            /* GESTION DES SLOTS */

void MainWindows::ouvrirCommandes()
{
    QMessageBox::information(this, "Commandes", "La télécommande fonctionne avec le clavier en utilisant les touches ci-dessous :\n\nO:\tAvancer\nL:\tReculer\nK:\tGauche\nM:\tDroite\n");
}



void MainWindows::demanderConnexion()
{
    socket->connectToHost(ipValue->text().toStdString().c_str(), portValue->text().toInt());
    etatValue->setText("<b>Activé</b>");
}

void MainWindows::demanderDeconnexion()
{
    socket->close();
    etatValue->setText("<b>Désactivé</b>");
}


void MainWindows::envoyerGauche()
{
    QString envoi;
    int valeur = 400 - 10 *(intensiteS->value());
    envoi = "t"+QString::number(valeur)+ "\r\n";
    socket->write(envoi.toStdString().c_str());
}

void MainWindows::envoyerDroite()
{
    QString envoi;
    int valeur = 600 + 10 *(intensiteS->value());
    envoi = "t"+QString::number(valeur) + "\r\n";
    socket->write(envoi.toStdString().c_str());
}

void MainWindows::envoyerReculer()
{
    QString envoi = "r" + QString::number(arriereS->value())+ "\r\n";
    socket->write(envoi.toStdString().c_str());
}

void MainWindows::envoyerAvancer()
{
    QString envoi = "a" + QString::number(avantS->value()) + "\r\n";
    socket->write(envoi.toStdString().c_str());
}

void MainWindows::envoyerStop()
{
    socket->write("s\r\n");
}

void MainWindows::envoyerPhare()
{
    socket->write("p\r\n");
}

void MainWindows::envoyerNeutre()
{
    QString envoi;
    qint16 valeur;
    valeur = 526 + neutreS->value();
    envoi = "t"+QString::number(valeur)+ "\r\n";
    socket->write(envoi.toStdString().c_str());
}

