FROM --platform=linux/amd64 ubuntu:22.10

RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y git cmake gdb build-essential clang \
    clang-tidy clang-format gcc-doc pkg-config glibc-doc tcpdump tshark && \
    apt upgrade -y && \
    apt autoremove -y
