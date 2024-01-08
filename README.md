<p style="color: red; font-weight: bold">>>>>>  gd2md-html alert:  ERRORs: 0; WARNINGs: 1; ALERTS: 2.</p>
<ul style="color: red; font-weight: bold"><li>See top comment block for details on ERRORs and WARNINGs. <li>In the converted Markdown or HTML, search for inline alerts that start with >>>>>  gd2md-html alert:  for specific instances that need correction.</ul>

<p style="color: red; font-weight: bold">Links to alert messages:</p><a href="#gdcalert1">alert1</a>
<a href="#gdcalert2">alert2</a>

<p style="color: red; font-weight: bold">>>>>> PLEASE check and correct alert issues and delete this message and the inline alerts.<hr></p>



## 

<p id="gdcalert1" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image1.png). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert2">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image1.png "image_tooltip")
 



<p id="gdcalert2" ><span style="color: red; font-weight: bold">>>>>>  gd2md-html alert: inline image link here (to images/image2.jpg). Store image on your image server and adjust path/filename/extension if necessary. </span><br>(<a href="#">Back to top</a>)(<a href="#gdcalert3">Next alert</a>)<br><span style="color: red; font-weight: bold">>>>>> </span></p>


![alt_text](images/image2.jpg "image_tooltip")



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