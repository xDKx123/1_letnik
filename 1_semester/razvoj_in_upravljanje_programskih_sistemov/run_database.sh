docker run -p 5434:5432 --name rups_database -e POSTGRES_USER=postgres -e POSTGRES_PASSWORD=postgres -d postgres || docker start rups_database
