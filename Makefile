include $(THEOS)/makefiles/common.mk

CPP:=/bin/false
CXX:=/bin/false
DEBUG:=1
messages:=yes

TOOL_NAME = myassert

myassert_FILES += main.c
myassert_FILES += myassert.c
myassert_CFLAGS = -fobjc-arc
myassert_CODESIGN_FLAGS = -Sentitlements.plist
myassert_INSTALL_PATH = /usr/local/bin

include $(THEOS_MAKE_PATH)/tool.mk

purge:
	$(MAKE) clean
	rm -rf packages/ .theos/obj/

# ios.bashrc: export -f <function>
transfer:
	@ssh2 'sh -c "test $$(whoami) = mobile"'
	@ssh2 rm -fv /private/var/mobile/$(TOOL_NAME)
	scp2 .theos/obj/debug/$(TOOL_NAME)

ALL_OBJCFLAGS:=-Wall -Wextra -g $(ALL_OBJCFLAGS) -UNDEBUG -UNS_BLOCK_ASSERTIONS # -Wno-error -Wdeprecated-declarations
ALL_CFLAGS:=-Wall -Wextra -g $(ALL_CFLAGS) -UNDEBUG # -E -Wno-error -Wunused-parameter
