#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STACK_SIZE 65536


char* readContent(char* filename);
void interpreter(unsigned char* sourceCode, int* sp);

int main(int argc, char* argv[])
{    

    int STACK[STACK_SIZE] = {0};
    int* sp = STACK;
    
    char* sourceCode = readContent("helloworld.bf");

    interpreter(sourceCode, sp);
    
    free(sourceCode);
    
    return 0;
}

char* readContent(char* filename)
{
    
    int fileSize = 0;
    char* content;
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    content = calloc(fileSize + 1, 1);

    fread(content, 1, fileSize, file);

    fclose(file);

    return content;

}

void interpreter(unsigned char* sourceCode,int* sp)
{
    int balancedLoop = 0;

    int strLen = strlen(sourceCode);

    char ch;    
    
    for(int i = 0; i < strLen; i++)
    {
        ch = sourceCode[i];
        //printf("current char: %c\n", ch);
        switch(ch)
        {
            case '+':
                ++(*sp);
                break;

            case '-':
                --(*sp);
                break;

            case '>':
                ++sp;
                break;

            case '<':
                --sp;
                break;

            case '.':
                printf("%c", (char)*sp);
                break;

            case ',':
                //*sp = getchar();
                scanf("%c", sp);
                break;

            case '[':

                if( !*sp )
                {
                    balancedLoop++;
                    while(balancedLoop)
                    {
                        i++;
                        if(sourceCode[i] == ']') balancedLoop--;
                        else if(sourceCode[i] == '[') balancedLoop++;

                    }
                }
                break;

            case ']':
                if( *sp )
                {
                    balancedLoop++;
                    while(balancedLoop)
                    {
                        i--;
                        if(sourceCode[i] == '[') balancedLoop--;
                        else if(sourceCode[i] == ']') balancedLoop++;
                    }
                }
                break;

            case ' ':
                continue; //skip
                break;

            default:
                printf("ERROR: token %c incorrect!\n", ch);
                return;
        }
    }
}


// ++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.