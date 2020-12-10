#!/bin/bash

for i in $(seq 50 140); do
  wget http://hpiers.obspm.fr/iers/bul/buld/bulletind.${i}
  echo "wget http://hpiers.obspm.fr/iers/bul/buld/bulletind.${i}"
done
