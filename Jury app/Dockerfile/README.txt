cd to-this-directory

docker build -t postgresql .

docker run --rm -P --name postgre_db postgresql

docker run --rm -t -i --link postgre_db:pg postgresql bash

psql -h $PG_PORT_5432_TCP_ADDR -p $PG_PORT_5432_TCP_PORT -d docker -U docker --password