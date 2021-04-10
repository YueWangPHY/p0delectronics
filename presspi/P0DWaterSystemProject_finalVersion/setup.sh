#!/bin/bash

#echo We are under: ${PWD}

export HEADDIR
export SOURCEDIR
export BUILDDIR
export SUBMITDIR
export STOREDIR

for dir in ${PWD} \
		 ${PWD}/* \
		 ${PWD}/*/* \
		 ${PWD}/*/* 
do		
if [ -f $dir/setup.sh ]
then 
	HEADDIR=${dir}
fi
done
	

#if [ -d ${PWD}/P0DWaterSystem/ ]
if [ -d ${HEADDIR}/P0DWaterSystem/ ]
then
#	HEADDIR=${PWD}
	SOURCEDIR=${HEADDIR}/P0DWaterSystem/
else
	echo checl where setup.sh is
fi

echo header dir is ${HEADDIR}
echo source code is under ${SOURCEDIR}

if [ -d ${HEADDIR}/build ]
then
	BUILDDIR=${HEADDIR}/build
else
	mkdir build
	BUILDDIR=${HEADDIR}/build
fi

if [ -d ${HEADDIR}/submit ]
then
	SUBMITDIR=${HEADDIR}/submit
fi

if [ -d ${HEADDIR}/storeDepth ]
then
	STOREDIR=${HEADDIR}/storeDepth
else
	mkdir storeDepth
	STOREDIR=${HEADDIR}/storeDepth
fi

echo build dir is ${BUILDDIR}

export PATH=$PATH:${SUBMITDIR}

