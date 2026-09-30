# Pipex

Implementacion en C del proyecto pipex de 42 School. Recrea el comportamiento de las pipes de shell (`|`) ejecutando comandos con redirecciones de entrada/salida usando `fork`, `pipe`, `dup2` y `execve`.

## Como funciona

El programa toma un archivo de entrada, dos comandos y un archivo de salida. Ejecuta el primer comando con el archivo de entrada como stdin, conecta su salida al segundo comando, y escribe el resultado final en el archivo de salida.

```
./pipex input.txt "grep foo" "wc -l" output.txt
```

Equivalente a: `< input.txt grep foo | wc -l > output.txt`

## Compilacion

```bash
make        # Compilar parte obligatoria
make bonus  # Compilar con bonus (multiples pipes + here_doc)
```

Requiere `cc` (compilador de C) y las librerias compartidas (libft, gnl, printf) del repositorio padre.

## Uso

### Obligatorio

```bash
./pipex input.txt "cmd1" "cmd2" output.txt
```

### Bonus (multiples comandos + here_doc)

```bash
./pipex input.txt "cmd1" "cmd2" "cmd3" "cmd4" output.txt
./pipex here_doc LIMITER "cmd1" "cmd2" output.txt
```

La funcionalidad `here_doc` lee desde stdin hasta que se encuentra la cadena limitadora, y usa eso como entrada.

## Estructura del proyecto

```
pipex/
├── src/
│   ├── main.c              # Punto de entrada obligatorio
│   ├── main_bonus.c        # Punto de entrada bonus
│   ├── find_executable.c   # Resolucion de PATH
│   ├── child_process.c     # Logica de fork y exec
│   ├── utils.c             # Ops de archivos, here_doc, manejo de errores
│   ├── pipe_utils.c        # Creacion y configuracion de pipes (bonus)
│   ├── process.c           # Gestion de multiples procesos (bonus)
│   └── free_array2.c       # Funcion de utilidad
├── inc/
│   └── pipex.h             # Header unificado
└── Makefile
```

## Limpieza

```bash
make clean    # Elimina archivos objeto
make fclean   # Elimina binario y archivos objeto
make re       # Recompila
```
