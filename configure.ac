AC_PREREQ(2.61)

AC_INIT([libproj], [m4_esyscmd_s([cat proj_version])])

AC_ARG_ENABLE(
  [verbose],
  AC_HELP_STRING(
    [--enable-verbose],
    [Enable verbose output of build]
  ),
  [VERBOSE="yes"],
  [VERBOSE="no"]
)


AC_ARG_WITH(
  [system-proj],
  AC_HELP_STRING(
    [--with-system-proj=<PROJ prefix>],
    [Supply location (prefix) of PROJ]
  ),
  [SYSTEM_PROJ=$withval],
  [SYSTEM_PROJ=""]
)

PROJ_CPPFLAGS=""
PROJ_LIBS=""


if test x"${SYSTEM_PROJ}" != x""; then 
  
  # User provided prefix for proj
  PROJ_CPPFLAGS="-I${SYSTEM_PROJ}/include"
  
  if test -d "${SYSTEM_PROJ}/lib64"; then
    PROJ_LIBS="-L${SYSTEM_PROJ}/lib64"
  elif test -d "${SYSTEM_PROJ}/lib"; then
    PROJ_LIBS="-L${SYSTEM_PROJ}/lib"
  else
    PROJ_LIBS="-L${SYSTEM_PROJ}" 
  fi
  PROJ_LIBS="${PROJ_LIBS} -lproj"
  
else 

  : ${R_HOME=$(R RHOME)}
  if test -z "${R_HOME}"; then
      AC_MSG_ERROR([Could not determine R_HOME.])   
  fi

  PROJ_VERSION=$(cat proj_version)

  PROJ_DIR="proj-${PROJ_VERSION}"
  DATUM_DIR="${PROJ_DIR}/nad"
  
  #AC_MSG_NOTICE([PROJ_DIR: ${PROJ_DIR}])
  #AC_MSG_NOTICE([DATUM_DIR: ${DATUM_DIR}])
  
  
  if ! test -d "${PROJ_DIR}"; then
    AC_MSG_ERROR([PROJ source directory can't be found.])   
  fi
  
  if ! test -e "${DATUM_DIR}/conus"; then
    AC_MSG_ERROR([PROJ datum directory can't be found.])   
  fi

  # Build PROJ
  cd ${PROJ_DIR}

  INST_DIR=`cd ../inst;pwd`

  AC_MSG_NOTICE([Configuring proj])
  if test x"${VERBOSE}" = x"no"; then
    sh ./configure --prefix="${INST_DIR}" --enable-static --disable-shared CFLAGS="${R_CFLAGS}" CXXFLAGS="${R_CXXFLAGS}" > /dev/null 2>&1
  else
    sh ./configure --prefix="${INST_DIR}" --enable-static --disable-shared CFLAGS="${R_CFLAGS}" CXXFLAGS="${R_CXXFLAGS}"
  fi
    
  AC_MSG_NOTICE([Compiling proj])
  if test x"${VERBOSE}" = x"no"; then
    make install > /dev/null 2>&1
  else
    make install
  fi

  cd ..

  if ! test -e "inst/lib/libproj.a"; then
    AC_MSG_ERROR([Building proj failed.])   
  fi
  
  if ! test -e "inst/share/proj/conus"; then
    AC_MSG_ERROR([Including proj datum failed.])   
  fi    

  strip -x -S inst/lib/libproj.a

  rm -rf inst/bin
  rm -rf inst/lib/pkgconfig
  rm -rf inst/share/man
  
  PROJ_LIBS="${INST_DIR}/lib/libproj.a"
  PROJ_CPPFLAGS="-I${INST_DIR}/include"
fi

CPPFLAGS="${CPPFLAGS} ${PROJ_CPPFLAGS}"
AC_CHECK_HEADER(
  [proj_api.h],
  [],
  [AC_MSG_ERROR([Unable to locate proj_api.h])]
) 

LIBS="${LIBS} ${PROJ_LIBS}"
AC_CHECK_LIB(
  [proj], 
  [pj_init], 
  [], 
  [AC_MSG_ERROR([Unable to locate libproj])]
)


AC_MSG_NOTICE([PROJ_CPPFLAGS: ${PROJ_CPPFLAGS}])
AC_MSG_NOTICE([PROJ_LIBS: ${PROJ_LIBS}])

AC_SUBST([PKG_CPPFLAGS],["${PROJ_CPPFLAGS}"])
AC_SUBST([PKG_LIBS],["${PROJ_LIBS}"])
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

