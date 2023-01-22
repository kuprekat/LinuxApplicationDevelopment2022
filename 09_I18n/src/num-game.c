#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main() {
	setlocale(LC_ALL, "");
	bindtextdomain ("ru", LOCALE_PATH);
	textdomain ("ru");
	
	int min = 0;
	int max = 100;
	char input[128];
	printf(_("Guess a number from 1 to 100:\n"));


	while(max - min > 1) {
	        printf(_("Is your number higher than %d?\n"), (min + max) / 2);
		scanf("%s", input);

		if(!strcmp(input, _("yes"))) {
			min = (min + max) / 2;
		}
		else if(!strcmp(input, _("no"))) {
			max = (min + max) / 2;
		}
		else {
		 printf(_("Please, enter 'yes' or 'no'\n"));
		}
	
	}
	printf(_("Your number is %d\n"), max);

	return 0;
}

