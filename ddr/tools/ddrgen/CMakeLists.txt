###############################################################################
# Copyright IBM Corp. and others 2017
#
# This program and the accompanying materials are made available under
# the terms of the Eclipse Public License 2.0 which accompanies this
# distribution and is available at http://eclipse.org/legal/epl-2.0
# or the Apache License, Version 2.0 which accompanies this distribution
# and is available at https://www.apache.org/licenses/LICENSE-2.0.
#
# This Source Code may also be made available under the following Secondary
# Licenses when the conditions for such availability set forth in the
# Eclipse Public License, v. 2.0 are satisfied: GNU General Public License,
# version 2 with the GNU Classpath Exception [1] and GNU General Public
# License, version 2 with the OpenJDK Assembly Exception [2].
#
# [1] https://www.gnu.org/software/classpath/license.html
# [2] https://openjdk.org/legal/assembly-exception.html
#
# SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
###############################################################################

omr_add_executable(omr_ddrgen
	ddrgen.cpp
)

set_property(
	TARGET omr_ddrgen
	PROPERTY CXX_STANDARD 11
)

target_link_libraries(omr_ddrgen
	omr_ddr_base
	omr_ddr_blobgen
	omr_ddr_ir
	omr_ddr_macros
	omr_ddr_scanner
	omrport
	j9thrstatic
)

if(OMRPORT_OMRSIG_SUPPORT)
	target_link_libraries(omr_ddrgen omrsig)
	if(OMR_OS_AIX)
		# make sure that omrsig can be found when ddrgen is run
		# ideally we would set the BUILD_RPATH, but that doesn't exist in cmake 3.4
		get_target_property(omrsig_dir omrsig RUNTIME_OUTPUT_DIRECTORY)

		set_target_properties(omr_ddrgen PROPERTIES
			BUILD_WITH_INSTALL_RPATH TRUE
			INSTALL_RPATH "${omrsig_dir}"
		)
	endif()
endif()

if((OMR_TOOLCONFIG STREQUAL "gnu") AND (NOT OMR_OS_OSX))
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-static-libstdc++" ALLOWS_STATIC_LIBCPP)
	if(ALLOWS_STATIC_LIBCPP)
		set_property(
			TARGET omr_ddrgen
			APPEND_STRING PROPERTY LINK_FLAGS " -static-libstdc++")
	endif()
endif()
