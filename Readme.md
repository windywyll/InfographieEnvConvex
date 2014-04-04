TP Infographe Enveloppe convexe et AlphaShape
=============================================

**Biblithèques nécessaires :** glew, glm

**Build :** 
 * Sous linux, make (testé non fonctionnel sur mon ordinateur, ne trouve pas la bibliothèque glew)
 * Sous Windows, un fichier de projet visual studion est proposé, il y cependant quelques modifications possible à faire au cas où les librairies ne sont pas au même endroit.

Code :
----------

La compilation de notre projet a été rendu impossible dû à une erreur de link surement dû à un problème d'encodage.

La classe main possède le code pour gérer les paramètres d'entrée (sois rien, sois le path vers un fichier .obj)
La classe Mesh et les fichers tools et ObjLoader (.h et .cpp) sont des fichiers de codes produit ou récupérés l'année précédente qui ont été modifiés pour correspondre à ce que nous avions besoins. (Le fichier tools possède de nombreuses fonction inutiles dans notre cas)

**Enveloppe Convexe :**
Le code pour l'enveloppe convexe à été traduit mais non testé donc peut-être des erreurs.

**Alpha Shape :**
Le code pour forme un alpha shape ne fonctine pas, l'algorithme n'a pas été complètement implémenté, malgré de nombreuses heures passées à tenter de comprendre comment faire, car certains passages n'étaient pas clair (le code est commenté à ce moment)

Le Calcul des sphères circonscrites est théoriquement fonctionnel mais possède un gros problème de performence, empéchant de pouvoir lancer des tests. Malgrès quelques optimisation, il est toujours impossible d'avoir un résultat.

Les classes AlphaShape et ListOfTriangleFromPoint sont utiliséespour calculer l'Alphashape. Les classes Triangle et Tetraedre sont utilisés pour calculer le centre de la sphère circonscriteV.
	
