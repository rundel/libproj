args = commandArgs(trailingOnly=TRUE)

url  = args[1]
file = args[2]
dir  = args[3]

download.file(url, file, quiet = TRUE)
unzip(file, exdir = dir)
unlink(file)