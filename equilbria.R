curDir <- ("~/Dropbox/sxoli/ptixiaki/evo3")
n<-1
for (i in 1:n){
	dirName <- paste(curDir,"/neutral.run.", i, sep="")
	setwd(dirName)

	    equilibrium <- tryCatch(
        {
            read.table("equilibrium_period.txt")
            setwd("~/Dropbox/sxoli/ptixiaki/evo3")
			png(file=paste(sprintf("%04d", i),".png",sep=""), width=1024, height=768)
			barplot(table(equilibrium), main = "barplot")
			dev.off()

        },
        error=function(cond) {

        },

        warning=function(cond) {

        },

        finally={
        }
    )    
}  
