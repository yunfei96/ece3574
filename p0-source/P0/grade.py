#-----------------------------------------------------------------------------
# this grade script assumes it is run from within the repository
# for example in /vagrant within the VM
#-----------------------------------------------------------------------------

import logging
import os
import subprocess
import sys
import shutil
from datetime import datetime
import tempfile

# simple CMakeLists.txt
cmake_text1="""
cmake_minimum_required(VERSION 3.5)
project(HEXD CXX)

if(UNIX AND WERROR)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_executable(hexd hexd.cpp)
set_property(TARGET hexd PROPERTY CXX_STANDARD 11)

enable_testing()
add_subdirectory(tests)
"""

# run test on each file
cmake_text2="""
foreach(ID RANGE 5)
add_test(NAME test${ID}
    COMMAND ${CMAKE_COMMAND}
    -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/raw${ID}.bin
    -DERR_FILE=raw${ID}.stderr
    -DOUT_FILE=raw${ID}.stdout
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/raw${ID}.hex
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
endforeach(ID)
"""

# test by capturing standard output and diffing with the expected
cmake_text3="""
execute_process( 
  COMMAND "../hexd" ${INPUT_FILE}
  ERROR_FILE ${ERR_FILE}
  OUTPUT_FILE ${OUT_FILE}
  )

# Compare the output to the expected
execute_process( 
  COMMAND "diff" ${OUT_FILE} ${TEST_FILE}
  RESULT_VARIABLE DIFFERENT
  )

if(DIFFERENT)
  message(FATAL_ERROR "Test failed - hexd output incorrect")
endif()
"""

def create_file(dirname, filename, text):
	pathname = os.path.join(dirname, filename)
	with open(pathname, "w") as outfile:
		outfile.write(text)
		
# build using cmake
def build_cmake(origindir, sourcedir, builddir):

	cmake_configure = ['cmake', SOURCE_DIR]
	cmake_build = ['cmake', '--build', BUILD_DIR, '--config', 'Debug']

	buildlogfile = os.path.join(origindir, "build.log")
	with open(buildlogfile, "w") as buildlog:
		subprocess.call(cmake_configure, cwd=BUILD_DIR, stdout=buildlog, stderr=buildlog)
		retcode = subprocess.call(cmake_build, stdout=buildlog, stderr=buildlog)

	return retcode

# build using cmake strict
def build_cmake_strict(sourcedir, builddir):

	cmake_configure = ['cmake', '-DWERROR=TRUE', SOURCE_DIR]

	cmake_build = ['cmake', '--build', BUILD_DIR, '--config', 'Debug']

	with open(os.devnull, 'w') as devnull:
		subprocess.call(cmake_configure, cwd=BUILD_DIR,stdout=devnull, stderr=subprocess.STDOUT)
		retcode = subprocess.call(cmake_build, stdout=devnull, stderr=subprocess.STDOUT)

	return retcode

# run ctest
def run_ctest(builddir, test_regexp):
	exe = ['ctest', '-R', test_regexp]
	with open(os.devnull, 'w') as devnull:
		return subprocess.call(exe,cwd=BUILD_DIR, stdout=devnull, stderr=subprocess.STDOUT)
	
# compare text converting CRLF
def check(var, value):
	if sys.platform.startswith('win32'):
		value = value.replace(b'\n', b'\r\n')

	return var == value
	
# assume original source directory is current one
ORIGIN_DIR = os.getcwd()

# logging feedback
feedbackfile = os.path.join(ORIGIN_DIR, "feedback.log")
logging.basicConfig(filename=feedbackfile,level=logging.DEBUG, format='%(message)s')

# make a temporary working directory
WORK_DIR = tempfile.mkdtemp()

# a temporary source directory
SOURCE_DIR = os.path.join(WORK_DIR, "src")

# make a temporary build directory
BUILD_DIR = os.path.join(WORK_DIR, "build")
os.mkdir(BUILD_DIR)
build_ok = False

# copy origin source to temp src directory
shutil.copytree(ORIGIN_DIR, SOURCE_DIR)

# change to the temp source directory
os.chdir(SOURCE_DIR)

# start the grading process
logging.info('\nBegin Grading at %s', str(datetime.now()))
grade = 0

# check that the file hexd.cpp exists
if os.path.isfile("hexd.cpp"):
	logging.info("File hexd.cpp exists.")
	
	# attempt to build the program
	create_file(SOURCE_DIR, "CMakeLists.txt", cmake_text1)
	create_file(os.path.join(SOURCE_DIR,"tests"), "CMakeLists.txt", cmake_text2)
	create_file(os.path.join(SOURCE_DIR,"tests"), "Test.cmake", cmake_text3)
	
	retcode = build_cmake(ORIGIN_DIR, SOURCE_DIR, BUILD_DIR)
	if retcode == 0:
		logging.info("Program Builds.")
		build_ok = True
		
		retcode = run_ctest(BUILD_DIR, "test0")
		if retcode == 0:
			logging.info("Test 0 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 0 failed.")

		retcode = run_ctest(BUILD_DIR, "test1")
		if retcode == 0:
			logging.info("Test 1 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 1 failed.")

		retcode = run_ctest(BUILD_DIR, "test2")
		if retcode == 0:
			logging.info("Test 2 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 2 failed.")

		retcode = run_ctest(BUILD_DIR, "test3")
		if retcode == 0:
			logging.info("Test 3 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 3 failed.")

		retcode = run_ctest(BUILD_DIR, "test4")
		if retcode == 0:
			logging.info("Test 4 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 4 failed.")

		retcode = run_ctest(BUILD_DIR, "test5")
		if retcode == 0:
			logging.info("Test 5 passed. +4")
			grade += 4
		else:
			logging.warning("Error: Test 5 failed.")
			
	else:
		logging.warning("Error: Program failed to build. See build.log for details.")
else:
	logging.warning("Error: File hexd.cpp does not exist. Are you running this from the repository?")

if build_ok:
	# check there are no warnings by building with Werror and check build passes
	# make a temporary build directory
	STRICT_BUILD_DIR = os.path.join(WORK_DIR, "build_strict")
	os.mkdir(STRICT_BUILD_DIR)
	retcode = build_cmake_strict(SOURCE_DIR, STRICT_BUILD_DIR)
	if retcode == 0:
		logging.info("Program Builds with NO WARNINGS. +5")
		grade += 5
	else:
		logging.info("Error: Build has WARNINGS. See build.log")

# check that there are more than 3 commits
exe = ['git', 'rev-list', '--count', 'HEAD']
result = subprocess.Popen(exe, cwd=ORIGIN_DIR, stdout=subprocess.PIPE)
result.wait()

# check if result return code is ok
if result.returncode == 0:
	output = result.stdout.read()
	if int(output) >= 3:
		logging.info("Expected number of commits are present. +1")
		grade += 1
	else:
		logging.warning("Error: Expected more than 2 commits total.")
else:
	logging.warning("Error: Not a git repository or git not in path.")

# log total grade
logging.info("Total Grade %s / 30", grade)

logging.info('End Grading at %s\n', str(datetime.now()))
logging.shutdown()

# cleanup work tree
shutil.rmtree(WORK_DIR)
