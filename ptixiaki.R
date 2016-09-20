#####################################################################################
#initialization
#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

##################################################################################################
##check robustness

setwd("~/Dropbox/sxoli/ptixiaki/evo3")

my_discrete=read.table("discrete.txt")
my_robust=read.table("robustness.txt")

#split ana generation
robust_list <- split(my_robust,rep(1:args[4],each=args[3]))
discrete_list <- split(my_discrete,rep(1:args[4],each=args[3]))

for (i in (1:args[4])){
	print(mean(unlist(discrete_list[i])==unlist(robust_list[i])))
}