#!/bin/bash
set -x
docker run -p 5434:5432 --name vaja_2_splet -e POSTGRES_USER=postgres -e POSTGRES_PASSWORD=postgres -d postgres || docker start vaja_2_splet
