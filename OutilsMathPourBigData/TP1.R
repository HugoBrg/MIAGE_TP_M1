is.na(mydata$Age1)<-0
mean(((mydata[1900,]$Age1*10+mydata[1900,]$Age2)+
       (mydata[1943,]$Age1*10+mydata[1943,]$Age2)+
       (mydata[1960,]$Age1*10+mydata[1960,]$Age2)+
       (mydata[1980,]$Age1*10+mydata[1980,]$Age2)+
       (mydata[1990,]$Age1*10+mydata[1990,]$Age2))/5)

moy = (mydata[1900,]$Age1*10+mydata[1900,]$Age2)/mydata[1900,]$Total * 10


