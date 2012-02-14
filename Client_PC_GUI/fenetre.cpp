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
    arriere= new QPushButton( QString::fromUtf8("\u25BC") );
    gauche= new QPushButton( QString::fromUtf8("\u25C4") );
    droite = new QPushButton( QString::fromUtf8("\u25BA") );
    QGridLayout* telec=new QGridLayout;
        telec->addWidget(avant,1,2);
        telec->addWidget(gauche,2,1);
        telec->addWidget(droite,2,3);
        telec->addWidget(arriere,3,2);
        avant->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        arriere->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        gauche->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        droite->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    zoneCentrale->setLayout(telec);


    /* GESTION DE LA BARRE D'ETAT */


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
    connect(gauche,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(droite,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(avant,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(arriere,SIGNAL(clicked()),qApp,SLOT(quit()));


}

/* GESTION DU CLAVIER */
void MainWindows::keyPressEvent ( QKeyEvent * event )
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

void MainWindows::keyReleaseEvent( QKeyEvent * event )
{


}

void MainWindows::ouvrirSetup()
{
    SetupWindows *fenetreSetup=new SetupWindows(this);
    fenetreSetup->exec();
}

