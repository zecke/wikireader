# Makefile
#
# Copyright (c) 2010 Openmoko Inc.
#
# Authors   Christopher Hall <hsw@openmoko.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# +++START_UPDATE_MAKEFILE: Start of auto included code
# The text between the +++ and --- tags is copied by the
# UpdateMakefiles script. Do not remove or change these tags.
# ---
# Autodetect root directory
define FIND_ROOT_DIR
while : ; do \
  d=$$(pwd) ; \
  [ -d "$${d}/samo-lib" ] && echo $${d} && exit 0 ; \
  [ X"/" = X"$${d}" ] && echo ROOT_DIRECTORY_NOT_FOUND && exit 1 ; \
  cd .. ; \
done
endef
ROOT_DIR := $(shell ${FIND_ROOT_DIR})
# Directory of Makefile includes
MK_DIR   := ${ROOT_DIR}/samo-lib/Mk
# Include the initial Makefile setup
include ${MK_DIR}/definitions.mk
# ---END_UPDATE_MAKEFILE: End of auto included code


INCLUDES += -I${SAMO_LIB_INCLUDE}
INCLUDES += -I${GRIFO_INCLUDE}
INCLUDES += -I${MINI_LIBC_INCLUDE}

LIBS += lib/libapplication.a
LIBS += ${GRIFO_LIB}
LIBS += ${MINI_LIBC_LIB}
LIBS += $(shell $(CC) -print-libgcc-file-name)

LDFLAGS += -static --strip-all -s --no-gc-sections -N

BUILD_PREFIX := build/

INCLUDES += -I${BUILD_PREFIX}

# main target (must be the only target in this file)
.PHONY: all
all:  build-targets
