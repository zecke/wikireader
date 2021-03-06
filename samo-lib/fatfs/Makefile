# Copyright (c) 2009 Openmoko Inc.
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


INCLUDES = -I${MINI_LIBC_INCLUDE}
INCLUDES += -I${FATFS_INCLUDE}
INCLUDES += -I${DRIVERS_INCLUDE}
INCLUDES += -I${SAMO_LIB_INCLUDE}


vpath %.c src

TYPE_LIST = read-only read-write

TARGETS = all

.PHONY: all
all: $(foreach type, ${TYPE_LIST}, lib/${type}/libtinyfat.a)

define BUILD
lib/$(strip ${1}):
	$${RM} -r $$@
	mkdir -p $$@

lib/$(strip ${1})/libtinyfat.a: lib/$(strip ${1})

build-$(strip ${1}): Makefile
	$${RM} -r $$@
	mkdir -p $$@
	@echo SAMO_LIB = $${SAMO_LIB} >> $$@/Makefile
	@echo include $${MK_DIR}/definitions.mk >> $$@/Makefile
	@echo INCLUDES = $${INCLUDES} | sed 's@\.\./\.\./@../../../@g' >> $$@/Makefile
	@echo vpath %.c ../src >> $$@/Makefile
	@echo INCLUDES += -I../config/c33/$(strip ${1})/ >> $$@/Makefile
	@echo TARGETS = all >> $$@/Makefile
	@echo include $${SAMO_LIB}/Mk/rules.mk >> $$@/Makefile
endef

# macros to generate rules

MAKE_RULE = $(eval $(call MAKE_RULE1,${1},${2}))

define MAKE_RULE1
lib/$(strip ${1})/libtinyfat.a: build-$(strip ${1})/$(strip ${2})

build-$(strip ${1})/$(strip ${2}): build-$(strip ${1})
	$${MAKE} -C build-$(strip ${1}) ${2}
	$${AR} r lib/$(strip ${1})/libtinyfat.a $$@
endef


# master rules

$(foreach type, ${TYPE_LIST}, $(eval $(call BUILD,${type})))

# create all the individual object file rules

$(call MAKE_RULE,read-only,tff.o)
# $(call MAKE_RULE,read-only,mmc.o)

$(call MAKE_RULE,read-write,tff.o)
# $(call MAKE_RULE,read-write,mmc.o)
$(call MAKE_RULE,read-write,GetFATTime.o)

clean:
	$(RM) *.[do] *.asm33
	$(RM) -r $(foreach type, ${TYPE_LIST}, build-${type})
	$(RM) $(foreach type, ${TYPE_LIST}, lib/${type}/libtinyfat.a)
	${RM} -r lib

include ${MK_DIR}/rules.mk
