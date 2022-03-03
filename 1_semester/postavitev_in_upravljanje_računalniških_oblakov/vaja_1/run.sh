#!/bin/bash

set -x

sed -n 31,54p > Dockerfile < $0

docker stop $(docker ps -aq) 


echo "/home/david/.ssh/id_rsa" | ssh-keygen -t rsa -b 4096

cp /home/david/.ssh/id_rsa.pub id_rsa.pub

#docker rm -f $(docker ps -aq)

docker build -t exercise1 .

#docker start exercise
#docker start -it exercise
docker run -t -d -p 22 --name exercise exercise1


LOCATION=$(docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' exercise)

ssh-keyscan -t rsa $LOCATION

ssh user123@$LOCATION

exit

FROM ubuntu:latest

RUN apt update -y
RUN apt install openssh-server sudo -y
RUN apt upgrade -y
RUN apt update -y

RUN useradd -m -s /bin/bash user123
RUN echo 'user123:password' | chpasswd

COPY id_rsa.pub /home/user123/.ssh/authorized_keys

RUN chown -R user123:user123 /home/user123/.ssh
RUN chmod 600 /home/user123/.ssh/authorized_keys

RUN systemctl enable ssh
RUN service ssh start

RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

#RUN systemctl restart ssh


ENTRYPOINT service ssh start && bash
