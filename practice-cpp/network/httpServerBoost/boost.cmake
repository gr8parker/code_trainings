include( ExternalProject )

set( boost_URL "https://github.com/gr8parker/boost" )
#set( boost_SHA1 "9f1dd4fa364a3e3156a77dc17aa562ef06404ff6" )
set( boost_INSTALL ${CMAKE_CURRENT_BINARY_DIR}/boost/src/boost/ )
set( boost_INCLUDE_DIR ${boost_INSTALL}/boost )
set( boost_LIB_DIR ${boost_INSTALL}/stage/lib )
set( boost_LD_PATH ${boost_INSTALL}/stage/lib )

ExternalProject_Add ( boost
  PREFIX boost
  GIT_REPOSITORY ${boost_URL}
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND
  ./bootstrap.sh
  --prefix=${boost_INSTALL}
  BUILD_COMMAND
  ./bjam
  --with-system
  --with-thread
  --with-date_time
  --with-regex
  --with-serialization
  stage
  INSTALL_COMMAND ""
  INSTALL_DIR ${boost_INSTALL} )

set( Boost_SHARED
  ${boost_LD_PATH}/libboost_system.so
  ${boost_LD_PATH}/libboost_thread.so)
  
message( STATUS "Boost shared libs: " ${boost_SHARED})
