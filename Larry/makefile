larry : active_module.o consumption_check.o database_module.o debug.o \
	global.o info_energy_saving.o language.o update_settings.o user_history.o \
	warning_energy_saving.o passive_module.o saving_advice.o machine_activation.o
	cc -o larry active_module.o consumption_check.o database_module.o debug.o \
 global.o info_energy_saving.o language.o update_settings.o user_history.o \
 warning_energy_saving.o passive_module.o saving_advice.o machine_activation.o

active_module.o : active_module.c
	cc -c active_module.c
consumption_check.o : consumption_check.c consumption_check.h 
	cc -c consumption_check.c
database_module.o : database_module.c database_module.h
	cc -c database_module.c
debug.o : debug.c debug.h
	cc -c debug.c
global.o : global.c global.h
	cc -c global.c
info_energy_saving.o : info_energy_saving.c info_energy_saving.h
	cc -c info_energy_saving.c
language.o : language.c language.h
	cc -c language.c
update_settings.o : update_settings.c update_settings.h
	cc -c update_settings.c
user_history.o : user_history.c user_history.h
	cc -c user_history.c
warning_energy_saving.o : warning_energy_saving.c warning_energy_saving.h
	cc -c warning_energy_saving.c
passive_module.o : passive_module.c passive_module.h
	cc -c passive_module.c
saving_advice.o : saving_advice.c saving_advice.h
	cc -c saving_advice.c
machine_activation.o : machine_activation.c machine_activation.h
	cc -c machine_activation.c
clean :
	rm larry active_module.o consumption_check.o database_module.o debug.o \
	global.o info_energy_saving.o language.o update_settings.o user_history.o \
 arning_energy_saving.o passive_module.o saving_advice.o machine_activation.o