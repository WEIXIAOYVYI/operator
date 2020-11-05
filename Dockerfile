FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc d.c -o d
RUN chmod +x d
