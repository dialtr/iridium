#!/bin/bash
#
# bootstrap.sh
# Copyright (C) 2018 The Iridium Authors
# All Rights Reserved
#


#
# Configuration Section: You may potentially want to change these.
#

# The URI to use to download the binutils source.
# Note: ensure that this is compatible with the gcc version.
BINUTILS_SRC_URI="https://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.gz"

# The URI to use to download the gcc source.
# Note: ensure that this is compatible with the binutils version.
GCC_SRC_URI="https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz"

# We unfortunately have to build TexInfo because binutils/gcc won't
# build with the system version.
TEXINFO_SRC_URI="https://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz"

# The root to use for downloading the cross-compilation build setup.
XC_ROOT="xc"

# Concurrency value for make
CONCURRENCY=`cat /proc/cpuinfo | grep processor | wc -l`

#
# Do common setup for installing the cross compilation environment.
#


function setup_xc {
	# Which directory are we putting the source?
  XC_SRC_ROOT="${XC_ROOT}/src"

  # Maybe create the directory to hold the cross compiler source.
	if [ ! -d "${XC_SRC_ROOT}" ]; then
    echo "$0: creating directory for cross compiler source: ${XC_SRC_ROOT}"
	  mkdir -p "${XC_SRC_ROOT}"
  fi

	# Note: this will install the cross compiler for each user. This is
	# probably what we really want. The only time that this would not be
	# appropriate was for systems where a large number of people were
	# using the toolchain. In that case, it should be put into a /opt
	# somewhere.
	# TODO(tdial): Make it possible to install globally.
	export PREFIX="$HOME/opt/cross"
	export TEXINFO_PREFIX="$HOME/opt/texinfo"
	export TARGET=i686-elf
	export PATH="$PREFIX/bin:$TEXINFO_PREFIX/bin:$PATH"
}


function install_debian_packages {
  sudo apt-get install -y build-essential binutils bison make flex \
		libgmp3-dev libmpfr-dev texinfo libmpc-dev libisl-dev          \
		libcloog-isl-dev ncurses-dev lib32stdc++-7-dev xorriso
}


# Helper function to download, extract binutils.
# Note: this can be re-run multiple times if it fails; it will only take
# the actions necessary to ensure that the target task is complete.

function get_binutils {
	# We force wget to download to this version-independent filename.
  BINUTILS_TGZ="${XC_SRC_ROOT}/binutils.tar.gz"

	# We'll force gzip to untar/gzip to this version-independent directory.
  BINUTILS_DIR="${XC_SRC_ROOT}/binutils"
  
	if [ ! -d "${BINUTILS_DIR}" ]; then
	  echo "$0: creating directory for binutils extraction"
		mkdir -p "${BINUTILS_DIR}"
  fi

	# Get the binutils tarball unless we have it already.
	if [ ! -f "${BINUTILS_TGZ}" ]; then
		echo "$0: downloading binutils from ${BINUTILS_SRC_URI}"
    wget "${BINUTILS_SRC_URI}" -O "${BINUTILS_TGZ}"
	fi

	# Unzip / untar unless we've already done so (we use md5.sum as an indicator)
	if [ ! -f "${BINUTILS_DIR}/md5.sum" ]; then
		echo "$0: extracting binutils into target directory"
	  tar -xzf "${BINUTILS_TGZ}" -C "${BINUTILS_DIR}" --strip-components 1
  fi
}


function get_texinfo {
	# We force wget to download to this version-independent filename.
  TEXINFO_TGZ="${XC_SRC_ROOT}/texinfo.tar.gz"

	# We'll force gzip to untar/gzip to this version-independent directory.
  TEXINFO_DIR="${XC_SRC_ROOT}/texinfo"
  
	if [ ! -d "${TEXINFO_DIR}" ]; then
	  echo "$0: creating directory for texinfo extraction"
		mkdir -p "${TEXINFO_DIR}"
  fi

	# Get the texinfo tarball unless we have it already.
	if [ ! -f "${TEXINFO_TGZ}" ]; then
		echo "$0: downloading texinfo from ${TEXINFO_SRC_URI}"
    wget "${TEXINFO_SRC_URI}" -O "${TEXINFO_TGZ}"
	fi

	# Unzip / untar unless we've already done so (we use md5.sum as an indicator)
	if [ ! -f "${TEXINFO_DIR}/md5.sum" ]; then
		echo "$0: extracting texinfo into target directory"
	  tar -xzf "${TEXINFO_TGZ}" -C "${TEXINFO_DIR}" --strip-components 1
  fi
}


