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
