#!/bin/sh

cd $(dirname "$0")
cd ..
BASEDIR=$(pwd)

if [ ! -d $BASEDIR/tmp ]; then
    mkdir "$BASEDIR/tmp"
fi

/usr/bin/env DYLD_LIBRARY_PATH=/usr/local/lib/ \
    spawn-fcgi \
    -s $BASEDIR/tmp/1Q.sock \
    $BASEDIR/build/1Q
/usr/bin/env BASEDIR=$BASEDIR envsubst < $BASEDIR/config/nginx.conf.template > $BASEDIR/tmp/nginx.conf
/usr/bin/env nginx -c $BASEDIR/tmp/nginx.conf