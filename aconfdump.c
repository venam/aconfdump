#include <unistd.h>
#include <getopt.h>
#include <alsa/asoundlib.h>

#define DEFAULT_OUTPUT "aconf.conf"

int main(int argc, char *argv[])
{
	char *output_location = NULL, *search_query = NULL;
	int err, opt;
	while ((opt = getopt(argc, argv, "o:s:")) != -1) {
		switch (opt)
		{
		case 'o':
			output_location = optarg;
		break;
		case 's':
			search_query = optarg;
		break;
		default:
			fprintf(stderr, "Usage: %s [-o output location] [-s search query]\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (output_location == NULL) {
		output_location = DEFAULT_OUTPUT;
	}
	snd_config_update();
	snd_output_t *output;
	snd_output_stdio_open(&output, output_location, "w");
	if (snd_config != NULL) {
		snd_config_t *cfg2;
		err = snd_config_search_definition(snd_config, "cards", "_dummy_", &cfg2);
		if (err >= 0)
			snd_config_delete(cfg2);

		if (search_query == NULL) {
			cfg2 = snd_config;
		} else {
			err = snd_config_search(snd_config, search_query, &cfg2);
			if (err < 0) {
				fprintf(stderr, "Expression '%s' not found in tree\n", search_query);
				exit(EXIT_FAILURE);
			}
		}
		snd_config_save(cfg2, output);
		snd_output_flush(output);
		printf("saved config to %s\n", output_location);
	}
	snd_output_close(output);
	return 0;
}
