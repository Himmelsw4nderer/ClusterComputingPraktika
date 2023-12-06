FROM alpine:latest

EXPOSE 8080

RUN apk update &&\
 apk upgrade &&\
 apk add lighttpd

COPY lighttpd.conf /etc/lighttpd/lighttpd.conf

COPY index.html /var/www/localhost/htdocs/index.html

CMD lighttpd -D -f /etc/lighttpd/lighttpd.conf
