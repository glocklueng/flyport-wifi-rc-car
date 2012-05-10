#include "fenetre.h"

MainWindows::MainWindows() : QMainWindow()
{
    setWindowIcon(QIcon("logo.png"));

       /* GESTION DU DOCK INFOS */
    dock=new QDockWidget("Informations",this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dockContent= new QWidget;
    dock->setWidget(dockContent);


    alim=new QGroupBox("Alimentation");
        battery=new QLabel("Batterie");
        batteryBar=new QProgressBar;
            batteryBar->setValue(50);
            batteryBar->setMinimumWidth(130);
    QHBoxLayout *batteryLayout=new QHBoxLayout;
        batteryLayout->addWidget(battery);
        batteryLayout->addWidget(batteryBar);
    alim->setLayout(batteryLayout);

    ip=new QGroupBox("Paramètres IP");
        netbios=new QLabel("Groupe de travail");
        netbiosValue=new QLabel("WORKGROUP");
        adress=new QLabel("Adresse IP");
        adressValue=new QLabel("xxx.xxx.xxx.xxx");
        dns1=new QLabel("Serveur DNS primiaire");
        dns1Value=new QLabel("xxx.xxx.xxx.xxx");
        dns2=new QLabel("Serveur DNS secondaire");
        dns2Value=new QLabel("xxx.xxx.xxx.xxx");
        gateway=new QLabel("Passerelle par défaut");
        gatewayValue=new QLabel("xxx.xxx.xxx.xxx");
        mask= new QLabel("Masque de sous réseau");
        maskValue=new QLabel("xxx.xxx.xxx.xxx");
    QGridLayout*ipLayout=new QGridLayout;
        ipLayout->addWidget(netbios,1,1);
        ipLayout->addWidget(netbiosValue,1,2);
        ipLayout->addWidget(adress,2,1);
        ipLayout->addWidget(adressValue,2,2);
        ipLayout->addWidget(dns1,3,1);
        ipLayout->addWidget(dns1Value,3,2);
        ipLayout->addWidget(dns2,4,1);
        ipLayout->addWidget(dns2Value,4,2);
        ipLayout->addWidget(gateway,5,1);
        ipLayout->addWidget(gatewayValue,5,2);
        ipLayout->addWidget(mask,6,1);
        ipLayout->addWidget(maskValue,6,2);
    ip->setLayout(ipLayout);

    wifi=new QGroupBox("Paramètres WIFI");
        type=new QLabel("Type de réseau");
        typeValue=new QLabel("Infrastructure");
        name=new QLabel("Nom du réseau (S.S.I.D)");
        nameValue=new QLabel("FlyPort");
        dhcp=new QLabel("D.H.C.P");
        dhcpValue=new QLabel("Activé");
        security=new QLabel("Sécurité");
        securityValue=new QLabel("Aucune");
    QGridLayout*wifiLayout=new QGridLayout;
        wifiLayout->addWidget(type,1,1);
        wifiLayout->addWidget(typeValue,1,2);
        wifiLayout->addWidget(name,2,1);
        wifiLayout->addWidget(nameValue,2,2);
        wifiLayout->addWidget(dhcp,3,1);
        wifiLayout->addWidget(dhcpValue,3,2);
        wifiLayout->addWidget(security,4,1);
        wifiLayout->addWidget(securityValue,4,2);
    wifi->setLayout(wifiLayout);


    QVBoxLayout *dockLayout=new QVBoxLayout;
        dockLayout->addWidget(alim);
        dockLayout->addWidget(ip);
        dockLayout->addWidget(wifi);
    dockContent->setLayout(dockLayout);


    /* GESTION DE LA ZONE PRINCIPALE */
    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);
    avant= new QPushButton( QString::fromUtf8("\u25B2"));
    stop= new QPushButton( "Stop");
    gauche= new QPushButton( QString::fromUtf8("\u25C4") );
    droite = new QPushButton( QString::fromUtf8("\u25BA") );
    neutre = new QPushButton( "Neutre");
    QGridLayout* telec=new QGridLayout;
        telec->addWidget(avant,1,2);
        telec->addWidget(gauche,2,1);
        telec->addWidget(droite,2,3);
        telec->addWidget(stop,2,2);
        telec->addWidget(neutre,3,2);
        avant->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        stop->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        gauche->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        droite->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        neutre->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    zoneCentrale->setLayout(telec);


    /* GESTION RESEAU */
    socket = new QTcpSocket(this);
    socket->abort();
    socket->connectToHost("192.168.1.115", 2050);
    socket->write("connecte");


    /*  GESTION DES MENUS */
    menuFichier = menuBar()->addMenu("&Fichier");
    menuAffichage = menuBar()->addMenu("&Afficher");
    menuAide = menuBar()->addMenu("&?");


    /* GESTION DES ACTIONS */
    setup= menuFichier->addAction("&Réglages");
        setup->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    infos = dock->toggleViewAction();
        infos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
        menuAffichage->addAction(infos);
    quitter = menuFichier->addAction("&Quitter");
        quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    about = menuAide->addAction("&A propos de WifiRC");
        about->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));



    /* GESTION DES SINGUAX/SLOTS */
    connect(quitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(setup,SIGNAL(triggered()),this,SLOT(ouvrirSetup()));
    connect(gauche,SIGNAL(clicked()),this,SLOT(envoyerGauche()));
    //connect(gauche,SIGNAL(released()),this,SLOT(envoyerNeutre()));
    connect(droite,SIGNAL(clicked()),this,SLOT(envoyerDroite()));
    connect(avant,SIGNAL(clicked()),this,SLOT(envoyerAvancer()));
    connect(stop,SIGNAL(clicked()),this,SLOT(envoyerStop()));
    connect(neutre,SIGNAL(clicked()),this,SLOT(envoyerNeutre()));



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
                stop->click();
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
                neutre->click();
                break;
            case Qt::Key_O :
                stop->click();
                break;
            case Qt::Key_M :
                neutre->click();
                break;
            case Qt::Key_L :
                stop->click();
                break;
            default:
            ;
        }
    }

}

void MainWindows::ouvrirSetup()
{
    SetupWindows *fenetreSetup=new SetupWindows(this);
    //socket->write("g");
    fenetreSetup->exec();
    //socket->write("g");
}

void MainWindows::envoyerGauche()
{
    socket->write("g");
    //quitter->trigger();
}

void MainWindows::envoyerDroite()
{
    socket->write("d");
}

void MainWindows::envoyerNeutre()
{
    socket->write("|");
}

void MainWindows::envoyerAvancer()
{
    socket->write("a50");
}

void MainWindows::envoyerStop()
{
    socket->write("s");
}
