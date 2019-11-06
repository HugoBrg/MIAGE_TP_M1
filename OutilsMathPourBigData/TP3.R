#                                                                 ----TP3----


#                                                                __Exercice 1__
# D'après une enquête sur la composition du management des entreprises françaises il en sort que 35% des entreprises est geré par des femmes.
# Sur un échantillon de n = 100 entreprises on a trouvé que 15 sont gerées par des femmes.
# Vérifier au niveau alpha = 1% si on peut considérer l'échantillon représentatif de la réalité.
# Déterminer le p-value du test.
#
#
# population = entreprises
# caractèe = être gerée par une femme
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
# Règle d'acceptation/refus :
# Si Zstat >= 2.575 ou Zstat <= -2.575 alors on refuse H0


#                                                               __Exercice 2__
# Une entreprise automobile