args = commandArgs(trailingOnly=TRUE)

if(length(args) != 1)
  stop("Expected only one argument, PROJ version string")

proj_version = args[1]
proj_zip = paste0(proj_version,".zip")
proj_folder = paste0("proj.4-", proj_version)
proj_url = paste0("https://github.com/OSGeo/proj.4/archive/", proj_version, ".zip")

if (!file.exists(proj_folder))
{
    download.file(proj_url, proj_zip, quiet = TRUE)
    unzip(proj_zip)
    unlink(proj_zip)
}

nad_folder = file.path(proj_folder,"nad")
conus = file.path(nad_folder, "conus.lla")

if (!file.exists(conus))
{
    datum_url = "http://download.osgeo.org/proj/proj-datumgrid-1.5.zip"
    datum_zip = file.path(nad_folder,"proj-datumgrid-1.5.zip")

    download.file(datum_url, datum_zip, quiet = TRUE)
    unzip(datum_zip, exdir = nad_folder)
    unlink(datum_zip)
}