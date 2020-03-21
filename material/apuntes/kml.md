# Archivos KML

Los archivos KML son archivos de texto plano utilizados por aplicaciones como Google Earth o Google Maps para mostrar información geográfica. Estos archivos deben cumplir un estándar con el que se pueden representar puntos, líneas y polígonos, entre otras cosas.

La referencia completa de esta sintaxis está disponible en [Internet](https://developers.google.com/kml/documentation/?hl=en). Sin embargo, aquí se definen un subconjunto mínimo de instrucciones para generar archivos KML con la información necesaria para visualizar las rutas.

Para visualizar estos archivos generados se puede usar [Google Maps](https://support.google.com/mymaps/answer/3024836?hl=en) o alguna aplicación externa que no requiere haber iniciado sesión con una cuenta de Google (por ejemplo [display-kml.appspot.com](http://display-kml.appspot.com)).

Se incluye junto a este apunte [un archivo KML de ejemplo](https://drive.google.com/file/d/1Q688kilDIoubp4lQH7Se9YWigbYcyxW3/view?usp=sharing).

## Encabezado XML

La primera línea de cada archivo KML debe ser el encabezado del estándar XML:

```xml
    <?xml version="1.0" encoding="UTF-8"?>
```

## Declaración de KML (inicio)

Las siguientes líneas del archivo indica que se trata de un archivo KML y se anuncia su inicio:
```xml
    <kml xmlns="http://www.opengis.net/kml/2.2">
        <Document>
```
## Información del archivo KML

A continuación se puede agregar el nombre del archivo y una descripción.
```xml
    <name>KML de ejemplo</name>
    <description>Un ejemplo introductorio.</description>
```
## Contenido geográfico

El lenguaje incluye muchos componentes para visualizar en mapas, especificando su estilo y muchos atributos. Por simplificación, explicaremos únicamente dos, con los cuales ya se puede tener una versión simplificada. En caso de querer aprender más sobre archivos KML, los referimos a la documentación antes mencionada.

Se pueden incluir muchos de estos componentes en un mismo archivo sin necesidad de ordenarlos ni especificar su cantidad previamente.


### Lugares

Se usan para indicar un lugar de interés en las coordenadas especificadas:
```xml
    <Placemark>
        <name>Facultad de Ingeniería, UBA</name>
        <Point>
            <coordinates>-58.3679593, -34.6176355</coordinates>
        </Point>
    </Placemark>
```
Este ejemplo ubica un punto con el nombre “Facultad de Ingeniería, UBA” en la coordenada indicada (especificando primero la longitud y luego la latitud, separadas por comas).


### Líneas

Se usan para indicar un recorrido entre las coordenadas especificadas:
```xml
    <Placemark>
        <LineString>
            <coordinates>-58.36795, -34.61763 -58.39644, -34.58850</coordinates>
        </LineString>
    </Placemark>
```
Este ejemplo dibuja una ruta entre los dos puntos indicados.


## Declaración de KML (fin)

Se indica el fin del archivo.
```xml
        </Document>
    </kml>
```

Se puede ver [un ejemplo de visualización de este archivo de ejemplo aquí](https://www.doogal.co.uk/KmlViewer.php?url=https://www.doogal.co.uk/UploadedKml/01f198d7-2ddc-4b07-8a73-eb84f3bb2c97.kml).

