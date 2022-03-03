#!/bin/bash

set -x

N=3

sed -n 52,76p > Dockerfile < $0

docker stop $(docker ps -aq) 


echo "/home/david/.ssh/id_rsa" | ssh-keygen -t rsa -b 4096

cp /home/david/.ssh/id_rsa.pub id_rsa.pub

docker rm -f $(docker ps -aq)

docker build -t exercise .

for (( i = 1; i < $N; i++))
do

	docker run -t -d -p 22 --name exercise$i exercise
	echo $i,
done

for (( i = 1; i <= $N; i++))
do

	LOCATION=$(docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' exercise$i)

	ssh-keyscan -t rsa $LOCATION

	ssh user123@$LOCATION	
	
	for (( j = 1; j <= $N; j++))
	do
	
		if [ $i -ne $j ] 
		then
			
			echo $i $j
		fi

	done

done


exit

FROM ubuntu:latest

RUN apt update -y
RUN apt install openssh-server sudo -y
RUN echo 'deb http://archive.ubuntu.com/ubuntu bionic universe' >> /etc/apt/sources.list; apt-get update; apt-get install pssh
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
