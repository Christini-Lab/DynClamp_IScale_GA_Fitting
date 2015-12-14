# Script plots the fitting results, separating the first 10 standard runs, and
# the second set of
library(ggplot2)
library(ggthemes)
library(grid)

if (interactive()) { # Check if script is being run in a GUI or as RScript
  setwd(dirname(sys.frame(1)$ofile)) # Set working directory to script location
} else {
  # Start X11
  X11()
}

# Get file names of all the data files
file.names <- c(list.files("Standard_Bounds/", full.names = TRUE),
                list.files("Constrained_Bounds/", full.names = TRUE))
num.first.run <- length(list.files("Standard_Bounds/"))
num.total.run <- length(file.names)

# Order of current scalings in data
current.order <- c("IKr", "IKs", "ICaL", "IK1", "ICaT", "INaK", "INa", "IKp",
                   "IpCa", "Jserca", "INCX")
num.current <- length(current.order)

vec.size <- (num.current) * num.total.run
run.type <- vector(length = vec.size)
current.scaled <- vector(length = vec.size)
scaling.factor <- vector(length = vec.size)
individual.error <- vector(length = vec.size)
idx <- 1

for (i in 1:length(file.names)) {
  data.input = read.table(file.names[i], skip = 1)
  best.idx = which.min(data.input[, dim(data.input)[2]])
  best.error = min(data.input[, dim(data.input)[2]])
  # Check that number of columns in data is correct
  # Should be currents plus error
  data.length <- length(data.input[best.idx,])
  stopifnot(data.length == num.current + 1)

  for (z in 1:(data.length - 1)) {
    if (i <= num.first.run) {
      run.type[idx] <- "Standard Bounds"
    } else {
      run.type[idx] <- "Constrained Bounds"
    }
    current.scaled[idx] <- current.order[z]
    scaling.factor[idx] <- as.numeric(data.input[best.idx,][z])
    individual.error[idx] <- best.error
    idx <- idx + 1
  }
}

# Construct data frame with modified ordering
data.df <- data.frame(
  run.type = factor(run.type, levels=c("Standard Bounds",
                                       "Constrained Bounds")),
  current.scaled = factor(current.scaled,
                          levels=c("INa", "IKs", "IKr", "IK1", "IKp", "ICaL",
                                   "ICaT", "IpCa", "Jserca", "INCX", "INaK")),
  scaling.factor = scaling.factor,
  individual.error = individual.error
)

# Plot current type versus parameter scaling
ggplot(data = data.df, aes(run.type, scaling.factor, color = run.type,
                           shape = run.type)) +
  # Add an alternating background for the currents
  geom_rect(data = data.df, aes(fill = current.scaled), xmin = -Inf, xmax = Inf,
            ymin = -Inf, ymax = Inf, alpha = 0.1, linetype = 0) +
  scale_fill_manual(values = rep(c("white", "gray90"), length.out = 11),
                    guide = "none") +
  # Plot data points
  geom_point(size = 3) +
  # Facet based on currents
  facet_grid(~current.scaled, space = "free_x") +
  stat_summary(fun.data = "mean_cl_normal", geom = "errorbar", color = "black",
               alpha = 0.5, width = 0.5, size= 1) +
  stat_summary(geom = "point", fun.y = mean, color = "black", alpha = 1.0,
               shape = 95, size = 10) +
  # Highchart theme
  theme_hc() +
  # Theme settings
  theme(
    text = element_text(size = 16),
    axis.text.x = element_blank(),
    axis.ticks.x = element_blank(),
    axis.ticks.y = element_blank(),
    legend.title = element_blank(),
    axis.title.x = element_blank(),
    panel.margin = unit(-1, "points"),
    panel.grid.major = element_line(size = 1, linetype = "dashed",
                                    color = "black"),
    strip.background = element_blank()
  ) +
  # Remove background on legend keys
  guides(color = guide_legend(override.aes = list(fill = NA))) +
  # Y-axis label
  ylab("Scaling Factor\n") + ylim(0, 2.5) + scale_color_gdocs()
ggsave("Nominal_model_fitting_results.pdf")

if (!interactive()) { # Keeps plot open if being run as Rscript
  message("Press Return To Continue")
  invisible(readLines("stdin", n=1))
}