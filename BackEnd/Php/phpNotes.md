# EnvSetup

There are 2 popular options of setting up the development

1. XAMPP, the most popular php development platform
2. Docker.

> Since a php application requires database and frontend, the whole application requires multiple services. Hence [docker compose](https://docs.docker.com/compose/) is ued.


PHP-FastCGI Process Manager: PHP-FPM is a cgi for nginx as nginx doesn't support php.

> Generally, web servers use integrated modules to compile PHP scripts, such as Common Gateway Interface (CGI) or single user PHP (suPHP). Web servers leveraging these handlers pair with processing PHP scripts, then compile and execute them as part of their standard processes when responding to traffic. To execute, they use the server process’s ownership and permission configurations. This creates a stable method of using PHP scripts.

> But PHP-FPM is designed to fill the gaps in other PHP handlers. The work is handled by a separate service that was created exclusively to process PHP scripts. It’s arranged as a master process handling singular worker processes in pools. Whenever the server gets a PHP script request, it utilizes a proxy, FastCGI connection to pass that request on to the PHP-FPM service.

[Build a Full Stack Web App in PHP and MySQL with Docker from scratch!](https://www.youtube.com/watch?v=2Bxh5FNGznQ)



