#!/bin/bash
set -x
#docker run -p 5433:5432 --name vaja_1_splet -e POSTGRES_USER=postgres -e POSTGRES_PASSWORD=postgres -d postgres || docker start vaja_1_splet
docker start vaja_1_splet

touch run_frontend.sh
chmod +x run_frontend.sh

echo -e "#!/bin/bash\nset -x\ncd frontend2\npwd\n./run_frontend.sh" > run_frontend.sh

gnome-terminal -x ./run_frontend.sh

cd /opt/idea-IU-212.5284.40/bin
gnome-terminal -x ./idea.sh
