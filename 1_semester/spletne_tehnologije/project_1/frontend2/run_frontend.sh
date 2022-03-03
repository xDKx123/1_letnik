#!/bin/bash
set -x
code .
echo -e '#!/bin/bash\n python3 -m http.server 1245' > http_server.sh
chmod +x http_server.sh
gnome-terminal -x ./http_server.sh

xdg-open http://localhost:1245/todoListView.html
