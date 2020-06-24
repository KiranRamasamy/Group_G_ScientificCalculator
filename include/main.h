
// typedef char* token;
// typedef struct
// {
// 	void **content;
// 	int size;
// 	int top;
// } Stack;
#include "./stack.h"

typedef double number;
typedef char* token;
int convert_to_tokens(char *str, char *(**tokensRef));
number construct_num(token str);
token number_to_string(number num);
number convert_to_rad(number degrees);


number convert_to_deg(number radians);

