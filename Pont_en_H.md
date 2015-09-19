![http://flyport-wifi-rc-car.googlecode.com/svn/trunk/Images/BanniereWiki.png](http://flyport-wifi-rc-car.googlecode.com/svn/trunk/Images/BanniereWiki.png)

# Introduction #

Le [pont en H](http://fr.wikipedia.org/wiki/Pont_en_H) est un montage à transistors qui permet de séparer les parties d'alimentation et de commande d'un dipôle. Il sert généralement à contrôler la vitesse et le sens de rotation de moteurs.

# Moteur utilisé #

Le moteur utilisé est un _DC Mabuchi RS540RH_. Ses principales caractéristiques sont listées ci-dessous :

| | Tension d'alimentation (V) | C / Hors-charge (A) | C / d'efficacité maximale | C / de blocage (A) |
|:|:---------------------------|:--------------------|:--------------------------|:-------------------|
| V<sub>ALIM</sub> = 12 V (théorique) | 4.5 - 12                   | 0.95                | 5.93                      | 37.0               |
| V<sub>ALIM</sub> = 8 V (réel) | ~                          | 1.42                | ~                         | ~                  |

# Références à étudier #

#### Driver de moteur DC Intégré ####

Le [MC33926 Motor Driver Carrier](http://www.pololu.com/catalog/product/1212) est une carte implémentant un driver de moteur. Il présente les caractéristiques suivantes :

  * Tension de sortie de 5 à 28V;
  * Courant de sortie de 3A (DC), 5A (peak);
  * Entrées logiques PWM de 3V à 5V;
  * Sonde de courant proportionnelle;
  * Protection contre le sur-courant, la sur-température et le sous-voltage.

Ce driver présente un courant de pic suffisant pour démarrer le moteur, un courant continu suffisant pour rouler, et des tensions d'alimentation et d'entrée adaptées au moteur et à la sortie du module Flyport.
http://www.robotshop.com/eu/controleur-moteur-dc-3a-5v-28v-pololu-mc33926-2.html
<p><img src='http://b.pololu-files.com/picture/0J1804.200.jpg?86e4f0e1598b5f996bbd0ecdfcd71b11' width='50px' /></p>

#### Une réalisation de pont en H ####

[Cette page](http://ancrobot.free.fr/Old_version/fichtech/action/ponthII/index.htm) présente une réalisation d'un pont en H capable de dissiper une grande puissance (courant de plusieurs ampères). On y trouve des références de composants intéressants dans le cadre du projet.

http://ikalogic.com/h_bridge.php

http://www.pyroelectro.com/tutorials/l298_control/schematic.html

#### Quelques références de composants ####

[Cette page](http://www.telecom-robotics.org/pont_en_H) présente quelques références de composants pour faire un pont en H.

#### Pont en H Bipolaire ####

http://ikalogic.com/H_bridge_old.php Pont en H à transistors bipolaire (à réaliser).


# Pont en H #

[LMD18200](http://www.national.com/pf/LM/LMD18200.html) Pont en H (3A, 55V, Peak Current 6A)


# Drivers de ponts en H #

  * **TD340** : [datasheet](http://ad5ey.net/~david/motors/7048%20H-bridge%20controller%20-%20external%20FETs.pdf)
  * **SN754410** : [datasheet](http://www.ti.com/lit/ds/symlink/sn754410.pdf) Quadruple Half-H Driver — 1A Output / Driver — 4.5 to 36V supply
  * **L298** : [datasheet](http://www.learn-c.com/l298.pdf) Ce driver [semble avoir la pêche](http://forum.sparkfun.com/viewtopic.php?f=32&t=21512) qu'il faut pour faire tourner une voiture similaire à la notre. 46V, 4A, protection contre la surchauffe. [3$ chez Sparkfun](http://www.sparkfun.com/products/9479).


# Documentation #

  * [PWM et Ponts en H](http://www.rfc1149.net/rose2010/wp-content/uploads/2010/03/PWM-et-ponts-en-H.pdf), R. Bichet, J. Estivie, E. Molto et F. Tovo, 2010
  * [Le Pont en H](http://ancrobot.free.fr/fiches/pdf/index(4).pdf), P. Lucidarme, 03/2009