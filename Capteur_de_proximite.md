![http://flyport-wifi-rc-car.googlecode.com/svn/trunk/Images/BanniereWiki.png](http://flyport-wifi-rc-car.googlecode.com/svn/trunk/Images/BanniereWiki.png)

# Introduction #

Notes importantes sur les conditions à vérifier sur les modules à ultrasons ou infrarouge, en termes de prix, de performances et de connectique (nombre de pins, tension).

[Cet article](http://bildr.org/2011/03/various-proximity-sensors-arduino/) présente une réalisation de détecteur de proximité avec un Arduino et 3 capteurs différents, qui peuvent être des choix pertinents pour le projet.


# Digital VS Analogique #

Les détecteurs digitaux semblent être plus chers et plus difficiles à manipuler. Malgré la limitation de résolution des entrées analogiques du Flyport (1/1024), cette solution semble être la plus pertinente pour des applications simples.


# Modèles de capteurs repérés #

#### Les plus pertinents ####

| **Nom** | [Infrared Proximity Sensor - Sharp GP2Y0A21YK](http://www.sparkfun.com/products/242) |
|:--------|:-------------------------------------------------------------------------------------|
| **Prix** | 13.95$ (10.6€)                                                                       |
| **Description** | Capteur de distance IR Non-Linéaire                                                  |

#### Les moins pertinents ####

| **Nom** | [ePIR](http://www.sparkfun.com/products/9587) |
|:--------|:----------------------------------------------|
| **Prix** | 11.95$ (9.09€)                                |
| **Description** | Motion Detector **Pas vraiment Adapté**       |

| **Nom** | [Maxbotix LV-EZ0](http://www.sparkfun.com/products/639) |
|:--------|:--------------------------------------------------------|
| **Prix** | 25.95$ (19.7€)                                          |
| **Description** | Capteur de distance US Linéaire **Trop cher**           |

| **Nom** | [Optical Detector / Phototransistor - QRD1114](http://www.sparkfun.com/products/246) |
|:--------|:-------------------------------------------------------------------------------------|
| **Prix** | 1.13$ (0.86€)                                                                        |
| **Description** | Détecteur de proximité immédiate (0.5 à 3 cm). **Trop court**                        |

#### À étudier ####

[Quelques référence de capteurs…](http://www.robotroom.com/Sensors.html)