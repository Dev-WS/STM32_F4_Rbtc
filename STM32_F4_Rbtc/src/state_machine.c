


typedef enum {STATE_OFF, STATE_RUN, STATE_ERROR, NUM_STATES} state_t;
typedef struct instance_data instance_data_t;
typedef state_t state_func_t(instance_data_t *data);


state_t do_off_to_run(instance_data_t *data);
state_t do_run_to_err(instance_data_t *data);
state_t do_err_to_off(instance_data_t *data);



