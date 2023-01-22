#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

void help() {
	printf(_("Usage: ./num-game [OPTIONS]\n"));
	printf(_("Simple number game: program will guess the number from 1 to 100 that you guessed\n\n"));
	printf(_("Options:\n"));
	printf(_("\t-r\t\tprint roman numbers instead arabic\n\n"));
	printf(_("\t-h, --help\tprint help message\n\n"));
	printf(_("Constants:\n"));
        printf(_("\tchar *romans\tarray containing Roman numerals from 1 to 100\n\n"));
	printf(_("Functions:\n"));
        printf(_("\tchar *to_roman(int num)\t\t"));
	printf(_("takes an integer from 1 to 100, returns a string with equal roman number or 'Err' on error\n\n"));
        printf(_("\tint to_arabic(char *roman)\t"));
	printf(_("takes a roman number from I to C, returns the equal value as an integer or -1 on error\n\n"));
}

char romans[100][12] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};

char *to_roman(int n) {
	if (n > 0 && n <= 100)
		return romans[n-1];
	else
		return "Err";
}

int to_arabic(char *roman) {
	for(int i = 0; i < 100; i++) {
		if(!strcmp(romans[i], roman)) {
			return i + 1;
		}
	}

	return -1;
}

char *get_num(int n, int r, char *s) {
	if(r)
		return to_roman(n);
	else {
		sprintf(s, "%d", n);
		return s;
	}
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
	bindtextdomain ("ru", LOCALE_PATH);
	textdomain ("ru");
	
	
	int min = 0;
	int max = 101;
	int r = 0;
	char s[12];
	char input[128];
	char val_min[8];
	char val_max[8];
	
	switch(argc) {
		case 1: {
			strcpy(val_min,"1");
			strcpy(val_max, "100");
			break;
			}
		case 2: {
			if(!strcmp(argv[1], "-r")) {
				strcpy(val_min, "I");
                        	strcpy(val_max, "C");
				r = 1;
				break;
			}
			if(!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
				help();
				return 0;
			}
			
			printf(_("num-game: invalid option '%s'\n"), argv[1]);
			printf(_("Try 'num-game --help' for more information.\n"));
			return 0;	
			}
		default:
			printf(_("Usage: ./num-game [OPTIONS]\n"));
			printf(_("Try 'num-game --help' for more information.\n"));
			return 0;
	}

	printf(_("Guess a number from %s to %s:\n"), val_min, val_max);

	while(max - min > 1) {
	        printf(_("Is your number higher than %s?\n"), get_num((min + max) / 2, r, s));
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
	printf(_("Your number is %s\n"), get_num(max, r, s));

	return 0;
}

