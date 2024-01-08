# **SAE 1.5 : Traiter des données**


## BUT Réseaux & Télécommunications / AlT 1 / Binôme 31

**─**

COLIN Lucas 

MICHON Antonin

Janvier 2024


---

**_<span style="text-decoration:underline;">Challenge #1 :</span>_  Réaliser trois tours de circuit**


# **Objectifs**



1. Le véhicule doit pouvoir parcourir l'intégralité des trois tours du circuit sans faire de sortie ni perdre de temps.
2. La LED multicolore doit servir d'indicateur quant à l'avancement du véhicule sur son nombre de tours.


# **Acheminement & Organisation**

Nous devons séparer les différentes composantes qui devront constituer notre futur programme qui permettra de remplir les objectifs ci-dessus.

Il nous faut donc en premier lieu pouvoir contrôler les mouvements du véhicule. Pour cela nous avons récupéré le contenu du TP4 de la ressource R107. Le fichier compressé [carMotors.zip](https://moodle.univ-fcomte.fr/mod/resource/view.php?id=713831) contient une classe déjà faite avec toutes les méthodes pour déplacer notre véhicule facilement.

Ensuite il fallait absolument pouvoir contrôler la LED multicolore pour permettre la résolution plus simple des problèmes qui allaient probablement se manifester sur la suite du programme. Nous avons donc récupéré notre code du TP2 avec la librairie “FastLED.h”.

Pour permettre à notre véhicule de suivre la ligne pour rester sur le circuit, il nous faut pouvoir utiliser le capteur line track positionné sous notre robot, en utilisant la documentation fournie par le fabricant  ELEGOO mise à notre disposition dans la SAE.


# **Structure du Programme**

Une fois tous les différents élément maîtrisés il faut coder un programme qui peut les faire marcher tous ensemble de la meilleur manière possible, c’est à dire avoir un programme court et efficace qui optimise au mieux les ressources mise à disposition par le matériel, et avoir un bon équilibre entre vitesse et précision afin de ne pas perdre trop de temps, et ne jamais sortir du circuit. Il faut aussi pouvoir compter les tours convenablement afin de respecter les objectifs initiaux.