CC=gcc
CFLAGS=-I
DEPS= larrymake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

larrymake : active_module.o consumption_check.o database_module.o debug.o \
        global.o info_energy_saving.o language.o update_settings.o user_history.o \
        warning_energy_saving.o
	
	$ (CC) -o larrymake active_module.o consumption_check.o database_module.o debug.o \
         global.o info_energy_saving.o language.o update_settings.o user_history.o \
         warning_energy_saving.o