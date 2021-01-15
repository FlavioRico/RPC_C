# RPC_C
Micro Uber using RPC and IDL with C language.
 
# Description
En este proyecto se hace uso de RPC combinado con el lenguaje C e IDL para crear una simulación de la aplicación Uber a menor escala. Se cuenta con un servidor y la posibilidad de la existencia de distintos clientes que ejecuten peticiones para solicitar un viaje.
 
# Project requirements
El compilador GCC
Contar con rpcbind o ejecutar los siguientes comandos en caso de no contar con rpcbind:
  1) sudo apt update
  2) sudo apt install rpcbind
  
# Steps to clone the project
(with HTTPS)
git clone https://github.com/FlavioRico/RPC_C.git

(with SSH)
git clone git@github.com:FlavioRico/RPC_C.git
 
# Compile and excecute project
Verificar que el servicio rpcbind se encuentre activo con el siguiente comando:
    sudo service rpcbind status
En caso de que el servicio no se encuentre activo se requiere ejecutar el siguiente comando:
    sudo service rpcbind start
Para compilar el cliente, abrir una términal y ejecutar el siguiente comando:
    gcc requests_client.c requests_clnt.c requests_xdr.c -o e_client
Para compilar el servidor, abrir una términal y ejecutar el siguiente comando:
    gcc requests_server.c requests_svc.c requests_xdr.c -lm -o e_server    
Primero ejecutar el servidor con el comando:
    ./e_server
Después ejecutar el cliente con el comando (se pueden abrir más términales y ejecutar distintos clientes):
    ./e_client localhost
 
# Important notes
El script "requests.x" contiene la declaración de las funciones que se utilizarán para comunicar el cliente y el servidor, así como los datos compuestos que serán enviados por parámetro en las funciones.
Los scripts "requests.h, requests.xdr.c requests_clnt.c requests_svc.c" son generados automáticamente con RPC utilizando el script "requests.x" para definir las estructuras y funciones indicadas en dicho script; de igual forma, la bandera "-a" nos ayuda a generar una plantilla automática en la cual solamente nos dedicaremos a escribir la lógica del proyecto. (rpcgen -a -C requests.x).
Cuando compilamos tanto cliente como servidor, es importante incluir el script generado "requests_xdr.c" debido a que se utilizan datos compuestos en IDL, RPC requiere este archivo con definiciones específicas de los datos compuestos en C.
El archivo BD.txt contiene un catálogo de automóviles con sus detalles, este archivo simula una Base de Datos de la cual se cargaría la información de cada automóvil para que desde el servidor se determine el manejo de esta información. Al inicio del archivo se especifica la longitud de la BD, es importante que si se agregan o quitan automóviles del catálogo, esto se vea relacionado con el valor de la longitud ya que este dato es utilizado por el servidor.
 
Desglosando los parámetros de compilación del CLIENTE:
    Comando: gcc requests_client.c requests_clnt.c requests_xdr.c -o e_client
    Donde:
    - "requests_client.c" => Corresponde a la plantilla generada por rpcgen y en el cual se encuentra la lógica desarrollada manualmente.
    - "requests_clnt.c" => Corresponde a un archivo generado por rpcgen, el cual contiene código para declarar las funciones en C a partir del archivo ".x".
    - "requests_xdr.c" => Corresponde a un archivo generado por rpcgen cuando se definen datos compuestos en IDL.
    - "e_client" => Corresponde al nombre del ejecutable.
 
Desglosando los parámetros de compilación del SERVIDOR:
    Comando: gcc requests_server.c requests_svc.c requests_xdr.c -lm -o e_server    
    Donde:
    - "requests_server.c" => Corresponde a la plantilla generada por rpcgen y en el cual se encuentra la lógica desarrollada manualmente.
    - "requests_svc.c" => Corresponde a un archivo generado por rpcgen, el cual contiene código para declarar las funciones en C a partir del archivo ".x".
    - "requests_xdr.c" => Corresponde a un archivo generado por rpcgen cuando se definen datos compuestos en IDL.
    - "-lm" => Es requerida para poder hacer uso de funciones como pow y sqrt.
    - "e_server" => Corresponde al nombre del ejecutable.
 
# Details
Se cuenta con la declaración de distintas estructuras a partir de la definición de datos compuestos en IDL, dichos datos compuestos son los siguientes:
    Utilizada para definir la posición respecto a un plano cartesiano con las coordenadas (x, y).
        <pre><code>struct Posicion {
            int x;
            int y;
        };
        </code></pre>
    Utilizada para definir la información de un auto específico cuando el cliente hace la petición de un viaje, de esta forma podemos saber la posición del automóvil, tipo, placa y status; este último, nos indica si el automóvil está libre u ocupado.
        struct InfoAuto {
            Posicion posicion_pasajero;
            string tipo<>;
            string placa<>;
            int status;
        };
    Utilizada cuando el viaje de un cliente ha terminado. De esta forma podemos saber en qué nueva posición se encuentra el automóvil, con la placa actualizaremos el status de dicho automóvil desde el servidor para dejarlo como disponible.
        struct Data {
            Posicion posicion_final;
            string placa<>;
        };
Se cuenta con la definición de dos funciones en IDL que tienen como parámetro un dato compuesto, en algunos campos se tienen datos compuestos que contienen otros datos compuestos.
    Utilizada para solicitar un viaje, en el parámetro Posición indicamos la posición en la cual se encuentra el cliente (esto de manera aleatoria). El tipo de función se especifica como "InfoAuto" para poder retornar la información del auto asignado o, en su caso, indicar que no existen automóviles disponibles.
        - InfoAuto SOLICITARVIAJE(Posicion)
    Utilizada para indicar que el viaje ha terminado. El parámetro "Data" contiene la posición a la cual llegó el cliente (simulada aleatoriamente) así como la placa del automóvil que fue utilizado para el viaje.
        - void TERMINARVIAJE(Data)

# others line commands:
rpcgen -a -C requests.x => genera scripts automaticamente para conectar cliente y servidor, definiciones de datos y uso de sockets.
