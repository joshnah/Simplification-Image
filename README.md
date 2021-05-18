# Simplification-Image
Simplification of image by segments and by curves bezier

#EXECUTABLES
- La commande "make" pour compiler
- Les programmes executables: tache5, tache6, bezier_2, bezier_3, bash_program.sh

******************************************************

- L'execution pour tache6, bezier_2,bezier_3:
	<nom_du_programme> <image> <distance_seuil>
+ Example: 
	./bezier_3 cheval.pbm 1

- L'execution pour tache5:
	<nom_du_programme> <image>
+ Example:
	tache5 cheval.pbm

******************************************************

- Bash_program: execute tous les programmes avec les distance_seuils
	./bash_program.sh <nom_du_fichier> <les distance_seuils>

+ Example: 
	./bash_program.sh chat.pbm 1 2 3 4 5
	(Les distance_seuils 1 2 3 4 5)

*******************************************************

- Fichiers resultat examples:
	+	cheval.contours.eps
	+	cheval.segment(d=1).eps  
	+	cheval.bezier2(d=1).eps
	+	cheval.bezier3(d=1).eps