# Helper function to download, extract gcc.
# Note: this can be re-run multiple times if it fails; it will only take
# the actions necessary to ensure that the target task is complete.
# TODO(tdial): This is cut & paste from the binutils function. Refactor.

function get_gcc {
	# We force wget to download to this version-independent filename.
  GCC_TGZ="${XC_SRC_ROOT}/gcc.tar.gz"

	# We'll force gzip to untar/gzip to this version-independent directory.
  GCC_DIR="${XC_SRC_ROOT}/gcc"
  
	if [ ! -d "${GCC_DIR}" ]; then
	  echo "$0: creating directory for gcc extraction"
		mkdir -p "${GCC_DIR}"
  fi

	# Get the gcc tarball unless we have it already.
	if [ ! -f "${GCC_TGZ}" ]; then
		echo "$0: downloading gcc from ${GCC_SRC_URI}"
    wget "${GCC_SRC_URI}" -O "${GCC_TGZ}"
	fi

	# Unzip / untar unless we've already done so (we use MD5SUMS as an indicator)
	if [ ! -f "${GCC_DIR}/MD5SUMS" ]; then
		echo "$0: extracting gcc into target directory"
	  tar -xzf "${GCC_TGZ}" -C "${GCC_DIR}" --strip-components 1
  fi
}


function make_binutils {
	# Save current working directory
	pushd `pwd`
	
	# TODO(tdial): This script assumes that get_binutils has succeeded.
	
	# Create directory to hold the build target.
	BUILD_TARGET="${XC_ROOT}/targets/binutils"
	mkdir -p "${BUILD_TARGET}"
	cd "${BUILD_TARGET}"
	
	# Configure
	../../src/binutils/configure --target=$TARGET --prefix=$PREFIX \
		--with-sysroot --disable-nls --disable-werror

	# Build binutils and install it locally.
  make -j$CONCURRENCY
	make install

	# Restore directory
	popd
}


function make_gcc {
	pushd `pwd`

	# TODO(tdial): This script assumes that make_binutils has succeeded.

	# Create directory to hold the build target.
	BUILD_TARGET="${XC_ROOT}/targets/gcc"
	mkdir -p "${BUILD_TARGET}"

	# TODO(tdial): Check that binutils directory has the assembler.
	which -- $TARGET-as || echo "$TARGET-as is not in the path"

	cd "${BUILD_TARGET}"
	../../src/gcc/configure --target=$TARGET --prefix="$PREFIX" \
		--disable-nls --enable-languages=c,c++ --without-headers
 
	make -j$CONCURRENCY
	make install

	#make -j$CONCURRENCY all-gcc
	#make -j4 all-target-libgcc

	#make install-host
	#make install-target-libgcc

	popd
}


function make_texinfo {
	pushd `pwd`

	# TODO(tdial): This script assumes that get_texinfo has succeeded.

	# Create directory to hold the build target.
	BUILD_TARGET="${XC_ROOT}/targets/texinfo"
	mkdir -p "${BUILD_TARGET}"

	# Configure
	cd "${BUILD_TARGET}"
	../../src/texinfo/configure --prefix="$TEXINFO_PREFIX"
 
	make -j4 
	make install

	popd
}


function post_build_message {
	echo ""
  echo "Cross compilation environment build complete."
	echo "You must add the cross compiler to the path to use it:"
	echo ""
	echo " export PATH=$PREFIX/bin:\$PATH"
	echo ""
	echo "Then ensure it works by running:"
	echo ""
	echo " $TARGET-gcc --version"
	echo ""
}

#
# Main
#

setup_xc
install_debian_packages

#get_texinfo
#make_texinfo

get_binutils
get_gcc

make_binutils
make_gcc

post_build_message
