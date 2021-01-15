# RPC_C
Micro Uber using RPC and IDL with C language.

# Introduction
<p>
RPC o llamados a procedimientos remotos es utilizado para estabelcer comunicación entre distintos programas, estructurando un modelo cliente-servidor. RPC es un Middleware que ayuda con la transparencia al utilizar sockets para enviar peticiones mediante una red local, brinda mecanismos para garantizar la integridad de los datos al enviar y recibir información; de igual forma genera stubs, el Marshaling, Unmarshalling, la gestión de datos y funciones declarados con IDL. Brinda la oportunidad de que el desarrollador se centre en la lógica detrás de los llamados a las funciones que harán posible la comunicación entre clientes y servidor.
</p><br />
Aplicaciones usando RPC:<br /> 
<p>
 1) Amazon Lumberyard. Amazon Lumberyard es un motor de videojuegos 3D gratuito y multiplataforma que le permite crear juegos de alta calidad los juegos, conecte los juegos al computador y al almacenamiento del AWS.  RPCs permite a los juegos enviar eventos o solicitudes a nodos remotos a través de réplicas. Se pueden utilizarse para enviar mensajes a un nodo específico o para enrutar llamadas de función al nodo autorizado. Por ejemplo, puede utilizar RPCs para implementar funciones que cambian la posición de un objeto. [3] <br />
 2) Google Protocol RPC Library Overview. La biblioteca RPC del protocolo de Google es un marco para implementar servicios de llamada a procedimiento remoto (RPC) basados en HTTP. Un servicio RPC es una colección de tipos de mensajes y métodos remotos que proporcionan una forma estructurada para que las aplicaciones externas interactúen con las aplicaciones web. Debido a que puede definir mensajes y servicios en el lenguaje de programación Python, es fácil desarrollar servicios de protocolo RPC, probar esos servicios y escalarlos en App Engine. [4]<br />
 3) Action Message Format (AMF) permite que las aplicaciones de Adobe Flex se comuniquen con back-end u otras aplicaciones compatibles con AMF para enviar información. [1] <br /> 
 4) Remote Function Call (RFC) es la interfaz estándar de SAP para la comunicación entre sistemas SAP. RFC llama a una función para que se ejecute en un sistema remoto que puede estar escrito en lenguajes como PHP, ASP, Java, or C, C++. [2]
</p>

# Description
En este proyecto se hace uso de RPC combinado con el lenguaje C e IDL para crear una simulación de la aplicación Uber a menor escala. Se cuenta con un servidor y la posibilidad de la existencia de distintos clientes que ejecuten peticiones para solicitar un viaje.
 
# Project requirements
  1) El compilador GCC
Contar con rpcbind o ejecutar los siguientes comandos en caso de no contar con rpcbind:
  1) sudo apt update
  2) sudo apt install rpcbind
  
# Steps to clone the project
(with HTTPS)
git clone https://github.com/FlavioRico/RPC_C.git

(with SSH)
git clone git@github.com:FlavioRico/RPC_C.git
 
# Compile and excecute project
1) Verificar que el servicio rpcbind se encuentre activo con el siguiente comando:
    <code><pre>sudo service rpcbind status</code></pre>
2) En caso de que el servicio no se encuentre activo se requiere ejecutar el siguiente comando:
    <code><pre>sudo service rpcbind start</code></pre>
3) Para compilar el cliente, abrir una términal y ejecutar el siguiente comando:
    <code><pre>gcc requests_client.c requests_clnt.c requests_xdr.c -o e_client</code></pre>
4) Para compilar el servidor, abrir una términal y ejecutar el siguiente comando:
    <code><pre>gcc requests_server.c requests_svc.c requests_xdr.c -lm -o e_server</code></pre>
5) Primero ejecutar el servidor con el comando:
    <code><pre>./e_server</code></pre>
6) Después ejecutar el cliente con el comando (se pueden abrir más términales y ejecutar distintos clientes):
    <code><pre>./e_client localhost</code></pre>
 
# Important notes
El script "requests.x" contiene la declaración de las funciones que se utilizarán para comunicar el cliente y el servidor, así como los datos compuestos que serán enviados por parámetro en las funciones.<br />
Los scripts "requests.h, requests.xdr.c requests_clnt.c requests_svc.c" son generados automáticamente con RPC utilizando el script "requests.x" para definir las estructuras y funciones indicadas en dicho script; de igual forma, la bandera "-a" nos ayuda a generar una plantilla automática en la cual solamente nos dedicaremos a escribir la lógica del proyecto. (rpcgen -a -C requests.x).
Cuando compilamos tanto cliente como servidor, es importante incluir el script generado "requests_xdr.c" debido a que se utilizan datos compuestos en IDL, RPC requiere este archivo con definiciones específicas de los datos compuestos en C.
El archivo BD.txt contiene un catálogo de automóviles con sus detalles, este archivo simula una Base de Datos de la cual se cargaría la información de cada automóvil para que desde el servidor se determine el manejo de esta información. Al inicio del archivo se especifica la longitud de la BD, es importante que si se agregan o quitan automóviles del catálogo, esto se vea relacionado con el valor de la longitud ya que este dato es utilizado por el servidor.<br />
 
