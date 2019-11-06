                                                                    # TP2 - Hugo BERANGER

#Lecture du fichier
mydata = read.csv(file = "C:/Users/hugob/Documents/deathsfrance18991995.csv", header=TRUE,sep=";", fill=TRUE)
head(mydata)


                                                                        #QUESTION 1


#Remplace les cases vides par des 0
mydata[is.na(mydata)] <-0

#Reconstruction du tableau pour la colonne "Age"
mydata$Age = mydata$Age1*10+mydata$Age2
mydata <- mydata[,c("Year", "Female", "Male", "Total", "Age")]

#Subset du tableau principal (9721 => 1ère ligne de 1980 & 11040 => dernière ligne de 1990)
mydatasub <- mydata[9721:11040,]

#Somme des hommes morts dans notre sous tableau
totalHommesMorts <- sum(mydatasub$Male)

#xbarre = moyenne
#mu = moyenne recherchée
#sigma = écart type
#n = echantillon
xbarre=sum(mydatasub$Male * mydatasub$Age)/totalHommesMorts
mu = 75 
sigma = 12
n = 50

#2 hypothèses :
#H0 espérance hommes entre 1980 et 1990 >= esperance hommes 2019
#H1 espérance hommes 2019 > esperance hommes entre 1980 et 1990
resH = (xbarre-mu)/(sigma/sqrt(n))

#On accepte l'hypothèse : 4.37 > 1.6766


                                                                        #QUESTION 2


#Somme des femmes mortes dans notre sous tableau
totalFemmesMortes <- sum(mydatasub$Female)

#xbarre = moyenne
#on garde les mêmes valeurs pour mu, sigma et n
xbarre=sum(mydatasub$Female * mydatasub$Age)/totalFemmesMortes

#2 hypothèses :
#H0 espérance femmes entre 1980 et 1990 >= esperance femmes 2019
#H1 espérance femmes 2019 > esperance femmes entre 1980 et 1990
resF = (xbarre-mu)/(sigma/sqrt(n))

#On refuse l'hypothèse : 0.87 < 1.6766


                                                                        #QUESTION 3 



#Sur la table l'intervalle varie entre 1.2991 et 2.4049, l'acceptation reste donc inchangée et l'effet de seuil n'a donc pas lieu.



                                                                        #QUESTION 4


xbarre=sum(mydatasub$Male * mydatasub$Age)/totalHommesMorts

z=1.67
x=seq(-3,3,length=250)
y=dnorm(x,mean=0,sd=1)
plot(x,y,type="l",lwd=1,main='Test unilatéral à droite', yaxt="n")
x=seq(1.67,3,length=250)
y=dnorm(x,mean=0,sd=1)
polygon(c(1.67,x,3),c(0,y,0),col="yellow")
text(2,0.01,"5%")
abline(v=z,col="red")
text(z-.1,0.2, srt=90, labels = z)
abline()

#Effet de seuil entre 1 et 6 compris pour alpha : 0.05


                                                                        #QUESTION 5
z=2.4049
x=seq(-3,3,length=250)
y=dnorm(x,mean=0,sd=1)
plot(x,y,type="l",lwd=1,main='Test unilatéral à droite', yaxt="n")
x=seq(2.4049,3,length=250)
y=dnorm(x,mean=0,sd=1)
polygon(c(2.4049,x,3),c(0,y,0),col="yellow")
text(2,0.01,"5%")
abline(v=z,col="red")
text(z-.1,0.2, srt=90, labels = z)
abline()

#Effet de seuil entre 1 et 6 compris pour alpha : 0.01