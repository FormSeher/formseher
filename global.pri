# set config needed by all subprojects
CONFIG += c++11

#projekt root directories
ROOT_DIR = $$PWD
ALG_DIR = $${ROOT_DIR}/algorithms
APP_DIR = $${ROOT_DIR}/app
TEST_DIR = $${ROOT_DIR}/test
BDB_DIR = $${ROOT_DIR}/TeamBdbTool

#src directories
SRC_DIR = $${ROOT_DIR}/src
ALG_SRC_DIR = $${ALG_DIR}/src
APP_SRC_DIR = $${APP_DIR}/src
TEST_SRC_DIR = $${TEST_DIR}/src
BDB_SRC_DIR = $${BDB_DIR}/src

#include directories for headers
ALG_INCL_DIR = $${ALG_DIR}/include
APP_INCL_DIR = $${APP_DIR}/include
TEST_INCL_DIR = $${TEST_DIR}/include
BDB_INCL_DIR = $${BDB_DIR}/include

# output path for algorithms library
ALG_BIN_DIR = $${ALG_DIR}/lib

#form dir directories
APP_FORM_DIR = $${APP_DIR}/form
BDB_FORM_DIR = $${BDB_DIR}/form

#build directories
#BUILD_DIR = $${ROOT_DIR}/build
#ALG_BUILD_DIR = $${BUILD_DIR}/algorihms
#APP_BUILD_DIR = $${BUILD_DIR}/app
#TEST_BUILD_DIR = $${BUILD_DIR}/test
#LIB_DIR = $${ROOT_DIRECTORY}/lib
#TESTS_DIR = $${BUILD_DIR}/tests
