#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

#define MAX_FIELD_LEN 50


typedef enum
{
    FALSE,
    TRUE
} bool_t;

// car type
typedef enum
{
    new = 1,
    used
} condition_t;


// Not new (alreary driven)
typedef struct
{
    int year; // year model
    int mileage; // mileage in Km
    int repairs; // number of technical problems
    int owners; // num of owners
} driven_t;


// Vehicle condition {new, used}
typedef union 
{
    int guarantee;  // new
    driven_t used;  // already owned
} variable_t;


// Car info type
typedef struct
{
    char brand[MAX_FIELD_LEN]; // car brand
    char country[MAX_FIELD_LEN]; // country of origin
    int price; // car price
    char color[MAX_FIELD_LEN]; // car color
    condition_t car_type; // car type
    variable_t add_info; // more about car {depends to car type}
} car_t;


// Keys (car price)
typedef struct
{
    int car_table_index; // index of car in main table
    int car_price; // car price
} car_key_t;



// All in one data
typedef struct
{
    car_t *main_table; // 
    car_key_t *key_table; //
    int size; // number of records in table
} data_t;

#endif // _DATA_STRUCT_H_