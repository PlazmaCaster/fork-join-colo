#!/bin/bash

# Copy the all alogrithms graphs from a directory to the proper location in
# the document build tree

function usage {
	src=`basename $0`
cat <<EOF
${src} <OUTPUT DIRECTORY> <DOCUMENT ROOT>

Copies the graphs related to the proof of context into the
document build tree at the correct location. If <DOCUMENT ROOT> is not
specified a guess is made and interactively verified.
EOF
}

# selection of graphs
sel=(
	fjtasks/task-484/graphs/task-484-per-core-composite.eps
	fjtasks/task-791/graphs/task-791-per-core-composite.eps
	fjtasks/task-956/graphs/task-956-per-core-composite.eps
	mrtc-base-incr.tex
    )

ODIR=${1}
DDIR=${2:-../../oleaf.git/}
evaldir=$3

if [ "$3" == "quick" ] 
then
	sel+=(
		prev-mrtc-base-incr.tex
	)
else
	sel+=(
		mrtc-base-incr.tex
	)
fi

if [ "${ODIR}" == "" ] ; then
	echo "An output directory must be supplied"
	usage
	exit -1
fi

ODIR=${ODIR}/
for file in ${sel[@]} ; do
	path=${ODIR}/${file}
	if [ -f ${path} ] ; then  
	   echo $path exists
	fi
done

echo $DDIR

if [ ! -d ${DDIR} ] ; then
	echo "A document root is required [$DDIR]"
	usage
	exit -1
fi

DDIR=${DDIR}/${evaldir}/
echo ${DDIR} exists
echo $3
mkdir -p ${DDIR}


for file in ${sel[@]} ; do
	src=$2
	src+="/simul/"
	src+=$file
	dst=${DDIR}/
	dst+=$(basename $file)

	if [ -e ${src} ]
	then
		echo "${src} -> ${dst}"
		cp ${src} ${dst}
	fi
done