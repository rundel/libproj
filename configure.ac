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

  LIBTOOLIZE=""
  for libtoolize in glibtoolize libtoolize; do
      LIBTOOLIZE=`which $libtoolize 2>/dev/null`
      if test "$LIBTOOLIZE"; then
          break;
      fi
  done

  if test x"${LIBTOOLIZE}" = x""; then
    AC_MSG_ERROR([proj requires either glibtoolize or libtoolize for configuration purposes.])   
  fi


  PROJ_VERSION=4.9.3
  
  AC_MSG_NOTICE([Downloading proj ${PROJ_VERSION}])
  if ! `${R_HOME}/bin/Rscript tools/get_proj.R ${PROJ_VERSION}`; then
    AC_MSG_ERROR([PROJ download failed.])   
  fi
  
  
  cd proj.4-${PROJ_VERSION}

  AC_MSG_NOTICE([Configuring proj ${PROJ_VERSION}])
  sh autogen.sh > /dev/null 2>&1
  ./configure --prefix="`pwd`/../inst" --disable-shared --enable-static > /dev/null 2>&1
  
  AC_MSG_NOTICE([Compiling proj ${PROJ_VERSION}])
  make > /dev/null 2>&1

  AC_MSG_NOTICE([Installing proj ${PROJ_VERSION}])
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
