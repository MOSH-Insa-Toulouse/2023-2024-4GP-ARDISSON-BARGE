# 4GP 2023/2024 - Projet de capteur _low-tech_ en graphite - Par Cyril ARDISSON et Kévin BARGE
## Table des matières
✓ [Contacts](#contacts) <br>
✓ [Contexte](#contexte) <br>
✓ [Livrables](#livrables) <br>
✓ [Matériel requis](#materiel-requis) <br>
1- [Simulation sous LTSpice](#simulation-sous-ltspice) <br>
2- [Design du PCB sous KiCAD](#design-du-pcb-sous-kicad) <br>
3- [Code sous Arduino IDE](#code-sous-arduino-ide) <br>
4- [Application Android](#application-android) <br>
5- [Réalisation du shield](#realisation-du-shield) <br>
6- [Banc de test et principaux résultats](#banc-de-test-et-principaux-resultats) <br>
7- [Datasheet du capteur](#datasheet-du-capteur) <br>
✓ [Conclusions et analyse critique du projet](#conclusions-et-analyse-critique-du-projet) <br>
___
## Contacts
Cyril ARDISSON : [ardisson@insa-toulouse.fr](mailto:ardisson@insa-toulouse.fr) <br>
Kévin BARGE : [barge@insa-toulouse.fr](mailto:barge@insa-toulouse.fr) <br>
___
## Contexte
Dans le cadre de l'UF de 4ème Année spécialité Génie Physique "Du capteur au banc de test" (I4GPMH21), nous avons réalisé l'évaluation d'une technologie low-tech : un capteur en graphite, composé de papier, recouvert d'une couche de graphite qu'on peut simplement trouver dans les crayons à papier ! En se déformant, le nombre de particules de graphite reliées varie, ce qui entraîne une modification de sa résistance. De cela, on peut donc induire la déformation. Sur le même principe qu'une jauge de contrainte (ici low-tech !). Ce travail se base sur les travaux de chercheurs de l'Université de Northwestern (Etats-Unis), publiés en 2014 dans l'article "_Pencil Drawn Strain Gauges and Chemiresistors on Paper_" (Cheng-Wei Lin, Zhibo Zhao, Jaemyung Kim & Jiaxing Huang). 

Afin de réaliser ce projet, plusieurs étapes ont été réalisées : simulation électronique, design de PCB et fabrication, programmation d'un Arduino Uno et d'une IHM, mise en place d'un banc de test et écriture d'une datasheet.

Ici, nous faisons le tour de tout ce qui a été fait dans le cadre de ce projet.

___
## Livrables
Plusieurs livrables sont attendus :

✓ **Le shield PCB connecté à une carte Arduino Uno**, composé : du capteur en graphite, d'un montage amplificateur transimpédance et d'un module Bluetooth. D'autres composants peuvent aussi être implémentés (*) : écran OLED, encodeur rotatoire, potentiomètre digital, flex sensor et connexions pour un servo-moteur ; <br>
✓ **Le code Arduino** permettant d'effectuer les mesures du capteur et de contrôler les composants implémentés ; <br>
✓ **L'APK Android** permettant d'interfacer le shield et le code Arduino correspondant : l'IHM en résumé ; <br>
✓ **Le / Les code(s) Arduino** permettant d'effectuer les tests du capteur ; <br>
✓ **La datasheet du capteur** reprenant toutes ses caractéristiques ainsi que ses tests. <br>

(*) Pour notre projet, nous avons décidés d'implémenter sur notre shield : l'écran OLED, l'encodeur rotatoire, le potentiomètre digital et le flex sensor. 
___
## Matériel requis
Afin de réaliser notre dispositif, nous avons eu besoin de :

Pour le montage amplificateur transimpédance : <br>
✓ Résistances : une de $1\ \text{k}\Omega$, une de $10\ \text{k}\Omega$ et deux de $100\ \text{k}\Omega$ - une troisième de $100\ \text{k}\Omega$ peut être prévue, mais peut aussi être substituée par une résistance variable (le potentiomètre digital), choix que l'on a fait ; <br>
✓ Un potentiomètre digital (si substitution d'une résistance de $100\ \text{k}\Omega$) : ici, choix du MCP41050 ; <br>
✓ Capacités : trois de $100\ \text{nF}$ et une de $1\ \mu\text{F}$ ; <br>
✓ Un amplificateur opérationnel : ici, choix du LTC1050 ; <br>

Pour le reste du dispositif : <br>
✓ Un module Bluetooth : ici, choix du HC05 ; <br>
✓ Un écran OLED de dimension 128*64 ; <br>
✓ Un encodeur rotatoire ; <br>
✓ Un flex sensor.
___
## 1- Simulation sous LTSpice
...
___
## 2- Design du PCB sous KiCAD
...
___
## 3- Code sous Arduino IDE
...
___
## 4- Application Android
...
___
## 5- Réalisation du shield
...
___
## 6- Banc de test et principaux résultats
...
___
## 7- Datasheet du capteur
...
___
## Conclusions et analyse critique
...