Desglosando los parámetros de compilación del CLIENTE:<br />
    Comando: <pre><code>gcc requests_client.c requests_clnt.c requests_xdr.c -o e_client</pre></code>
    Donde:<br />
    - "requests_client.c" => Corresponde a la plantilla generada por rpcgen y en el cual se encuentra la lógica desarrollada manualmente.<br />
    - "requests_clnt.c" => Corresponde a un archivo generado por rpcgen, el cual contiene código para declarar las funciones en C a partir del archivo ".x".<br />
    - "requests_xdr.c" => Corresponde a un archivo generado por rpcgen cuando se definen datos compuestos en IDL.<br />
    - "e_client" => Corresponde al nombre del ejecutable.<br /><br />
 
Desglosando los parámetros de compilación del SERVIDOR:<br />
    Comando: <pre><code>gcc requests_server.c requests_svc.c requests_xdr.c -lm -o e_server</pre></code> 
    Donde:<br />
    - "requests_server.c" => Corresponde a la plantilla generada por rpcgen y en el cual se encuentra la lógica desarrollada manualmente.<br />
    - "requests_svc.c" => Corresponde a un archivo generado por rpcgen, el cual contiene código para declarar las funciones en C a partir del archivo ".x".<br />
    - "requests_xdr.c" => Corresponde a un archivo generado por rpcgen cuando se definen datos compuestos en IDL.<br />
    - "-lm" => Es requerida para poder hacer uso de funciones como pow y sqrt.<br />
    - "e_server" => Corresponde al nombre del ejecutable.<br />
 
# Details
Se cuenta con la declaración de distintas estructuras a partir de la definición de datos compuestos en IDL, dichos datos compuestos son los siguientes:
    Utilizada para definir la posición respecto a un plano cartesiano con las coordenadas (x, y).
        <pre><code>struct Posicion {
            int x;
            int y;
        };
        </code></pre>
    Utilizada para definir la información de un auto específico cuando el cliente hace la petición de un viaje, de esta forma podemos saber la posición del automóvil, tipo, placa y status; este último, nos indica si el automóvil está libre u ocupado.
        <pre><code>struct InfoAuto {
            Posicion posicion_pasajero;
            string tipo<>;
            string placa<>;
            int status;
        };
        </code></pre>
    Utilizada cuando el viaje de un cliente ha terminado. De esta forma podemos saber en qué nueva posición se encuentra el automóvil, con la placa actualizaremos el status de dicho automóvil desde el servidor para dejarlo como disponible.
        <code><pre>struct Data {
            Posicion posicion_final;
            string placa<>;
        };
        </code></pre>
Se cuenta con la definición de dos funciones en IDL que tienen como parámetro un dato compuesto, en algunos campos se tienen datos compuestos que contienen otros datos compuestos.<br />
    Utilizada para solicitar un viaje, en el parámetro Posición indicamos la posición en la cual se encuentra el cliente (esto de manera aleatoria). El tipo de función se especifica como "InfoAuto" para poder retornar la información del auto asignado o, en su caso, indicar que no existen automóviles disponibles.<br />
        <code><pre>InfoAuto SOLICITARVIAJE(Posicion)</code></pre>
    Utilizada para indicar que el viaje ha terminado. El parámetro "Data" contiene la posición a la cual llegó el cliente (simulada aleatoriamente) así como la placa del automóvil que fue utilizado para el viaje.<br />
        <code><pre>void TERMINARVIAJE(Data)</code></pre>

# Others line commands:
<code><pre>
rpcgen -a -C requests.x => genera scripts automaticamente para conectar cliente y servidor, definiciones de datos y uso de sockets.
</code></pre>
## References
[1] Wikipedia contributors. (2021, January 3). Action Message Format. In Wikipedia, The Free Encyclopedia. Retrieved 23:32, January 15, 2021, from https://en.wikipedia.org/w/index.php?title=Action_Message_Format&oldid=997960797<br />
[2] Wikipedia contributors. (2018, December 6). Remote Function Call. In Wikipedia, The Free Encyclopedia. Retrieved 23:33, January 15, 2021, from https://en.wikipedia.org/w/index.php?title=Remote_Function_Call&oldid=872318548<br />
[3] Amazon. (s. f.). Llamadas de procedimiento remoto (RPC) - Guía del usuario de Lumberyard. aws. Recuperado 15 de enero de 2021, de https://docs.aws.amazon.com/es_es/lumberyard/latest/userguide/network-replicas-remote-procedure-calls.html<br />
[4] Google. (2020, 16 noviembre). Google Protocol RPC Library Overview. Google Cloud. https://cloud.google.com/appengine/docs/standard/python/tools/protorpc
