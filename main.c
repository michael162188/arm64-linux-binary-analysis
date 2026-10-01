#include <stdio.h>
#include <string.h>
#include <stdint.h>

const uint8_t the_big_secret[] = {
        0xde, 0xc2, 0xcf, 0xf5, 0xc8, 0xc3, 0xcd, 0xf5,
        0xd9, 0xcf, 0xc9, 0xd8, 0xcf, 0xde, 0x00
};

const uint8_t the_big_code[] = {
        0xfe, 0xc2, 0xcf, 0x8a, 0xc9, 0xc5, 0xce, 0xcf,
        0x8a, 0xde, 0xc5, 0x8a, 0xcb, 0xc6, 0xc6, 0x8a,
        0xde, 0xc2, 0xc3, 0xc4, 0xcd, 0xd9, 0x90, 0x8a,
        0xec, 0xe6, 0xeb, 0xed, 0xd1, 0x9b, 0x98, 0x99,
        0x9e, 0x9f, 0x9c, 0x9d, 0x92, 0x93, 0xd7, 0x00
};

const char* get_the_code(const char* the_secret) {
	const uint8_t* pc = the_big_secret;
	while (*the_secret == (*pc ^ 0xaa)) {
		the_secret++;
		pc++;
	}
	if (*pc) return NULL;

	static char buf[sizeof(the_big_code)];
	static int initialized = 0;

	if (!initialized) {
		memcpy(buf, the_big_code, sizeof(the_big_code));

		for (size_t i = 0; i < sizeof(the_big_code) - 1; i++) {
			buf[i] ^= 0xaa;
		}
		initialized = 1;
	}

	return buf;
}

// Helper function to safely read strings like std::getline
void get_line(char* buffer, int max_len) {
    if (fgets(buffer, max_len, stdin)) {
        // Strip trailing newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

int main() {
	char username[256];
        printf("Please, enter your full name: ");
	get_line(username, sizeof(username));

        if (strcmp(username, "le door de back") != 0) {
		printf("Hello, %s! I hope you have a great day!\n", username);
		return 0;
    	}

	printf( "Very good...\n");
        char user_secret[256];
        printf("Please, do tell me a secret, will you? ");
        get_line(user_secret, sizeof(user_secret));
        
	const char* the_code = get_the_code(user_secret);
        if (!the_code) {
                printf("No code was found.\n");
                printf("There are no more features in this program.\n");
                printf("Thank you for stopping by, have a nice day now!\n");
                printf("(c) The Brotherly Institution, Inc.\n");
                return -1;
        }
        printf("%s\n", the_code);
        printf("You may now access the special features.\n");
        return 0;
}
