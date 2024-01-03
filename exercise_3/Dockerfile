FROM python:3.12-slim
LABEL authors="krishna"

RUN groupadd --force swpc
RUN useradd --create-home --shell /bin/bash --gid swpc swpc
RUN echo 'swpc:swpc' | chpasswd

RUN usermod -aG sudo swpc
RUN mkdir -p /etc/sudoers.d
RUN echo "swpc	ALL=(ALL:ALL) ALL" > /etc/sudoers.d/swpc
RUN chmod 400 /etc/sudoers.d/swpc

WORKDIR /home/swpc

RUN apt-get -y update
RUN apt-get -y install gcc python3-dev curl sudo vim procps iproute2

COPY requirements.txt .
RUN pip install --no-cache --upgrade pip wheel
RUN pip install --requirement requirements.txt
RUN rm -f requirements.txt

RUN mkdir packages
COPY dist/* packages/
RUN pip install --no-cache --upgrade packages/swpctools*
RUN rm -rf packages

RUN apt-get -y purge gcc python3-dev

RUN mkdir /var/lib/swpc
RUN chmod 700 /var/lib/swpc
RUN chown -R swpc:swpc /var/lib/swpc

RUN mkdir /var/log/swpc
RUN chmod 700 /var/log/swpc
RUN chown -R swpc:swpc /var/log/swpc

USER swpc:swpc

ENTRYPOINT ["swpctools", "as-local-service", "--datapath=/var/lib/swpc", "--logspath=/var/log/swpc"]
