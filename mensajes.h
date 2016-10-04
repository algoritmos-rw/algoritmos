#ifndef MENSAJES_H
#define MENSAJES_H

// Mensajes del programa.
#define PACIENTE_ENCOLADO "Paciente %s encolado\n"
#define PACIENTE_ATENDIDO "Se atiende a %s\n"

#define NUM_PACIENTES_ESPERAN "%zu paciente(s) en espera para %s\n"
#define CERO_PACIENTES_ESPERAN "No hay pacientes en espera\n"

#define NUM_DOCTORES "%zu doctor(es) en el sistema\n"
#define INFORME_DOCTOR "%d: %s, especialidad %s, %d paciente(s) atendido(s)\n"

// Mensajes de error.
#define ENOENT_DOCTOR "ERROR: no existe el doctor '%s'\n"
#define ENOENT_PACIENTE "ERROR: no existe el paciente '%s'\n"
#define ENOENT_ESPECIALIDAD "ERROR: no existe la especialidad '%s'\n"

#define ENOENT_CMD "ERROR: no existe el comando '%s:%s'\n"
#define EINVAL_CMD "ERROR: formato de comando incorrecto\n"

#endif  // MENSAJES_H
