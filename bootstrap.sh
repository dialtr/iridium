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
# Dependent Variables: These depend on config vars. above. Don't change.
#

XC_SRC_ROOT="${XC_ROOT}/src"


# Helper function to download, extract binutils.
# Note: this can be re-run multiple times if it fails; it will only take
# the actions necessary to ensure that the target task is complete.

function get_binutils {
  # Maybe a directory to hold the tar/gzip source.
	if [ ! -d "${XC_SRC_ROOT}" ]; then
    echo "$0: creating directory for binutils source: ${XC_SRC_ROOT}"
	  mkdir -p "${XC_SRC_ROOT}"
  fi

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

# "main"
get_binutils

