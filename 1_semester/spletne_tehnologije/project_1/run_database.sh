#!/bin/bash
set -x
docker run -p 5433:5432 --name vaja_1_splet -e POSTGRES_USER=postgres -e POSTGRES_PASSWORD=postgres -d postgres || docker start vaja_1_splet
