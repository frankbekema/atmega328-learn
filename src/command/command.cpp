#include "command.h"


void command_add(command_object_t* c_object, command_t command) {
  command_t* new_commands;
  
  if(c_object->list.commands == NULL) {
    if(Serial)
      Serial.println("ERROR: No commands object has been initialized");
    return;
  }
  new_commands = (command_t*)malloc(sizeof(command_t) * (c_object->list.size + 1));
  memcpy(new_commands, c_object->list.commands, c_object->list.size * sizeof(command_t));
  new_commands[c_object->list.size] = command;
  free(c_object->list.commands);
  c_object->list.size = c_object->list.size + 1;
  c_object->list.commands = new_commands;

}


void command_add(command_object_t* c_object, const char* name, void (*function)()) {
    command_t* new_commands;
    command_t command;
  
    if(c_object->list.commands == NULL) {
      if(Serial)
        Serial.println("ERROR: No commands object has been initialized");
      return;
    }
    command.name = name;
    command.function = function;

    new_commands = (command_t*)malloc(sizeof(command_t) * (c_object->list.size + 1));
    memcpy(new_commands, c_object->list.commands, c_object->list.size * sizeof(command_t));
    new_commands[c_object->list.size] = command;
    free(c_object->list.commands);
    c_object->list.size = c_object->list.size + 1;
    c_object->list.commands = new_commands;
}


bool command_remove(command_object_t* c_object, const char* command_name) {
  int i;
  int b;
  command_t empty_command;

  for(i = 0; i < c_object->list.size; i++) {
    if(command_string_compare(c_object->list.commands[i].name, command_name)) {
      for(b = i; b < c_object->list.size - 1; b++) {
        c_object->list.commands[b] = c_object->list.commands[b+1];
      }
      c_object->list.commands[c_object->list.size] = empty_command;
      c_object->list.size--;
      return true;
    }
  }
  return false;
}


void command_data_append(command_object_t* c_object, const char* data) {
  char* buffer;
  int buffer_size;
  
  if(c_object->buffer == NULL) {
    if(Serial)
      Serial.println("ERROR: Buffer is null");
    return;
  }
  if(strlen(data) > c_object->buffer_size - c_object->buffer_data_size) {
    buffer_size = c_object->buffer_size + strlen(data) * 2;
    buffer = malloc(sizeof(char) * buffer_size);
    c_object->buffer_size = buffer_size;
    
    strcpy(buffer, c_object->buffer);
    free(c_object->buffer);
    c_object->buffer = buffer;
  }
  strcat(c_object->buffer, data);
  c_object->buffer_data_size = strlen(data) + c_object->buffer_data_size;
}


void command_handler(command_object_t* c_object) {
  char character;
  int i;
  char endMarker = '\n';

  if(!Serial) {
    return false;
  }

  while(Serial.available() > 0) {
    if(c_object->new_data) {
      c_object->buffer = (char*)malloc(sizeof(char) * 64);
      c_object->buffer[0] = '\0';
      c_object->buffer_size = 64;
      c_object->buffer_data_size = 0;
      c_object->new_data = false;
    }
    
    character = Serial.read();

    if(character == endMarker) {
      for(i = 0; i < c_object->list.size; i++) {
        if(command_string_compare(c_object->list.commands[i].name, c_object->buffer)) {
          c_object->list.commands[i].function();
          break;
        }
      }
      c_object->new_data = true;
      free(c_object->buffer);
      return;
    }
    command_data_append(c_object, &character);
  }
}


command_object_t command_get_object() {
  command_object_t c_object;
  
  c_object.buffer = NULL;
  c_object.buffer_size = 0;
  c_object.buffer_data_size = 0;
  c_object.new_data = true;
  
  c_object.list.commands = (command_t*)malloc(0);
  c_object.list.size = 0;
  return c_object;
}


void command_remove_object(command_object_t* c_object) {
  free(c_object->list.commands);
  c_object = NULL;
}


bool command_string_compare(const char* string1, const char* string2) {
  return strncmp(string1, string2, strlen(string1)) == 0 && strlen(string1) == strlen(string2);
}