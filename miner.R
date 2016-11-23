anakata=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessanakata.txt")
deka_assoi=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessdekaassoi.txt")
deka_midenika=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnessmidenika.txt")
pente_assoi_pente_midenika=read.table("/home/antonios/Dropbox/sxoli/ptixiaki/evo3/fitnesspenteassoi.txt")

c(65:90)
anakata <- anakata[-c(50:101), ]
deka_assoi <- deka_assoi[-c(50:101), ]
deka_midenika <- deka_midenika [-c(50:101), ]
pente_assoi_pente_midenika <- pente_assoi_pente_midenika [-c(50:501),]

anakata <- anakata[,-c(1, 2, 3) ]
deka_assoi <- deka_assoi[,-c(1, 2, 3) ]
deka_midenika <- deka_midenika [,-c(1, 2, 3) ]
pente_assoi_pente_midenika <- pente_assoi_pente_midenika [,-c(1, 2, 3) ]

png(filename="fitness_generations")

plot(deka_midenika,col="red",type="l",xlab="Generation Number",ylab="Generation Fitness")
lines(deka_assoi,col="blue",type="l",xlab="Generation Number",ylab="Generation Fitness")

lines(pente_assoi_pente_midenika,col="black",type="l",xlab="Generation Number",ylab="Generation Fitness")
lines(anakata,col="green",type="l",xlab="Generation Number",ylab="Generation Fitness")

legend('bottomright', legend=c("0000000000","1111100000","1010101010","1111111111") , lty=1, col=c('red', 'black', 'green','blue'), bty='n', cex=.75)

dev.off()
