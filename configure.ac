AC_PREREQ(2.61)

AC_INIT([libproj], [0.0.4.9.3])

AC_LANG(C++)
AC_REQUIRE_CPP
AC_PROG_CXX

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


if test x"${SYSTEM_PROJ}" = x""; then
  
  : ${R_HOME=$(R RHOME)}
  if test -z "${R_HOME}"; then
      AC_MSG_ERROR([Could not determine R_HOME.])   
  fi

  # LIBTOOLIZE=""
  # for libtoolize in glibtoolize libtoolize; do
  #     LIBTOOLIZE=`which $libtoolize 2>/dev/null`
  #     if test "$LIBTOOLIZE"; then
  #         break;
  #     fi
  # done

  # if test x"${LIBTOOLIZE}" = x""; then
  #   AC_MSG_ERROR([proj requires either glibtoolize or libtoolize for configuration purposes.])   
  # fi

  R_CPICFLAGS=`${R_HOME}/bin/R CMD config CPICFLAGS`


  PROJ_VERSION="4.9.3"
  DATUM_VERSION="1.6"

  
  PROJ_ZIP="proj-${PROJ_VERSION}.zip"
  PROJ_DIR="proj-${PROJ_VERSION}"
  #PROJ_URL="https://github.com/OSGeo/proj.4/archive/${PROJ_VERSION}.zip"
  PROJ_URL="http://download.osgeo.org/proj/proj-${PROJ_VERSION}.zip"

  AC_MSG_NOTICE([Downloading proj (${PROJ_VERSION})])
  ${R_HOME}/bin/Rscript tools/download_zip.R "${PROJ_URL}" "${PROJ_ZIP}" "./"

  if ! test -d "${PROJ_DIR}"; then
    AC_MSG_ERROR([proj download failed.])   
  fi

    
  DATUM_DIR="${PROJ_DIR}/nad"
  DATUM_ZIP="proj-datumgrid-${DATUM_VERSION}.zip"
  DATUM_URL="http://download.osgeo.org/proj/${DATUM_ZIP}"

  AC_MSG_NOTICE([Downloading proj datum (${DATUM_VERSION})])
  ${R_HOME}/bin/Rscript tools/download_zip.R "${DATUM_URL}" "${DATUM_ZIP}" "${DATUM_DIR}"

  if ! test -e "${DATUM_DIR}/conus"; then
    AC_MSG_ERROR([proj datum download failed.])   
  fi


  
  cd ${PROJ_DIR}
  echo "Changing to `pwd`"

  AC_MSG_NOTICE([Configuring proj])
  #sh autogen.sh > /dev/null 2>&1
  autoconf
  sh ./configure --prefix="`pwd`/../inst" --enable-static CFLAGS=${R_CPICFLAGS} > /dev/null 2>&1
  
  AC_MSG_NOTICE([Compiling proj])
  make > /dev/null 2>&1
  make install > /dev/null 2>&1

  cd ..

  if ! test -e "inst/lib/libproj.a"; then
    AC_MSG_ERROR([Building proj failed.])   
  fi

  rm -rf "proj.4-${PROJ_VERSION}"

  PROJ_LIBS="`pwd`/inst/lib/libproj.a"
  PROJ_CPPFLAGS="-I`pwd`/inst/include"

else # User provided prefix for proj

  PROJ_CPPFLAGS="-I${SYSTEM_PROJ}/include"
  CPPFLAGS="${CPPFLAGS} ${PROJ_CPPFLAGS}"
  AC_CHECK_HEADER(
    [proj_api.h],
    [],
    [AC_MSG_ERROR([Unable to locate proj_api.h])]
  ) 

  if test -d "${SYSTEM_PROJ}/lib64"; then
    PROJ_LIBS="-L${SYSTEM_PROJ}/lib64"
  elif test -d "${SYSTEM_PROJ}/lib"; then
    PROJ_LIBS="-L${SYSTEM_PROJ}/lib"
  else
    PROJ_LIBS="-L${SYSTEM_PROJ}" 
  fi

  LIBS="${LIBS} ${PROJ_LIBS}"
  AC_CHECK_LIB(
    [proj], 
    [pj_init_plus], 
    [PROJ_LIBS="${PROJ_LIBS} -lproj"], 
    [AC_MSG_ERROR([Unable to locate libproj])]
  )

fi



## now use all these
AC_SUBST([PKG_CPPFLAGS],["${PKG_CPPFLAGS} ${PROJ_CPPFLAGS}"])
AC_SUBST([PKG_LIBS],["${PKG_LIBS} ${PROJ_LIBS}"])
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
