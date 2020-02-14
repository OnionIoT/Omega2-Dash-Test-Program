# Copyright (C) 2020 Onion Corporation
#
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
PKG_NAME:=omega2-dash-test-program
PKG_VERSION:=0.0.1
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_VERSION:=HEAD  # latest commit from master branch
PKG_SOURCE_URL:=https://github.com/OnionIoT/Omega2-Dash-Test-Program.git
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk


# application package
define Package/omega2-dash-test-program
	SECTION:=onion
	CATEGORY:=Onion
	SUBMENU:=Utilities
	TITLE:=A program to test Omega2 Dash during manufacturing
endef

define Package/omega2-dash-test-program/description
A program to test Omega2 Dash during manufacturing
endef


# TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
# TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib

# define Build/Compile
# 	$(MAKE) -C $(PKG_BUILD_DIR)/ \
# 	CC="$(TARGET_CC)" \
# 	CFLAGS="$(TARGET_CFLAGS)" \
# 	LDFLAGS="$(TARGET_LDFLAGS)"
# endef

define Package/omega2-dash-test-program/install
	$(INSTALL_DIR) $(1)/usr/bin
	# install the binary
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/bin/output $(1)/usr/bin/omega2-dash-test-program
endef

$(eval $(call BuildPackage,$(PKG_NAME)))