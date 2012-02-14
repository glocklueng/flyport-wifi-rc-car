#include "setup.h"

SetupWindows::SetupWindows(QWidget * parent = 0) : QDialog(parent)
{
    boutons= new QDialogButtonBox(QDialogButtonBox::Ok |QDialogButtonBox::Cancel, Qt::Horizontal, 0);

    QVBoxLayout* setupLayout=new QVBoxLayout;
    setupOnglets = new QTabWidget;

    onglet1 = new QWidget;
    netbiosValue= new QLineEdit;
    adressValue=new QLineEdit;
    dns1Value=new QLineEdit;
    dns2Value=new QLineEdit;
    gatewayValue=new QLineEdit;
    maskValue=new QLineEdit;

    QFormLayout* onglet1Layout=new QFormLayout;
    onglet1Layout->addRow("Groupe de travail", netbiosValue);
    onglet1Layout->addRow("Adresse I.P", adressValue);
    onglet1Layout->addRow("D.N.S Primaire", dns1Value);
    onglet1Layout->addRow("D.N.S Secondaire", dns2Value);
    onglet1Layout->addRow("Passerelle par défaut", gatewayValue);
    onglet1Layout->addRow("Masque de sous réseau", maskValue);
    onglet1->setLayout(onglet1Layout);


    onglet2 = new QWidget;
    type=new QFrame;
    typeAdhoc = new QRadioButton("Adhoc");
    typeInfrastructure= new QRadioButton("Infrastructure");
        QVBoxLayout* typeLayout = new QVBoxLayout(this);
            typeLayout->addWidget(typeAdhoc);
            typeLayout->addWidget(typeInfrastructure);
        type->setLayout(typeLayout);
    nameValue = new QLineEdit;
    dhcpValue = new QLineEdit;
    securityValue=new QComboBox;
    securityValue->addItem("Aucune");
    securityValue->addItem("WEP");
    securityValue->addItem("WPA-PSK");
    securityValue->addItem("WPA2-PSK");


    QFormLayout* onglet2Layout=new QFormLayout;
    onglet2Layout->addRow("Type de réseau",type);
    onglet2Layout->addRow("Nom du réseau (S.S.I.D)",nameValue);
    onglet2Layout->addRow("Serveur DHCP", dhcpValue);
    onglet2Layout->addRow("Type de securité", securityValue);
    onglet2->setLayout(onglet2Layout);

    setupOnglets->addTab(onglet1, "Paramètres I.P");
    setupOnglets->addTab(onglet2, "Paramètres Wifi");

    setupLayout->addWidget(setupOnglets);
    setupLayout->addWidget(boutons);
    setLayout(setupLayout);

    connect(boutons,SIGNAL(accepted()),this,SLOT(close()));
    connect(boutons,SIGNAL(rejected()),this,SLOT(close()));

}
