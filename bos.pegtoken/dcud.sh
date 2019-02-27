#!/bin/sh
cd /data3/flash/bos.pegtoken
docker-compose -f docker-compose.yml up -d 
docker-compose exec cdt /bin/sh /data3/flash/build-testnet.sh
docker-compose down
