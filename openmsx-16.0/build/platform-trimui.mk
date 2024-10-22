# Configuration for Trimui Smart Pro

# Set CXX before including platform-linux.mk (see comments in platform-linux.mk)
CXX:=/opt/aarch64-linux-gnu-7.5.0-linaro/bin/aarch64-linux-gnu-g++

include build/platform-linux.mk

USE_SYMLINK:=false

# Build with OpenGL ES and Laserdisc support.
LINK_MODE:=3RD_STA_GLES
