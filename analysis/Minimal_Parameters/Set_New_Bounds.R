# This script obtains the best individual from all specified GA data files, and
# creates a new GA settings file with the parameter bounds set to the span of
# all best individuals.
#
# Usage:
# Rscript Set_New_Bounds.R [settings file name] [GA Data file(s)]

# First argument is the file name of the new GA settings file, followed by
# any number of GA data files.
args <- commandArgs(trailingOnly = TRUE)
settings.filename <- args[1]

all.best <- vector() # Holder for all the parameters of the best individuals
for (i in 2:(length(args))) {
  data <- read.table(args[i], skip = 1) # Skip first line since it is the header
  data.dim <- dim(data)

  error <- data[data.dim[2]] # Last column is the objective error
  best.idx <- which.min(error[,1]) # Find index of lowest error
  best.param <- data[best.idx, 1:data.dim[2] - 1] #
  all.best <- rbind(all.best, best.param[1,])
}

# Write GA settings file with new bounds
line <- c("SGA",
           "9")
write(line, file = settings.filename)
for (i in 1:dim(all.best)[2]) {
  line = paste(c("double",
                 min(all.best[i]),
                 max(all.best[i])), sep = "", collapse = " ")
  write(line, file = settings.filename, append = TRUE)
}

line <- c("1",
           "Min",
           "0",
           "400",
           "200",
           "0.9",
           "default",
           "TournamentWOR 4",
           "default",
           "default",
           "default",
           "default",
           "default",
           "default",
           "default",
           "default",
           "default",
           "1 GA_Run.dat")
write(line, file = settings.filename, append = TRUE)
