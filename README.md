# webcam_point_features
Detection of ORB features from online webcam imges.

ORB: És un algoritme que permet la obtenció de features i descriptors de una imatge. Està bassat en els algoritmes FAST per la obtenció de features i BRIEF per a la obtenció de descriptors. Tanmateix, aquest últim ha estat millorat per dotar-lo de invariança rotacional, el qual el fa molt més potent que l’algoritme original. 


Modificació: 
1. S'ha creat una màscara central de 100x100 pixels a la part central de la imatge.
2. S'han creast dues finestres de sortida on es pot comprovar que l'àrea central capta molts més keypoints (en aquella àrea) que a la finestra complerta.
