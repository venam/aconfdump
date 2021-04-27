#include <alsa/asoundlib.h>

#define DEFAULT_OUTPUT "aconf.conf"

int main(int argc, char *argv[])
{
	char *output_location;
	if (argc > 1) {
		output_location = argv[1];
	} else {
		output_location = DEFAULT_OUTPUT;
	}
	snd_config_update();
	snd_output_t *output;
	snd_output_stdio_open(&output, output_location, "w");
	if (snd_config != NULL) {
		snd_config_save(snd_config, output);
		printf("saved config to %s\n", output_location);
	}
	return 0;
}
