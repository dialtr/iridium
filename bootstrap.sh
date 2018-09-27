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
GCC_SRC_URI="https://ftp.gnu.org/gnu/gcc/gcc-4.7.3/gcc-4.7.3.tar.gz"

# The root to use for downloading the cross-compilation build setup.
XC_ROOT="xc"


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
}


# Helper function to download, extract binutils.
# Note: this can be re-run multiple times if it fails; it will only take
# the actions necessary to ensure that the target task is complete.

function get_binutils {
	# If this function is to run independently, we must have the src dir.
	setup_xc

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


# Helper function to download, extract gcc.
# Note: this can be re-run multiple times if it fails; it will only take
# the actions necessary to ensure that the target task is complete.
# TODO(tdial): This is cut & paste from the binutils function. Refactor.

function get_gcc {
	# If this function is to run independently, we must have the src dir.
	setup_xc

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


# "main"
get_binutils
get_gcc
