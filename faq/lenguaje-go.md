# FAQ - Lenguaje Go
{:.no_toc}

* Contenido
{:toc}

## ¿Qué son los tipos de datos enumerativos, y cómo usarlos en Go?

Supongamos que tenemos que trabajar con los días de la semana. Como buenos
aprendices de Algoritmos y Programación I (o Pensamiento Computacional), sabemos
que debemos usar constantes. Entonces podríamos hacer: 
```golang
const (
	LUNES = 1
	MARTES = 2
	MIERCOLES = 3
	JUEVES = 4
	VIERNES = 5
	SABADO = 6
	DOMINGO = 7
)

func main() {
	...
	dia := LUNES
	fmt.Println(dia)
}
```
El problema con ello, es lo siguiente: 
1. La variable día es de tipo entero. Es decir, nada me limita más adelante hacer `dia = 14`.
1. No puedo agregarle funcionalidades a los días de manera sencilla. 

Como justamente ahora no estamos trabajando con un valor constante _suelto_, o de un
uso particular, sino que varias constantes tienen una relación, lo que podemos hacer
es crear un tipo de dato enumerativo: 

```golang
type DiaSemana int // definicion de mi tipo

const (
	LUNES DiaSemana = iota
	MARTES
	MIERCOLES
	JUEVES
	VIERNES
	SABADO
	DOMINGO
)

func main() {
	...
	dia := LUNES
	fmt.Println(dia)
}
```

Con esto, resolvemos directamente lo primero. Si hiciéramos `dia = 14`, el compilador diría
que no es una operación válida porque 14 es de tipo `int` mientras que `dia` es de tipo `DiaSemana` (hay formas de "hackear" esto, pero el punto es que quien lo quiera hacer ya debe ser muy conciente que está obrando mal). Y lo segundo puede resolverse agregándole métodos al tipo de dato, como puede hacerse a cualquier tipo, por ejemplo: 
```golang
func (dia DiaSemana) ToString() string {
	switch int(dia) {
	case 0:
		return "Lunes"
	case 1: 
		return "Martes"
	case 2:
		return "Miercoles"
	case 3:
		return "Jueves"
	case 4:
		return "Viernes"
	case 5:
		return "Sabado"
	case 6:
		return "Domingo"
	default:
		panic("¿Dia Osvaldo?")
	}
}
```
De esta forma, podríamos cambiar ese `main` por:
```golang
func main() {
	...
	dia := LUNES
	fmt.Println(dia.ToString())
}
```

Esto permite poder trabajar con una mejor calidad de código, que sea autoexpresivo. 

## ¿Cómo trabajar con un archivo en Go?

### Lectura

Hay varias formas de hacer esto, pero la forma que recomendamos en el curso es la que damos en clase. Aquí damos un ejemplo completo:

```golang
func leerArchivo(ruta string) {
	archivo, err := os.Open(ruta)
	if err != nil {
		fmt.Printf("Archivo %s no encontrado", ruta)
		return
	}
	defer archivo.Close()

	s := bufio.NewScanner(archivo)
	for s.Scan() {
		fmt.Printf("Leí: %s\n", s.Text())
	}
	err = s.Err()
	if err != nil {
		fmt.Println(err)
	}
}
```

### Escritura

Para escribir en un archivo, podemos usar `fmt.Fprintf`, abriendo el archivo para escritura:
```golang
func escribirArchivo(ruta string, texto string) {
	file, err := os.Create(ruta)
	if err != nil {
		fmt.Printf("No se pudo crear el archivo %s", ruta)
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "El texto es: %s\n", texto)
}
```

Dado que esto no permite tener manejo del flujo de archivos, también se puede hacer uso de un 
`datawriter`:

```golang
func escribirArchivo(ruta string, texto string) {
	file, err := os.Create(ruta)
	if err != nil {
		fmt.Printf("No se pudo crear el archivo %s", ruta)
		return
	}
	defer file.Close()

	datawriter := bufio.NewWriter(file)

	for _, dato := range []string{"hola", "como", "estas"} {
		_, err = datawriter.WriteString(dato + "\n")
		if err != nil {
			fmt.Printf("No se pudo guardar la línea %s, error: %v", dato, err)
		}
		datawriter.Flush()
	}
}
```

## ¿Cómo se usan stdin, stdout y stderr?

Estos 3 archivos se usan de la misma forma que cualquier otro archivo, sólo que no es necesario abrirlos (ya están abiertos), ni cerrarlos (se los puede cerrar, pero no es una buena práctica). Por supuesto, stdin es un archivo de lectura, y los otros dos son de escritura. La diferencia entre esos dos es que stderr, al ser pensado para manejo de errores, no hace _buffering_ (para evitar que un cierre abrupto del programa nos haga perder información). 

Por ejemplo, para la lectura de stdin, podríamos hacer: 
```golang

func leerEntradaEstandar() {
	s := bufio.NewScanner(os.Stdin)
	for s.Scan() {
		fmt.Printf("Leí: %s\n", s.Text())
	}
}
```

Para imprimir por salida estándar o salida de error estándar, podemos hacer: 
```golang
fmt.Fprintf(os.Stdout, "Mi salida")
fmt.Fprintf(os.Stderr, "Mi error")
```

En particular, hacer `fmt.Fprintf(os.Stdout, ...)` es lo mismo que hacer `fmt.Printf(...)` (este imprime a stdout).

## ¿Cómo se usan los argumentos de un programa?

Para esto, sólo necesitamos usar `os.Args`. Recordar que siempre la posición 0 de dicho arreglo será el nombre del ejecutable. Por ejemplo: 

```golang
func main() {
	if len(os.Args) != 3 {
		fmt.Println("La cantidad de parametros es erronea")
		return
	}
	fmt.Printf("Primer argumento %s\n", os.Args[0])
	fmt.Printf("Segundo argumento %s\n", os.Args[1])
	fmt.Printf("Tercer argumento %s\n", os.Args[2])
}
```

Supongamos que nuestro ejecutable se llama `prueba`, y lo invoco de la siguiente manera: 
```
./prueba ejemplo cosa
```
Entonces la salida del programa será: 
```
Primer argumento: ./prueba
Segundo argumento: ejemplo
Tercer argumento: cosa
```

Si quisiéramos que un argumento fuera de más de una palabra (por la razón que fuere), podemos encerrarlo entre comillas: 

```
./prueba ejemplo "cosa maravillosa"
```

Y allí la salida sería: 
```
Primer argumento: ./prueba
Segundo argumento: ejemplo
Tercer argumento: cosa maravillosa
```
Notar que el tercer argumento no tiene comillas "agregadas". 