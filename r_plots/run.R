library(foreach)
library(doMC)
registerDoMC(4)  #change the 2 to your number of CPU cores

args = commandArgs(trailingOnly=TRUE)
fileName = args[1]

files <- read.table(fileName)

foreach(i=1:(length(files[,1]))) %dopar% {
    cmd <- paste("Rscript ./analyze_matrix_output.R ", files[i,1])
    system(cmd)
}
