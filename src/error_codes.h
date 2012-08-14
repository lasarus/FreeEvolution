#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum error_code
  {
    ERROR_NONE = 0,
    ERROR_UNKNOWN,
    ERROR_IMAGE_NOT_POWER_OF_TWO,
    ERROR_IMAGE_INVALID_PIXELS_PER_BYTES
  } error_code_t;

#endif
