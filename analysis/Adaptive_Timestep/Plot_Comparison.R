# Requires ggplot2 and ggthemes
library('ggplot2')
library('ggthemes')

if (interactive()) { # Check if script is being run in a GUI or as RScript
  setwd(dirname(sys.frame(1)$ofile)) # Set working directory to script location
} else {
  # Start X11
  X11()
}

# Voltage data of LivR2009 model simulation using genetic algorithm evaluation
# protocol
sim.10.data  <- t(read.table("../Simulation_vs_Objective/Voltage_10kHz.dat"))
sim.adapt.data  <- t(read.table("Voltage_Adaptive.dat"))

# Voltage data from full dynamic clamp experiment done on the LivR2009 model
# within RTXI
# obj.data <- t(read.table("../../objectives/Objective_DynClamp_Simulation.dat"))
obj.data <- t(read.table("/home/francis/Dropbox/Data/IScale/2016.01.04/Objective_Cell_15.dat"))

dt <- 0.1
# Extract simulation data
# Adaptive model integration, data is downsampled to 10kHz
tmp.input <- sim.adapt.data[,1]
Sim.Adapt.Pace <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "2 Hz Pacing",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,2]
Sim.Adapt.IKr <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "IKr",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,3]
Sim.Adapt.IKs <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "IKs",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,4]
Sim.Adapt.ICaL <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "ICaL",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,5]
Sim.Adapt.IK1 <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "IK1",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,6]
Sim.Adapt.ICaT <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "ICaT",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,7]
Sim.Adapt.INaK <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "INaK",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.adapt.data[,8]
Sim.Adapt.INCX <- data.frame(
  Category = "Adaptive Simulation",
  Protocol = "INCX",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
# 10 kHz
dt <- 0.1
tmp.input <- sim.10.data[,1]
Sim.10.Pace <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "2 Hz Pacing",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,2]
Sim.10.IKr <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "IKr",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,3]
Sim.10.IKs <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "IKs",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,4]
Sim.10.ICaL <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "ICaL",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,5]
Sim.10.IK1 <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "IK1",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,6]
Sim.10.ICaT <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "ICaT",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,7]
Sim.10.INaK <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "INaK",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- sim.10.data[,8]
Sim.10.INCX <- data.frame(
  Category = "10 kHz Simulation",
  Protocol = "INCX",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)

# Extract dynamic clamp data used as GA objective
tmp.input <- obj.data[,1]
Obj.Pace <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "2 Hz Pacing",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,2]
Obj.IKr <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "IKr",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,3]
Obj.IKs <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "IKs",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,4]
Obj.ICaL <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "ICaL",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,5]
Obj.IK1 <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "IK1",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,6]
Obj.ICaT <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "ICaT",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,7]
Obj.INaK <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "INaK",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)
tmp.input <- obj.data[,8]
Obj.INCX <- data.frame(
  Category = "Dynamic Clamp Simulation",
  Protocol = "INCX",
  time = seq(from = 0, to = length(tmp.input) * dt - dt, by = dt),
  value = tmp.input
)

# Plots
p <- ggplot(Obj.Pace, aes(time, value, color = Category)) +
  geom_line(size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.IKr, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.IKs, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.INCX, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.INaK, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.ICaT, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.ICaL, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.IKs, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Obj.IK1, size = 1.5, alpha = 1.0, linetype = 2) +
  geom_line(data = Sim.10.Pace, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.IKr, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.IKs, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.INCX, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.INaK, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.ICaT, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.ICaL, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.IKs, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.10.IK1, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.Pace, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.IKr, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.IKs, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.INCX, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.INaK, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.ICaT, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.ICaL, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.IKs, size = 1.5, alpha = 0.7) +
  geom_line(data = Sim.Adapt.IK1, size = 1.5, alpha = 0.7) +
  facet_wrap(~ Protocol) +
  xlim(0, 250) +
  xlab("Time (ms)") + ylab("value (mV)") + theme_hc(12)
print(p)

# Calculate error
error.Adapt <- sum(abs(Obj.Pace$value - Sim.Adapt.Pace$value)^2)
error.10kHz <-  sum(abs(Obj.Pace$value - Sim.10.Pace$value)^2)

if (!interactive()) { # Keeps plot open if being run as Rscript
  message("Press Return To Continue")
  invisible(readLines("stdin", n=1))
}