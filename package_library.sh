#!/usr/bin/env bash
LIBRARY_OUTPUT_FOLDER=lib
LIBRARY=libstackjitvm.a
LIBRARY_BUILD_FOLDER=bin

rm -rf ${LIBRARY_OUTPUT_FOLDER}
mkdir -p ${LIBRARY_OUTPUT_FOLDER}
mkdir -p ${LIBRARY_OUTPUT_FOLDER}/stackjit
cp ${LIBRARY_BUILD_FOLDER}/${LIBRARY} ${LIBRARY_OUTPUT_FOLDER}/${LIBRARY}
find src/ -name '*.h*' | cpio -pdm ${LIBRARY_OUTPUT_FOLDER}/stackjit
mv -f ${LIBRARY_OUTPUT_FOLDER}/stackjit/src/* ${LIBRARY_OUTPUT_FOLDER}/stackjit
rmdir ${LIBRARY_OUTPUT_FOLDER}/stackjit/src
cp -r rtlib ${LIBRARY_OUTPUT_FOLDER}