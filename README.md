[Read this in English](./README_EN.md)
# ShadowFog

ShadowFog es una herramienta de anonimato desarrollada en C++ que utiliza Tor y Proxychains para facilitar una navegación web segura y anónima. Esta utilidad automatiza todo el proceso de instalación, configuración y ejecución de Tor y Proxychains en tu sistema. Permite a los usuarios ejecutar navegadores y otras aplicaciones a través de Tor y Proxychains de manera fluida, asegurando que tus actividades en línea permanezcan privadas y protegidas.

## Contexto

En la era digital actual, la privacidad y el anonimato en internet son más que simples lujos; son derechos esenciales que protegen la libertad individual. A medida que nuestras vidas se entrelazan cada vez más con internet, la capacidad de salvaguardar la información personal contra el acceso y la vigilancia no autorizados se ha vuelto crucial. Ya seas un periodista, un defensor de la privacidad o simplemente un usuario precavido, mantener el anonimato puede protegerte de anuncios dirigidos, prevenir el robo de identidad e incluso proteger tu libertad de expresión bajo regímenes opresivos.

ShadowFog está diseñado para empoderar a los usuarios proporcionando herramientas robustas para la navegación web anónima. Aprovechando el poder de Tor y Proxychains, ShadowFog automatiza los procesos complejos de instalación, configuración y operación, facilitando más que nunca la navegación segura y anónima por la web. Esta herramienta no se trata solo de acceder a la web; se trata de reclamar tu derecho a la privacidad en una era donde las huellas digitales son constantemente monitoreadas.

## Disclaimer

Este software se proporciona "tal cual", sin garantía de ningún tipo, expresa o implícita. En ningún caso el autor o los colaboradores del proyecto serán responsables por cualquier daño directo, indirecto, incidental, especial, ejemplar o consecuente (incluyendo, pero no limitado a, la adquisición de bienes o servicios sustitutos; pérdida de uso, datos o beneficios; o interrupción de la actividad empresarial) sin importar la causa y bajo cualquier teoría de responsabilidad, ya sea por contrato, responsabilidad estricta o agravio (incluyendo negligencia u otra) que surja de cualquier forma del uso de este software, incluso si se advierte de la posibilidad de dicho daño.

El uso de ShadowFog para actividades que infrinjan la ley esta estrictamente prohibido. El desarrollador de ShadowFog no aprueba el uso ilegal de herramientas de anonimato y no se hace responsable de cualquier uso indebido del software. El usuario final es el único responsable de asegurarse que todas sus acciones con ShadowFog cumplan con las leyes aplicables en su jurisdicción.

## Instalación y uso

**1. Clonar el repositorio / Descargar codigo fuente**

Primero, debes clonar el repositorio de ShadowFog a tu máquina local utilizando Github o puedes descargar el codigo fuente.
- git clone https://github.com/Julen-H/ShadowFog

**2. Ejecutar el script de instalacion / Compilar el programa**

ShadowFog incluye un script de bash que prepara todas las dependencias necesarias y compila el programa. Es necesario tener permisos de administrador (sudo) para ejecutar este script. El script instalara un compilador para c++ y figlet. Si no usas el script puede instalar los paquetes de esta manera:
- sudo apt-get install g++ -y
- sudo apt-get install figlet -y

Una vez instalados, ejecuta el script en modo administrador (sudo) o si deseas ejecuta directamente el script y se descargaran automaticamente. Además una vez que se instalan los paquetes el script compilara y ejecutara el programa automaticamente. 

**ATENCIÓN**
Cuando el script compila y ejecuta el programa, ejecutara ShadowFog como administrador (sudo) ya que deberas de realizar la configuración inicial de Proxychains. La configuración se hace editando parametros en el archivo de configuración (el .conf file que se encuentra en /etc/proxychains4.conf), para ello necesitaras permisos de administrador. Es por eso que se ejecuta como administrador (sudo). Una vez que se haya llevado a cabo la configuración cierra el programa y ejecutalo con tu usuario normal. Haz lo mismo cuando desees usar el programa en tu dia a dia.

Ejecuta el script en modo administrador (sudo)
- sudo ./shadowfog.sh

**3. Configuración inicial**

Despues de que el script haya compilado y ejecutado el programa y antes de empezar a navegar de forma seegura y anonima, es crucial realizar una configuración inicial. Esta configuración incluye la instalación y configuración de Tor y Proxychains, lo cual se realiza a través del comando -configure dentro de ShadowFog. Una vez se instalan Tor y Proxychains hay que realizar la configuración de Proxychains. Para ello podemos usar el comando -set y especificar el modo de las cadenas. 

Para instalar Tor y Proxychains

|Modo|Comando|
| -- | -- |
|Dinamico|-set dynamic|
|Random|-set random 3|
* El numero despues de random es la longitud de la cadena, en este caso Proxychains rebotara en 3 proxies. Puedes elegir la longitud como veas adecuado, por defecto suele configurarse en 2



