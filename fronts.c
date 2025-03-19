#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *html_file;
    FILE *fc_list;
    char font_family[1024];
    char command[1024];

    // Create HTML file
    html_file = fopen("/tmp/html_fonts.html", "w");
    if (html_file == NULL) {
        perror("Failed to open HTML file");
        return 1;
    }

    // Write HTML header
    fprintf(html_file, "<html>\n<head>\n<title>FONTS</title>\n</head>\n<body>\n");
    fclose(html_file);

    // Run fc-list command and capture output
    fc_list = popen("fc-list : family | sort | uniq", "r");
    if (fc_list == NULL) {
        perror("Failed to run fc-list command");
        return 1;
    }

    // Append each font to the HTML file
    html_file = fopen("/tmp/html_fonts.html", "a");
    if (html_file == NULL) {
        perror("Failed to open HTML file for appending");
        pclose(fc_list);
        return 1;
    }

    while (fgets(font_family, sizeof(font_family), fc_list) != NULL) {
        // Remove newline character if present
        size_t len = strlen(font_family);
        if (len > 0 && font_family[len-1] == '\n') {
            font_family[len-1] = '\0';
        }

        // Write font sample to HTML file
        fprintf(html_file, "<p style=\"font-family: '%s';\">%s --- the quick brown fox jumps over the lazy dog --- 0123456789</p>\n",
                font_family, font_family);
    }

    // Close HTML file
    fprintf(html_file, "</body>\n</html>\n");
    fclose(html_file);
    pclose(fc_list);

    // Open HTML file in default browser
    system("xdg-open /tmp/html_fonts.html &");

    return 0;
}
