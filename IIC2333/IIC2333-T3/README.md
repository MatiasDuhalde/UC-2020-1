# Integrantes
 - Javier Paravich / 15621057
 - Matías Duhalde / 18639496

# Introducción
 - Hola! Consideramos que la topología de la red es bastante auto-descriptiva, y tiene notas dentro del archivo que describen qué corresponde a qué. De este README, es importante que lean la parte **Consideraciones Generales**, que contiene detalles relevantes de la tarea. Si alguna parte llega a ser poco clara, también se describen cada una de las redes parte por parte en la sección **Detalles**.

# Detalles
## Red Canvas (192.168.1.0/24)
 - Las direcciones IP fueron asignadas estáticamente.
 - `Canvas Server`:
     - Posee la IP `192.168.1.2`
     - Hostea la página pedida en el enunciado (`www.canvas.com`).
         - Pusimos [este anuncio](https://cursos.canvas.uc.cl/courses/5536/discussion_topics/114336) como index de está página. Se puede demorar un poco en cargar ^-^
     - Este servidor bloquea los host provenientes de `192.168.2.0` (red Mi Casa) mediante una regla de excepción (fue configurada en Desktop -> Firewall). Todas las otras redes deberían tener acceso normal a este servidor.
 - `Canvas Gateway Router`:
     - Posee la IP `192.168.1.1`
     - Está conectado directamente a la red DNS y la red Mi Casa, y a través de sus gateway routers se puede acceder a la red UC.
 - Dispositivos inalámbricos:
     - Se conectaron 3 dispositivos inalámbricos mediante un access point conectado a un switch.
     - La SSID es `canvas`, y la contraseña es `password` (WPA2-PSK AES)
     - Las IPs de los dispositivos corresponden a `192.168.1.10-12`

## Red Mi Casa (192.168.2.0/24)
 - `Mi Casa Gateway Router`:
     - Posee la IP `192.168.2.1`
     - Está conectado directamente a la red Canvas y la red UC, y a través de sus gateway routers se puede acceder a la red DNS.
 - Usuarios:
     - Se conectaron 3 usuarios mediante un switch.
     - Las IPs de los dispositivos corresponden a `192.168.2.10-12`

## Red UC (192.168.3.0/24)
 - `UC Server`:
     - Posee la IP `192.168.3.2`
     - Hostea la página pedida en el enunciado (`iic2333.ing.puc.cl`).
         - Pusimos [la página oficial del curso](iic2333.ing.puc.cl) cómo index, se puede demorar en cargar un poco ^-^.
         - El botón `Ir`, abajo de `Sitio Canvas`, conecta a la página `www.canvas.com` (igual que la página real :o).
     - Este servidor configura el DHCP (configurado en Services -> DHCP). Cumple las especificaciones del enunciado.
 - `UC Gateway Router`:
     - Posee la IP `192.168.3.1`
     - Está conectado directamente a la red DNS y la red Mi Casa, y a través de sus gateway routers se puede acceder a la red Canvas.
 - Usuarios:
     - Se conectaron 2 usuarios por red inalámbrica (a través de un access point conectado al switch principal), y 2 por red cableada directamente al switch principal.
     - Para la red inalámbrica, la SSID es `eduroam`, y la contraseña es `password` (WPA2-PSK AES).
     - Las direcciones IP de estos usuarios se asignan por medio de DHCP.

## Red DNS (2.2.0.0/16)
 - Las direcciones IP fueron asignadas estáticamente.
 - `DNS Server`:
     - Posee la IP `2.2.0.2`
     - Posee las siguientes entradas en su tabla DNS:
        - `A` - `www.canvas.com` - `192.168.1.2`
        - `A` - `iic2333.ing.puc.cl` - `192.168.3.2`
        - `CNAME` - `canvas.com` - `www.canvas.com`
 - `DNS Gateway Router`:
     - Posee la IP `2.2.0.1`
     - Está conectado directamente a la red Canvas y la red UC, y a través de sus gateway routers se puede acceder a la red Mi Casa.


# Consideraciones Generales
 - Este diseño posee el problema con las tablas ARP que se describía en varias issues: los primeros ping fallan, puesto que las tablas ARP no tienen las entradas correspondientes. Al fallar, se generan automáticamente ARP Queries, las cuales obtienen las entradas correspondientes, y los pings subsecuentes no deberían tener problemas para llegar a su destino (siempre que los hosts que se encuentran entre los dos nodos posean las entradas correctas en sus tablas ARP).
 - La forma más fácil de generar estos pings es mediante la consola de los hosts (por ejemplo, en un PC en Desktop -> Command Line), usando el comando `ping <destinatario>`.
 - Conectarse a los servidores HTTP mediante el navegador se demora bastante (debido a que los contenidos de las páginas son relativamente grandes), por lo que si durante la corrección van a acceder repetidas veces a estos servidores, es recomendable que cambien los contenidos de los archivos `index.html` de cada página a algo más "ligero" (como los ejemplos del enunciado).

 PD: gracias a Ariel y Raimundo por la ayudantía extra!