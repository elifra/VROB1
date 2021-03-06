#############################################################################
#
# $Id: cmake_uninstall.cmake.in,v 1.1.1.1 2007/02/06 10:47:23 fspindle Exp $
#
# Copyright (C) 1998-2006 Inria. All rights reserved.
#
# This software was developed at:
# IRISA/INRIA Rennes
# Projet Lagadic
# Campus Universitaire de Beaulieu
# 35042 Rennes Cedex
# http://www.irisa.fr/lagadic
#
# This file is part of the ViSP toolkit
#
# This file may be distributed under the terms of the Q Public License
# as defined by Trolltech AS of Norway and appearing in the file
# LICENSE included in the packaging of this file.
#
# Licensees holding valid ViSP Professional Edition licenses may
# use this file in accordance with the ViSP Commercial License
# Agreement provided with the Software.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# Contact visp@irisa.fr if any conditions of this licensing are
# not clear to you.
#
# Description:
# Comes from http://www.cmake.org/Wiki/CMake_FAQ to create an uninstall target
#
# Authors:
# Fabien Spindler
#
#############################################################################

IF(NOT EXISTS "/home/thomas/Documents/VROB1/VROB-code/install_manifest.txt")
  #MESSAGE("Cannot find install manifest: \"/home/thomas/Documents/VROB1/VROB-code/install_manifest.txt\"")
  MESSAGE("There is no files to uninstall")
ELSE(NOT EXISTS "/home/thomas/Documents/VROB1/VROB-code/install_manifest.txt")
  FILE(READ "/home/thomas/Documents/VROB1/VROB-code/install_manifest.txt" files)
  STRING(REGEX REPLACE "\n" ";" files "${files}")
  FOREACH(file ${files})
    MESSAGE(STATUS "Uninstalling \"${file}\"")
    IF(EXISTS "${file}")
      EXEC_PROGRAM(
        "/usr/bin/cmake" ARGS "-E remove \"${file}\""
        OUTPUT_VARIABLE rm_out
        RETURN_VALUE rm_retval
        )
      IF("${rm_retval}" STREQUAL 0)
      ELSE("${rm_retval}" STREQUAL 0)
        MESSAGE(FATAL_ERROR "Problem when removing \"${file}\"")
      ENDIF("${rm_retval}" STREQUAL 0)
    ELSE(EXISTS "${file}")
      MESSAGE(STATUS "File \"${file}\" does not exist.")
    ENDIF(EXISTS "${file}")
  ENDFOREACH(file)

ENDIF(NOT EXISTS "/home/thomas/Documents/VROB1/VROB-code/install_manifest.txt")
