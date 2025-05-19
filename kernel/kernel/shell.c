#include "shell.h"
#include "keyboard_driver.h"
#include <string.h>
#include <stdio.h>

void input(char * buffer) {
    clear_line_buffer();
    char * line = get_line_buffer();

    while (line[0] == 0) {
        asm("nop");
    }
    int i;
    for (i = 0; line[i] != 0; ++i) {
        buffer[i] = line[i];
    }

    buffer[i + 1] = 0;
}

char bonobos[28][80] = {
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMWNXX0:'oXWWN0:'lXXXNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMWXOlc;  ,xo,. .:co0NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMWNKkc.           .oOXWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMN0d:'.                 .,lxKWMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMW0o,.                         .;xXWMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMNk:.                               .l0WMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMW0:.                                   .oXMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMNd.                                       ,OWMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMXc       ..''...               ..''...      .dNMMMMMMMMMMMMMMMMM",
"MMMMMMMWKkddxO0c    .;okKXNNNX0xc'        .;okKXNNNX0xl'    .d0OxdxOXWMMMMMMMMM",
"MMMMMWO:.     .   .c0WMMMMMMMMMMMXx,    .:OWMMMMMMMMMMMNx,    .     .lKMMMMMMMM",
"MMMMWx.  ,ooc.   .cO0OOOOOOOOO00KXNKc .;dNNXK00OOOOOOOOO0k;    'lol.  ,0MMMMMMM",
"MMMMK,  :XMMX:    ..'lxO00KKK00Oko:;,..,;;cdkO0KKKK0Okd:..    .xMMMO'  lNMMMMMM",
"MMMMO.  oWMMK,  .. .kWMMMMNxcdXMMNo. ..  .kWMW0olOWMMMMNo...   dWMMX:  :XMMMMMM",
"MMMMX;  ;KMMK,  ,x;:XMMXdlxc  :XMMk,oK0x::KMMO' .oxcxNMMO,ld.  oWMWk.  oWMMMMMM",
"MMMMWO'  'd0O;  .dolXMMK; ..  :XMXooNMMM0lxWMO'  .  oNMMOcxc  .l0Ol.  :KMMMMMMM",
"MMMMMW0c.   .    'ooOWMMKo:;:dKWXxxXMMMMM0dOWW0l;;cxNMMNdol.    .   .dXMMMMMMMM",
"MMMMMMMW0dc::;.   .;cx0NWMWWWNKkxONMMMMMMMXkxOXWWWWMWXOo:,.   .;;:lkXWMMMMMMMMM",
"MMMMMMMMMMMMMNl     ..;lxkkkkkkOXMMMMMMMMMMWKkkkkkkkdc,..    .kWMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMX:       ..',c0WMMWKkx0NX0kxOXWMMNk;,'..      .dNMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMK:          :XMMMWN0dlOkclkKNWMMM0'         .oNMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMXo.        dWMMMMMMMWWWWWMMMMMMMX:        'kWMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMWO;       lWMMMMMMMMMMMMMMMMMMMK;      .lKMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMNk;.    '0WXKNMMMMMMMMMMWX0NWd.    .c0WMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMNOl'   ,OKkoloxkOkkkdoloOXd.  .,dKWMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMNOo:''lOKkoc:::::cdOKk:'':d0NMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMWX0kkKNWMWWWWWMWX0kkKNWMMMMMMMMMMMMMMMMMMMMMMMMMMMMM",
"MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM"

};






char commands[COMMAND_COUNT][32] = {"echo", "bonobos", "exit"};


void shell() {
    int run = 1;
    char buffer[500];
    printf("Available commands: echo, bonobos and exit.\n");
    while (run) {

        for (int i = 0; i < 500; ++i) {
            buffer[i] = 0;
        }
        printf("> ");
        input(buffer);

        int i;
        for (i = 0; i < COMMAND_COUNT && !startswith(commands[i], buffer); ++i) {
        }

        if (i == 0) {
            int j;
            for (j = 4; buffer[j] == ' '; ++j) {
            }
            printf("%s\n", buffer + j);
        } else if (i == 1) {
            
            for (int j = 0; j < 28; ++j) {
                printf("%s\n", bonobos[j]);
            }
        } else if (i == 2) {
            run = 0;
        }
    }

    

}





