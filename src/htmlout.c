/*
 * Generate scamp metadata report output
 *
 */
#include <stdio.h>
#include "prefs.h"

void
HtmlOut_write()
{
	char ch;

	FILE *tpl = fopen("html/scamp.html.tpl", "r");
	if (!tpl) {
		perror(prefs.html_tpl);
		return;
	}

	FILE *json = fopen(prefs.json_name, "r");
	if (!json) {
		perror("scamp.json");
		fclose(tpl);
		return;
	}

	FILE *out = fopen(prefs.html_name, "w");
	if (!out) {
		perror(prefs.html_name);
		fclose(tpl);
		fclose(json);
		return;
	}

	while ((ch = fgetc(tpl)) != EOF)
		fputc(ch, out);
	fclose(tpl);
	
	fprintf(out, "<script>\n\tvar scamp_data = $.parseJSON('");

	while ((ch = fgetc(json)) != EOF) {
		if (ch == '\'')
			fputc('\\', out);
		fputc(ch, out);
	}
	fclose(json);

	fprintf(out, "');\n</script>");
	fclose(out);

}
