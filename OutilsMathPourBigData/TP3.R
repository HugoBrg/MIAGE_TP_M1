#                                                                 ----TP3----


#                                                                __Exercice 1__
# D'apr�s une enqu�te sur la composition du management des entreprises fran�aises il en sort que 35% des entreprises est ger� par des femmes.
# Sur un �chantillon de n = 100 entreprises on a trouv� que 15 sont ger�es par des femmes.
# V�rifier au niveau alpha = 1% si on peut consid�rer l'�chantillon repr�sentatif de la r�alit�.
# D�terminer le p-value du test.
#
#
# population = entreprises
# caract�e = �tre ger�e par une femme
# p = 35%
# alpha = 1%
#
#
# H0 : p = 0.35
# H1 : p ???  0.35
# Zstat = pbarre - p0 / ???(p0(1-p0)/n) ---> N(0,1)
# Z1-alpha = 2.575
# Zstat = 0.15 - 0.35 / ???(0.35(1-0.35)/100) = -4.19
#
# R�gle d'acceptation/refus :
# Si Zstat >= 2.575 ou Zstat <= -2.575 alors on refuse H0


#                                                               __Exercice 2__
# Une entreprise automobile