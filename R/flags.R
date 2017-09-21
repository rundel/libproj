proj_cppflags = function()
{
  proj_api =  system.file("include/proj_api.h", package = "libproj")
  
  if (.Platform$OS.type == "windows" | file.exists(proj_api))
  {
    cat(
      paste0("-I", system.file("include", package = "libproj"))
    )
  } else {
    flag = readLines(system.file("build_flags", package = "libproj"))
    flag = flag[grep("PKG_CPPFLAGS=", flag)]
    flag = sub("PKG_CPPFLAGS=", "", flag)
    cat(flag)
  }
}

proj_libs = function()
{
  proj_static =  system.file("lib/libproj.a", package = "libproj")
  
  if (.Platform$OS.type == "windows")
  {
    cat(
      paste0("-L", system.file("lib", package = "libproj"), " -lproj")
    )
  } else if (file.exists(proj_static)) {
    cat(
     paste0(proj_static) 
    )
  }else {
    flag = readLines(system.file("build_flags", package = "libproj"))
    flag = flag[grep("PKG_LIBS=", flag)]
    flag = sub("PKG_LIBS=", "", flag)
    cat(flag)
  }
}