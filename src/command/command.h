#ifndef  COMMAND_H
#define  COMMAND_H

#include <Arduino.h>
#include <stdbool.h> 

typedef struct command_t {
  const char* name;
  void (*function)();
} command_t;

typedef struct command_list_t {
  command_t* commands;
  int size;
} command_list_t;

typedef struct command_object_t {
  command_list_t list;
  char* buffer;
  int buffer_size;
  int buffer_data_size;
  bool new_data;
} command_object_t;

void command_add(command_object_t* c_object, command_t com);
void command_add(command_object_t* c_object, const char* name, void (*function)());
bool command_remove(command_object_t* c_object, const char* command_name);
void command_data_append(command_object_t* c_object, const char* data);
void command_handler(command_object_t* c_object);
command_object_t command_get_object();
void command_remove_object(command_object_t* c_object);
bool command_string_compare(const char* string1, const char* string2);

#endif /* COMMAND_H */
    
