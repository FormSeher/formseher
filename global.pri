#projekt root directories
ROOT_DIR = $$PWD
ALG_DIR = $${ROOT_DIR}/algorithms
APP_DIR = $${ROOT_DIR}/app

#src directories
SRC_DIR = $${ROOT_DIR}/src
ALG_SRC_DIR = $${ALG_DIR}/src
APP_SRC_DIR = $${APP_DIR}/src

#include directories for headers
ALG_INCL_DIR = $${ALG_DIR}/include
APP_INCL_DIR = $${APP_DIR}/include

#form dir
$$(APP_FORM_DIR) = $${APP_DIR}/form


#LIB_DIR = $${ROOT_DIRECTORY}/lib
#BUILD_DIR = $${ROOT_DIR}/build
#TESTS_DIR = $${BUILD_DIR}/tests
