# BASE IMAGE
FROM ubuntu:latest

# METADATA : Info about container creater
LABEL maintainer="vishal"
LABEL description="Ubuntu with SSH support"

RUN DEBIAN_FRONTEND=noninteractive apt update && apt install -y \
    openssh-server \
    sudo \
    vim \
    curl \
    build-essential \
    g++ \
    cmake \
    gcc

# MAKE SSH DIRECTORY
RUN mkdir /var/run/sshd

# Creates a user - vishal with a home directory and bash shell
# password = vishal1234
# gives sudo(root) access to vishal
RUN useradd -m -s /bin/bash vishal && \
    echo 'vishal:vishal1234' | chpasswd && \
    adduser vishal sudo

# CONFIGURE SSH FOR PASSWORD LOGIN 
# sed is stream editor : it looks for specific string and make changes to it
# here it looks for "#PassAuth yes" and change into PassAuth yes : uncomment it
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
    sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config 
#! Root login using password is not recomended in production phase

# EXPOSE PORT
EXPOSE 22

# COMMAND TO RUN WHEN CONTAINER STARTS
CMD [ "/usr/sbin/sshd" , "-D" ]

